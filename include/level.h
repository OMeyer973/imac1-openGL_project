#ifndef LEVEL_H_
#define LEVEL_H_

#include "physics.h"

//Description of the level : walls, enemy ships, bulets in the air etc...


//values describing objects in ppm file (r channel)
#define PPMWALL 0
#define PPMBONUS 100
#define PPMMOB 200


//static EntityList mobs; //linked list of mobs in the level
	//TODO : ne pas déclarer ici, mais dans une fonction d'initialisation du niveau
//static EntityList walls; //linked list of walls in the level
	//TODO : ne pas déclarer ici, mais dans une fonction d'initialisation du niveau


int makeLevelFromPPM(char* filename);
	//takes a PPM filepath as input and add objects to the 3 lists describing a level : walls list, foes list, bonus list
int addObjectToLevel(int x, int y, int obj, int type);
	//add an object to the level in correct list

int addWall(int x, int y, int type);
int addBonus(int x, int y, int type);
int addFoe(int x, int y, int type);
#endif
