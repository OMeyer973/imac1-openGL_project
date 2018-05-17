#ifndef ENTITY_H_
#define ENTITY_H_

//#include "geometry.h"

//Description of the level : walls, enemy ships, bulets in the air etc...

//STRUCTURE
typedef struct point2D {
	float x, y;
} Point2D;


typedef struct boundingBox {
	//the 2 bounding box corners : north-west & south-east
	//sw.x < ne.x, sw.y < ne.y
	Point2D sw, ne;
} BoundingBox;


typedef struct entity {
	//structure describing an entity : wall - mob - bonus - bullet - VFX 
	Point2D anchor;			//general : position of the entity
	BoundingBox spriteBox;  //general : size of sprite
	int textureID; 			//general : id of the texture in the gluint textures list
	BoundingBox hitBox; 	//general : size of hitbox
	int type;				//general : type of entity : mob - wall - bonus - bullet - VFX
	
	int subType;			//mob - bullet - bonus : sub-type of entity
	int hp; 				//mob : nb of health points - bonus : nb of bonus hp - bullet : damage caused by the bullet
	int bulletType; 		//mob : id of bullet to  instantiate when shooting 
	float angle; 			//mob - bullet : facing direction
	float speed; 			//mob - bullet : speed of movement - bonus - new bullet speed of movement
	float shootDelay; 		//mob : delay between 2 shots - bonus : new delay between 2 shots - VFX : second time, may be used for animation
	float shootTime;		//mob : entity internal time used to compute shots delay
	float invDelay; 		//mob : delay during wich the entity is invincible - bonus : new invDelay to affect the player - VFX : remaining time of animation
	float invTime;			//mob : entity internal time used to compute invicible time
	int shootAnglesNb; 		//mob : nb of shooting angles
	float shootAngles[16]; 	//mob : array of shooting angles
	int behaviorsNb;		//general : number of behaviors the entity have
	int behaviors[8];		//general : ids of behaviors the entity have (movement, rotation, opacity)
	struct entity* next;	//next entity in the linked list
	struct entity* prev;	//previous entity in the linked list (used to simplify the remove function)
} Entity, *EntityList;

//FUNCTIONS

Point2D pointXY(float x, float y);
	//returns a point defined by its coordinates
BoundingBox boundingBoxSWNE(float s, float w, float n, float e);
	//returns a boundingbox defined by its sides

EntityList instantiateEntity (
		Point2D anchor,
		BoundingBox spriteBox, 
		int textureID, 
		BoundingBox hitBox,
		int type,
		int subType,
		int hp,
		int bulletType,
		float angle,
		float speed,
		float shootDelay,
		float invDelay,
		int shootAnglesNb,
		float* shootAngles,
		int behaviorsNb,
		int* behaviors
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
void removeEntity(EntityList* entity, EntityList* list);
	//remove the entity from the list it belongs to
void deleteList(EntityList* list);
	//delete all the entities of the list

#endif
