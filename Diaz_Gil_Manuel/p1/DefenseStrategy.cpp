// ###### Config options ################

//#define PRINT_DEFENSE_STRATEGY 1    // generate map images

// #######################################

#define BUILDING_DEF_STRATEGY_LIB 1

#include "../simulador/Asedio.h"
#include "../simulador/Defense.h"
#include "math.h"

#ifdef PRINT_DEFENSE_STRATEGY
#include "ppm.h"
#endif

#ifdef CUSTOM_RAND_GENERATOR
RAND_TYPE SimpleRandomGenerator::a;
#endif

using namespace Asedio;

bool factible(int row,int col,int nCellsWidth, int nCellsHeight, float mapWidth,float mapHeight,std::list<Object*> obstacles,std::list<Defense*> defenses,std::list<Defense*>::iterator current){
	float cellWidth = mapWidth / nCellsWidth;
	float cellHeight = mapHeight / nCellsHeight; 
	float x,y,distanciapuntos=0;
	x=row*cellWidth+cellWidth*0.5f;
	y=col*cellHeight+cellHeight*0.5f;
	std::list<Object*>::iterator obsts=obstacles.begin();
	while(obsts != obstacles.end()){
		distanciapuntos=sqrt(abs(x-obsts->posicion.x)**2+abs(y-obsts->posicion.y)**2);
		if((current->radio+obsts->radio)>distanciapuntos)return false;
	}
	std::list<Object*>::iterator defs=defenses.begin();
	while(defs != defenses.end()){
		distanciapuntos=sqrt(abs(x-defs->posicion.x)**2+abs(y-defs->posicion.y)**2);
		if((current->radio+defs->radio)>distanciapuntos)return false;
	}
	return true;

}

float cellValue(int row, int col, bool** freeCells, int nCellsWidth, int nCellsHeight
	, float mapWidth, float mapHeight, List<Object*> obstacles, List<Defense*> defenses) {
	return 0; // implemente aqui la función que asigna valores a las celdas
}
void selecionarCeldas(int &row,int &col,const float &vCelda,const bool &bCelda, int nCellsWidth,int nCellsHeight){
	float mejorvalor=vCelda[0][0];
	for (int i = 0; i < nCellsWidth ; ++i)
	{
		for (int j = 0; j < nCellsHeight; ++j)
		{
			if((vCelda[i][j] > mejorvalor)&& (!bCelda[i][j])){
				row=i;
				col=j;
				mejorvalor=vCelda[i][j];
			}
		}
	}
}

bool ocupado(const bool &bCelda,int nCellsWidth,int nCellsHeight){
	for (int i = 0; i < nCellsWidth; ++i)
	{
		for (int j = 0; j < nCellsHeight; ++j)
		{
			if(!bCelda[i][j])return false;
			
		}
	}
	return true;
}

void DEF_LIB_EXPORTED placeDefenses(bool** freeCells, int nCellsWidth, int nCellsHeight, float mapWidth, float mapHeight
              , std::list<Object*> obstacles, std::list<Defense*> defenses) {

    float cellWidth = mapWidth / nCellsWidth;
    float cellHeight = mapHeight / nCellsHeight; 

 
    float vCelda[nCellsWidth][nCellsHeight];
    bool bCelda[nCellsWidth][nCellsHeight];
    bool colocado=false;
    int x=0,y=0;
    List<Defense*>::iterator currentDefense = defenses.begin(); //Primera defensa (Generador)
    for (int i = 0; i < nCellsWidth; ++i)
    {
    	for (int j = 0; j < nCellsHeight; ++j)
    	{
    		vCelda[i][j]=cellValue(i,j,freeCells,nCellsWidth,nCellsHeight,mapWidth,mapHeight,obstacles,defenses);	
    		bCelda[i][j]=false;
    	}
    }

    while(ocupado(bCelda,nCellsWidth,nCellsHeight) || !colocado){
    	selecionarCeldas(x,y,vCelda,bCelda,nCellsWidth,nCellsHeight);
    	bCelda[x][y]=true;
    	if(factible(x,y,nCellsWidth,nCellsHeight,mapWidth,mapHeight,obstacles,defenses,currentDefense)){
    		(*currentDefense)->position.x = x * cellWidth + cellWidth * 0.5f;
        	(*currentDefense)->position.y = y * cellHeight + cellHeight * 0.5f;
        	(*currentDefense)->position.z = 0; 
    	}
    }
    ++currentDefense;
    for (int i = 0; i < nCellsWidth; ++i)
    {
    	for (int j = 0; j < nCellsHeight; ++j)
    	{
    		vCelda[i][j]=cellValue(i,j,freeCells,nCellsWidth,nCellsHeight,mapWidth,mapHeight,obstacles,defenses);	
    		bCelda[i][j]=false;
    	}
    }

    bool auxbCelda=new bool(bCelda);
    while(currentDefense != defenses.end()) {
    	x=0;
    	y=0;
    	bCelda=new bool(auxbCelda);
    	colocado=false;
    	while(ocupado(bCelda,nCellsWidth,nCellsHeight) || !colocado){
    		selecionarCeldas(x,y,vCelda,bCelda,nCellsWidth,nCellsHeight);
    		bCelda[x][y]=true;
    		if(factible(x,y,nCellsWidth,nCellsHeight,mapWidth,mapHeight,obstacles,defenses,currentDefense)){
    			(*currentDefense)->position.x = x * cellWidth + cellWidth * 0.5f;
        		(*currentDefense)->position.y = y * cellHeight + cellHeight * 0.5f;
        		(*currentDefense)->position.z = 0; 
    		}
    	}
    	/*
        (*currentDefense)->position.x = ((int)(_RAND2(nCellsWidth))) * cellWidth + cellWidth * 0.5f;
        (*currentDefense)->position.y = ((int)(_RAND2(nCellsHeight))) * cellHeight + cellHeight * 0.5f;
        (*currentDefense)->position.z = 0; 
        ++currentDefense;
        */
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
