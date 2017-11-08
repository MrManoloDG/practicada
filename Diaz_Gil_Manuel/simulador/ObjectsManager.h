#ifndef _ObjectsManager_
#define _ObjectsManager_

#include "Asedio.h"

namespace Asedio
{
    template <class T>
    class ObjectsManager {
    protected:
        Game* game;
    public:
        List<T> objects;

        ObjectsManager(Game* game){
            this->game = game;
        }

        virtual ~ObjectsManager(){
            deleteAllObjects();
        }

        /*virtual*/ bool addObject(T object){ 
            objects.push_back(object);
			return true;
        }

		void removeObject(T object){ 
            objects.remove(object);
        }

        void deleteAllObjects(){ 
            for (typename List<T>::iterator it=objects.begin(); it != objects.end(); ++it) {
                _DELETE(*it);
            }
            objects.clear();
        }

        void update(float step){
            typename List<T>::iterator it=objects.begin();
            while ( it != objects.end() ) {
                if(!(*it)->update(step)) {
                    it = objects.erase(it); // the iterator is automatically incremented
                } else {
                    ++it;
                }
            }
        }

        T getClosestTo(Vector3 position){
            float min = INF_F;
            T o = NULL;
            for (typename List<T>::iterator it=objects.begin(); it != objects.end(); ++it) {
                float dist = _sdistance((*it)->position, position);
                if(dist < min) {
                    min = dist;
                    o = (*it);
                }
            }
            return o;
        }
        
        void getInRange(Vector3 position, float range, List<T>& out){
            for (typename List<T>::iterator it=objects.begin(); it != objects.end(); ++it) {
                float dist = _sdistance((*it)->position, position);
                if(dist <= range * range) {
                    out.push_back(*it);
                }
            }
        }
    };
}

#endif
