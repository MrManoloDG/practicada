#define VERSION 1.6

// ###### Config options ################

#define RANDOM_DEFENSES 1

//#define PESIMISTIC_FREE_CELLS 1 // mark cell as invalid if any of its borders collide with an obstacle
//#define OPTIMISTIC_FREE_CELLS 1 // mark cell as invalid only if all of its borders collide with an obstacle
#define DEFAULT_FREE_CELLS 1    // mark cell as invalid only if its center collides with an obstacle

#define CUSTOM_RAND_GENERATOR 1

#define FORCE_DEFENSES_AT_CELLS_CENTER 1 // defenses are moved to the center of the cells automatically

//#define PEDANTIC 1 // more detailed debug information

// #######################################

#include <list>
#include <limits>
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include "Vector3.h"


//To use this module in a library, say libfoo, you will do these steps:
//
//Add @CFLAG_VISIBILITY@ or (in a Makefile.am) $(CFLAG_VISIBILITY) to the CFLAGS for the compilation of the sources that make up the library.
//Add a C macro definition, say ‘-DBUILDING_LIBFOO’, to the CPPFLAGS for the compilation of the sources that make up the library.
//Define a macro specific to your library like this.
//
//          #if BUILDING_LIBFOO && HAVE_VISIBILITY
//          #define LIBFOO_DLL_EXPORTED __attribute__((__visibility__("default")))
//          #else
//          #define LIBFOO_DLL_EXPORTED
//          #endif
//
//This macro should be enabled in all public header files of your library.
//Annotate all variable, function and class declarations in all public header files of your library with ‘LIBFOO_DLL_EXPORTED’. This annotation can occur at different locations: between the ‘extern’ and the type or return type, or just before the entity being declared, or after the entire declarator. My preference is to put it right after ‘extern’, so that the declarations in the header files remain halfway readable. 
//
//Note that the precise control of the exported symbols will not work with other compilers than GCC >= 4.0, and will not work on systems where the assembler or linker lack the support of “hidden” visibility. Therefore, it's good if, in order to reduce the risk of collisions with symbols in other libraries, you continue to use a prefix specific to your library for all non-static variables and functions and for all C++ classes in your library. 

#if BUILDING_DEF_STRATEGY_LIB && HAVE_VISIBILITY
#define DEF_LIB_EXPORTED __attribute__((__visibility__("default")))
#elif BUILDING_DEF_STRATEGY_LIB && defined _MSC_VER
#define DEF_LIB_EXPORTED __declspec(dllexport)
#elif defined _MSC_VER
#define DEF_LIB_EXPORTED __declspec(dllimport)
#else
#define DEF_LIB_EXPORTED
#endif

#define _DELETE(p)      if ( (p) != NULL ) { delete p; p = NULL; }

#define List std::list

#define _distance(a,b) b.subtract(a).length()
#define _sdistance(a,b) b.subtract(a).slength() // squared length

#define INF_F std::numeric_limits<float>::max()
#define INF_I std::numeric_limits<int>::max()
#define INF_UI std::numeric_limits<int>::max()

#ifdef CUSTOM_RAND_GENERATOR

#define CUSTOM_RAND_MAX 32749

#define _RAND1 static_cast <float> (SimpleRandomGenerator::nextValue()) / static_cast <float> (CUSTOM_RAND_MAX) // number from 0.0 to 1.0, inclusive.
#define _RAND2(b) static_cast <float> (SimpleRandomGenerator::nextValue()) / (static_cast <float> (CUSTOM_RAND_MAX/b)) // number from 0.0 to b
#define _RAND3(a,b) a + static_cast <float> (SimpleRandomGenerator::nextValue()) /( static_cast <float> (CUSTOM_RAND_MAX/(b-a))) // number from a to b

#else

#define _RAND1 static_cast <float> (rand()) / static_cast <float> (RAND_MAX) // number from 0.0 to 1.0, inclusive.
#define _RAND2(b) static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/b)) // number from 0.0 to b
#define _RAND3(a,b) a + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(b-a))) // number from a to b

#endif

#ifndef _Asedio_
#define _Asedio_

#ifdef CUSTOM_RAND_GENERATOR
#define RAND_TYPE long
    class SimpleRandomGenerator {
    protected:
        static RAND_TYPE a;
    public:
        SimpleRandomGenerator(RAND_TYPE seed = 1) { a = seed; }

        static int nextValue(RAND_TYPE lim = CUSTOM_RAND_MAX) {
            a = (a * 32719 + 3) % 32749;
            return ((a % lim) + 1);
        }
    };
#endif

namespace Asedio
{

    class Object {
    public:
        int id;
        Vector3 position;
        float radio;

        Object(int id, float radio) : id(id), radio(radio) { }

        virtual Object* clone(){
            Object* copy = new Object(id, radio);
            copy->position.x = position.x;
            copy->position.y = position.y;
            copy->position.z = position.z;
            return copy;
        }
    };

    class DynamicObject : public Object {
    public:
        float elapsed;

        DynamicObject(int id, float radio) : Object(id, radio), elapsed(0) { }

        virtual bool update(float step) { elapsed += step; return true; }

        virtual void clearCache() {}
    };

    enum Action { ACTION_NONE=0, ACTION_ATTACK, ACTION_HURT };

    typedef struct {
        float instant;
        Vector3 position;
        Action action;
        float argument;
    } Event;

    class RecordableObject : public DynamicObject {
    protected:
        float timeSinceLastRecord;
    public:
        float interval;
        float creation;

        List<Event> events;

        RecordableObject(int id, float radio, float interval, float currentInstant) 
            : DynamicObject(id, radio), interval(interval), creation(currentInstant)
            , timeSinceLastRecord(10000000) { }

        virtual bool update(float step) { 

            if(timeSinceLastRecord > interval) {
                recordKey();
            }
            timeSinceLastRecord += step; 

            return DynamicObject::update(step);
        }

        virtual void recordKey(Action action, int arg) {             
            timeSinceLastRecord = 0;
            Event e;
            e.instant = elapsed;
            e.position = Vector3(position.x, position.y, position.z);
            e.action = action;
            e.argument = arg;
            events.push_back(e);        
        }

        virtual void recordKey() {             
            recordKey(ACTION_NONE, INF_I);       
        }

        virtual void recordKey(Action action) {
            recordKey(action, INF_I);
        }

        virtual void clearCache() {}
    };

    class AStarNode {
    public:
        List<AStarNode*> adjacents;
        Vector3 position;
        AStarNode* parent;
        float F, G, H;

        AStarNode() : parent(NULL), F(0), G(0), H(0) {};
    };

    class Defense;
    class DefensesManager;
    class Unit;
    class UnitsManager;
    class Game;
    class Map;
//    class ObjectsManager;
}

#endif
