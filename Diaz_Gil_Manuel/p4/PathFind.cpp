// ###### Config options ################

#define PRINT_PATHS 1

// #######################################

#define BUILDING_DEF_STRATEGY_LIB 1

#include "../simulador/Asedio.h"
#include "../simulador/Defense.h"
#include <queue>
#include <set>

#ifdef PRINT_PATHS
#include "ppm.h"

#endif

using namespace Asedio;

Vector3 cellCenterToPosition(int i, int j, float cellWidth, float cellHeight){ 
    return Vector3((j * cellWidth) + cellWidth * 0.5f, (i * cellHeight) + cellHeight * 0.5f, 0); 
}

void DEF_LIB_EXPORTED calculateAdditionalCost(float** additionalCost
                   , int cellsWidth, int cellsHeight, float mapWidth, float mapHeight
                   , List<Object*> obstacles, List<Defense*> defenses) {

    float cellWidth = mapWidth / cellsWidth;
    float cellHeight = mapHeight / cellsHeight;

    for(int i = 0 ; i < cellsHeight ; ++i) {
        for(int j = 0 ; j < cellsWidth ; ++j) {
            Vector3 cellPosition = cellCenterToPosition(i, j, cellWidth, cellHeight);
            float cost = 0;
            if( (i+j) % 2 == 0 ) {
                cost = cellWidth * 100;
            }
            
            additionalCost[i][j] = cost;
        }
    }
}

void DEF_LIB_EXPORTED calculatePath(AStarNode* originNode, AStarNode* targetNode
                   , int cellsWidth, int cellsHeight, float mapWidth, float mapHeight
                   , float** additionalCost, std::list<Vector3> &path) {

    std::priority_queue<AStarNode*> opened;
    std::set<AStarNode*> closed,open;
   
    originNode->G = 0;
    originNode->H = abs((originNode)->position.length() - targetNode->position.length());
    originNode->F = (originNode)->G + (originNode)->H;
    opened.push(originNode);
    int maxIter = 100;
    AStarNode* current = originNode;

    while(current != targetNode && maxIter > 0 and !opened.empty()) { // @todo ensure current and target are connected
        current = opened.top();
        opened.pop();
        float min = INF_F;
        if(current != targetNode){
            for (List<AStarNode*>::iterator it=current->adjacents.begin(); it != current->adjacents.end(); ++it){
                if(closed.count(*it) == 0){
                    if(open.count(*it) == 0){
                        (*it)->parent = current;
                        (*it)->G = current->G + abs((*it)->position.length() - current->position.length());
                        (*it)->H = abs((*it)->position.length() - targetNode->position.length());

                        (*it)->F = (*it)->G + (*it)->H;
                        opened.push((*it));
                        open.insert((*it));
                    }else{
                        min = abs((*it)->position.length() - current->position.length());
                        if((*it)->G > (current->G + min)){
                            (*it)->parent = current;
                            (*it)->G = current->G + min;
                            (*it)->F = (*it)->G + (*it)->H;
                        }
                    }
                }
            }

        }
        closed.insert(current);
	    

       
    }
    

    current = targetNode;    
    path.push_back(current->position);
    while(current->parent != originNode){
        current = current->parent;
        path.push_back(current->position);
    }
    --maxIter;

}
