#ifndef LEVEL_H_
#define LEVEL_H_

#include "physics.h"

//Description of the level : walls, enemy ships, bulets in the air etc...

typedef struct entity {
	BoundingBox spriteBox;  //general : size of sprite
	int textureID; 			//general : id of the texture in the gluint textures list
	BoundingBox hitBox; 	//general : size of hitbox
	int type;				//general : type of entity : mob - wall - bonus - bullet-  animation
	
	int subType;			//mob - bullet - bonus : sub-type of entity
	int hp; 				//mob : nb of health points - bonus : nb of bonus hp - bullet : damage caused by the bullet
	int bulletType; 		//mob : id of bullet to  instantiate when shooting 
	float speed; 			//mob - bullet : speed of movement
	float delay; 			//mob : delay between 2 shots - bonus : new delay between 2 shots - annimation : remaining time of animation
	int shootAnglesNb; 		//mob : nb of shooting angles
	float* shootAngles; 	//mob : array of shooting angles

	struct entity* next;	//next entity in the linked list
} Entity, *EntityList;


//values describing objects in ppm file (r channel)
#define WALL 0
#define BONUS 100
#define FOE 200


static EntityList mobs; //linked list of foes in the level
	//TODO : ne pas déclarer ici, mais dans une fonction d'initialisation du niveau
static EntityList walls; //linked list of walls in the level7
	//TODO : ne pas déclarer ici, mais dans une fonction d'initialisation du niveau


int makeLevelFromPPM(char* filename);
	//takes a PPM filepath as input and add objects to the 3 lists describing a level : walls list, foes list, bonus list
int addObjectToLevel(int x, int y, int obj, int type);
	//add an object to the level in correct list

int addWall(int x, int y, int type);
int addBonus(int x, int y, int type);
int addFoe(int x, int y, int type);
#endif
