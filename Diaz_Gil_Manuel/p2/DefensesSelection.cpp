// ###### Config options ################


// #######################################

#define BUILDING_DEF_STRATEGY_LIB 1

#include "../simulador/Asedio.h"
#include "../simulador/Defense.h"

using namespace Asedio;

float valorar(const Defense& d){
	std::cout<<"Radio: "<<d.range<<" dispersion: "<<d.dispersion<<" Daño: "<<d.damage<<" ataques por segundo: "<<d.attacksPerSecond<<" vida: "<<d.health<<std::endl;
	return (d.range/30)+d.dispersion+((d.damage*d.attacksPerSecond)/5)+(d.health/500);
}

void DEF_LIB_EXPORTED selectDefenses(std::list<Defense*> defenses, unsigned int ases, std::list<int> &selectedIDs
            , float mapWidth, float mapHeight, std::list<Object*> obstacles) {
	float tabla[defenses.size()][ases];
	float valor[defenses.size()];
	int costes[defenses.size()];


    std::list<Defense*>::iterator it = defenses.begin();
    int i = 0;
    for(it = defenses.begin(); it!=defenses.end();++it){
    	valor[i]=valorar(*(*it));
    	costes[i]=(*it)->cost;
    }

    for (int j = 0; j < ases; ++j)
    {
    	if(j<costes[0]){
    		tabla[0][j] = 0;
    	}else{
    		tabla[0][j] = valor[0];
    	}
    }

    for (int j = 1; j < defenses.size(); ++j)
    {
    	for (int z = 0; z < ases; ++z)
    	{
    		if(z < costes[j]){
    			tabla[j][z] = tabla[j-1][z];
    		}else{
    			tabla[j][z] = std::max(tabla[j-1][z],(tabla[j-1][z-costes[j]]+valor[i]));
    		}
    		std::cout<<tabla[j][z]<<" ";
    	}
    	std::cout<<""<<std::endl;
    }


    
    it = defenses.begin();
    unsigned int currentases = ases;
    selectedIDs.push_back((*it)->id);
    currentases -= (*it)->cost;

    it = defenses.end();
    for (i = defenses.size()-1; i > 0; --i)
    {
    	--it;
    	if (tabla[i][currentases]!=tabla[i-1][currentases])
    	{
    		selectedIDs.push_back((*it)->id);
    		currentases -= (*it)->cost;
    	}
    }

    /**
    
    std::list<Defense*>::iterator it = defenses.begin();
    while(it != defenses.end()) {
        if(cost + (*it)->cost <= ases) {
            selectedIDs.push_back((*it)->id);
            cost += (*it)->cost;
        }
        ++it;
    }
    */
}
