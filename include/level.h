#ifndef LEVEL_H_
#define LEVEL_H_

//Description of the level : walls, enemy ships, bulets in the air etc...

/*
walls[] - bounding box, position
foes* (ennemy ships) - bounding box, position, hp
*/

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


static FoeList foes; //chained list of foes in the level
	//TODO : ne pas déclarer ici, mais dans une fonction d'initialisation du niveau
static Wall walls[]; //fixed-lenght list of walls in the level7
	//TODO : ne pas déclarer ici, mais dans une fonction d'initialisation du niveau


#endif
