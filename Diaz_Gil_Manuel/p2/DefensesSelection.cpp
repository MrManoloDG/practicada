// ###### Config options ################


// #######################################

#define BUILDING_DEF_STRATEGY_LIB 1

#include "../simulador/Asedio.h"
#include "../simulador/Defense.h"

using namespace Asedio;

double valorar(const Defense& d){
    double x= (d.range/30)*10+d.dispersion*12+((d.damage*d.attacksPerSecond)/5)*15+(d.health/500)*5+(1-(d.cost/150))*8;
    std::cout<<x<<std::endl;
    return x;

}

void DEF_LIB_EXPORTED selectDefenses(std::list<Defense*> defenses, unsigned int ases, std::list<int> &selectedIDs
            , float mapWidth, float mapHeight, std::list<Object*> obstacles) {
    double tabla[defenses.size()][ases];
    double valor[defenses.size()];
    double costes[defenses.size()];


    std::list<Defense*>::iterator it = defenses.begin();
    int i = 0;
    for(it = defenses.begin(); it!=defenses.end();++it){
        valor[i] = valorar(*(*it));
        costes[i]=(*it)->cost;
        i++;
    }

    for (int j = 0; j < ases; ++j)
    {
        if(j<costes[0]){
            tabla[0][j] = 0;
        }else{
            tabla[0][j] = valor[0];
        }
    }

    for (i = 1; i < defenses.size(); i++)
    {
        for (int j = 0; j < ases; j++)
        {
            if(j < costes[i]){
                tabla[i][j] = tabla[i-1][j];
            }else{
                tabla[i][j] = std::max(tabla[i-1][j],tabla[i-1][j-(int)costes[i]]+valor[i]);
            }
            
        }
        
    }


    
    it = defenses.begin();
    int currentases = ases;
    selectedIDs.push_back((*it)->id);
    currentases -= (*it)->cost - 1;

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
