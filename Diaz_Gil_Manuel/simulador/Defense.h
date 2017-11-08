#ifndef _Defense_
#define _Defense_

#include "Asedio.h"
#include "ObjectsManager.h"

#define DEFAULT_DEFENSE_RADIO 5
#define DEFAULT_DEFENSE_RANGE 30
#define DEFAULT_DEFENSE_DISPERSION 1
#define DEFAULT_DEFENSE_DAMAGE 5
#define DEFAULT_DEFENSE_ATTACKS_PER_SECOND 1
#define DEFAULT_DEFENSE_HEALTH 500
#define DEFAULT_DEFENSE_COST 100

namespace Asedio
{
    class Defense : public RecordableObject {
    public:
        float range, dispersion, damage, attacksPerSecond, health;
        unsigned int cost, type;

    protected:
        float timeForNextAttack, secondsPerAttack;
        Game* game;

    public:

        Defense(Game* game, int id);

        Defense(Game* game, int id, float radio, unsigned int type, float range, float dispersion, float damage
            , float attacksPerSecond, float health, unsigned int cost);

        virtual ~Defense(){};

        virtual bool update(float step);
        void attack(Unit* u);
        void hurt(float damage);

        virtual void clearCache() { secondsPerAttack = 1 / attacksPerSecond; };
        virtual Defense* clone();
    };

    class DefensesManager : public ObjectsManager<Defense*> {
    protected:
		std::string error;
    public:

        enum STRATEGY_MODE { RANDOM=0, EXTERNAL };

        List<Defense*> destroyed;
        bool valid;

        DefensesManager(Game* game) : valid(false), ObjectsManager<Defense*>(game), error("") {};
        virtual ~DefensesManager();

        bool addObject(Defense* object);

		void removeObject(Defense* object);

		void kill(Defense* defense);

		std::string getError() { return error; };

        unsigned int createDefenses(unsigned int nDefenses, unsigned int nDefenseTypes, float randomness);
        
        void placeDefenses_(STRATEGY_MODE mode, int nCellsBorderWidth = 1, int nCellsBorderHeight = 1);
        void placeDefensesRandomly();
        
        void selectDefenses_(unsigned int ases);

        bool validateDefense(Defense* defense, float mapInnerBorder = 0);
        bool validate(float mapInnerBorder = 0);

		// debug utils

		unsigned char* dAddDefensesToImage(unsigned char* pixels);
    };
}

#endif
