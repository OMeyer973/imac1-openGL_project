#ifndef LEVEL_H_
#define LEVEL_H_

#include "physics.h"

//Description of the level : walls, enemy ships, bulets in the air etc...

typedef struct wall {
	BoundingBox spriteBox; //size of sprite
	BoundingBox hitBox; //size of hitbox
	int textureID;
} Wall;

typedef struct foe {
	BoundingBox spriteBox; //size & position of sprite
	BoundingBox hitBox; //size & position of hitbox
	int hp; //nb of health points
	int foeType; //id of foe to look for additional info in correct foeStat 
	int bulletType; //id of bullet to look for infos when instantiating a bullet 
	struct foe* nextFoe; //next foe in the list of foes
} Foe, *FoeList;

typedef struct bonus {
	BoundingBox spriteBox; //size & position of sprite
	BoundingBox hitBox; //size & position of hitbox
	int BonusType; //id of foe to look for additional info in correct bonusStat 
	struct bonus* nextBonus; //next bonus in the list of foes
} Bonus, *BonusList;

//values describing objects in ppm file (r channel)
#define WALL 0
#define BONUS 100
#define FOE 200


static FoeList foes; //chained list of foes in the level
	//TODO : ne pas déclarer ici, mais dans une fonction d'initialisation du niveau
static Wall walls[]; //fixed-lenght list of walls in the level7
	//TODO : ne pas déclarer ici, mais dans une fonction d'initialisation du niveau


int makeLevelFromPPM(char* filename);
	//takes a PPM filepath as input and add objects to the 3 lists describing a level : walls list, foes list, bonus list
int addObjectToLevel(int x, int y, int obj, int type);
	//add an object to the level in correct list

int addWall(int x, int y, int type);
int addBonus(int x, int y, int type);
int addFoe(int x, int y, int type);
#endif
