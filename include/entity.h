#ifndef ENTITY_H_
#define ENTITY_H_

#include "physics.h"

//Description of the level : walls, enemy ships, bulets in the air etc...

//STRUCTURE

typedef struct entity {
	//structure describing an entity : wall - mob - bonus - bullet - VFX 
	Point2D center;			//general : position of the entity
	BoundingBox spriteBox;  //general : size of sprite
	int textureID; 			//general : id of the texture in the gluint textures list
	BoundingBox hitBox; 	//general : size of hitbox
	int type;				//general : type of entity : mob - wall - bonus - bullet - VFX
	
	int subType;			//mob - bullet - bonus : sub-type of entity
	int hp; 				//mob : nb of health points - bonus : nb of bonus hp - bullet : damage caused by the bullet
	int bulletType; 		//mob : id of bullet to  instantiate when shooting 
	float speed; 			//mob - bullet : speed of movement - bonus - new bullet speed of movement
	float delay; 			//mob : delay between 2 shots - bonus : new delay between 2 shots - VFX : remaining time of animation
	int shootAnglesNb; 		//mob : nb of shooting angles
	float* shootAngles; 	//mob : array of shooting angles

	struct entity* next;	//next entity in the linked list
	struct entity* prev;	//previous entity in the linked list (used to simplify the remove function)
} Entity, *EntityList;

//FUNCTIONS

EntityList instantiateEntity (
		Point2D center,
		BoundingBox spriteBox, 
		int textureID, 
		BoundingBox hitBox,
		int type,
		int subType,
		int hp,
		int bulletType,
		float speed,
		float delay,
		int shootAnglesNb,
		float* shootAngles
	);
	//instantiate an entity according to the given parameters and return it's adress
EntityList copyEntity (EntityList orig);
	//instantiate an entity with the same parameters as the one given as argument and return it's adress
void printEntity(EntityList list);
	//prints all the parameters of an entity
void addEntityStart(EntityList* list, EntityList entity);
	//adds the entity at the start of the list (only use with entity->next == NULL or the next entity will be lost in memory)
void addEntityEnd(EntityList* list, EntityList entity);
	//adds the entity at the end of the list (only use with entity->next == NULL or the next entity will be lost in memory)
void removeEntity(EntityList* entity);
	//remove the entity from the list it belongs to

#endif
