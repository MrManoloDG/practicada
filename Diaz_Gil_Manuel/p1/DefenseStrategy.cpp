// ###### Config options ################

//#define PRINT_DEFENSE_STRATEGY 1    // generate map images

// #######################################

#define BUILDING_DEF_STRATEGY_LIB 1

#include "../simulador/Asedio.h"
#include "../simulador/Defense.h"
#include "math.h"
#include <queue>

#ifdef PRINT_DEFENSE_STRATEGY
#include "ppm.h"
#endif

#ifdef CUSTOM_RAND_GENERATOR
RAND_TYPE SimpleRandomGenerator::a;
#endif

using namespace Asedio;

struct celda
{
    int row,col;
    float valor;
    celda():row(0),col(0),valor(0){}
    celda(int x,int y,float v):row(x),col(y),valor(v){}
    

};
bool operator < (const celda& a,const celda& b){return a.valor<b.valor;}

bool factible(int row,int col,int nCellsWidth, int nCellsHeight, float mapWidth,float mapHeight,std::list<Object*> obstacles,std::list<Defense*> defenses,std::list<Defense*>::iterator current){
	float cellWidth = mapWidth / nCellsWidth;
	float cellHeight = mapHeight / nCellsHeight; 
	float x,y,distanciapuntos=0;
	x=row*cellWidth+cellWidth*0.5f;
	y=col*cellHeight+cellHeight*0.5f;
	std::list<Object*>::iterator obsts=obstacles.begin();
	while(obsts != obstacles.end()){
		distanciapuntos=sqrt(abs(x-(*obsts)->position.x)*abs(x-(*obsts)->position.x) +abs(y-(*obsts)->position.y)*abs(y-(*obsts)->position.y));
		if(((*current)->radio+(*obsts)->radio)>distanciapuntos)return false;
        ++obsts;
	}
    
	std::list<Defense*>::iterator defs=defenses.begin();
	
    while(defs != defenses.end()){
		distanciapuntos=sqrt(abs(x-(*defs)->position.x)*abs(x-(*defs)->position.x)+abs(y-(*defs)->position.y)*abs(y-(*defs)->position.y));
		if(((*current)->radio+(*defs)->radio)>distanciapuntos)return false;
        ++defs;
	}
    
	return true;

}

float cellValue(int row, int col, bool** freeCells, int nCellsWidth, int nCellsHeight
	, float mapWidth, float mapHeight, List<Object*> obstacles, List<Defense*> defenses) {
	return 0; // implemente aqui la función que asigna valores a las celdas
}


void DEF_LIB_EXPORTED placeDefenses(bool** freeCells, int nCellsWidth, int nCellsHeight, float mapWidth, float mapHeight
              , std::list<Object*> obstacles, std::list<Defense*> defenses) {

    float cellWidth = mapWidth / nCellsWidth;
    float cellHeight = mapHeight / nCellsHeight; 

 
   // float vCelda=new float [nCellsWidth][nCellsHeight];

    bool colocado=false;

    celda cactual;
    std::priority_queue<celda> mceldas;
    List<Defense*>::iterator currentDefense = defenses.begin(); //Primera defensa (Generador)
    for (int i = 0; i < nCellsWidth; ++i)
    {
        
    	for (int j = 0; j < nCellsHeight; ++j)
    	{
    		mceldas.push(celda(i,j,cellValue(i,j,freeCells,nCellsWidth,nCellsHeight,mapWidth,mapHeight,obstacles,defenses)));	
    		
    	}
    }

    while(!mceldas.empty() && !colocado){
    	cactual=mceldas.top();
        mceldas.pop();
    	if(factible(cactual.row,cactual.col,nCellsWidth,nCellsHeight,mapWidth,mapHeight,obstacles,defenses,currentDefense)){
    		(*currentDefense)->position.x = (cactual.row * cellWidth) + cellWidth * 0.5f;
        	(*currentDefense)->position.y = (cactual.col * cellHeight) + cellHeight * 0.5f;
        	(*currentDefense)->position.z = 0; 
            colocado=true;
    	}

    }
    ++currentDefense;
    /*
    std::priority_queue<celda> mceldas2;
    for (int i = 0; i < nCellsWidth; ++i)
    {
    	for (int j = 0; j < nCellsHeight; ++j)
    	{
    		mceldas2.push(celda(i,j,cellValue(i,j,freeCells,nCellsWidth,nCellsHeight,mapWidth,mapHeight,obstacles,defenses)));
    	}
    }
    */

    while(currentDefense != defenses.end()) {
    	colocado=false;
    	while(!mceldas.empty() && !colocado){
    		cactual=mceldas.top();
            mceldas.pop();
    		if(factible(cactual.row,cactual.col,nCellsWidth,nCellsHeight,mapWidth,mapHeight,obstacles,defenses,currentDefense)){
    			(*currentDefense)->position.x = (cactual.row * cellWidth) + cellWidth * 0.5f;
        		(*currentDefense)->position.y = (cactual.col * cellHeight) + cellHeight * 0.5f;
        		(*currentDefense)->position.z = 0; 
                colocado=true;
                std::cout<<"Defensa colocada "<<std::endl;
    		}
    	}
        ++currentDefense;
    	
    }

#ifdef PRINT_DEFENSE_STRATEGY

    float** cellValues = new float* [nCellsHeight]; 
    for(int i = 0; i < nCellsHeight; ++i) {
       cellValues[i] = new float[nCellsWidth];
       for(int j = 0; j < nCellsWidth; ++j) {
           cellValues[i][j] = ((int)(cellValue(i, j))) % 256;
       }
    }
    dPrintMap("strategy.ppm", nCellsHeight, nCellsWidth, cellHeight, cellWidth, freeCells
                         , cellValues, std::list<Defense*>(), true);

    for(int i = 0; i < nCellsHeight ; ++i)
        delete [] cellValues[i];
	delete [] cellValues;
	cellValues = NULL;

#endif
}
