#ifndef PHYSICS_H_
#define PHYSICS_H_

#include <math.h>
#include "geometry.h"
#include "entity.h"

extern int player_goX;
extern int player_goY;

extern float player_speed;
extern float input_angle;
extern int player_holdAngle;

extern EntityList level_walls;	
extern BoundingBox game_box;

extern Entity player;

//define physics elements : bounding boxes, internections


BoundingBox boundingBoxSWNE(float s, float w, float n, float e);
	//returns a boundingbox defined by its sides
float lerp(float a, float b, float f);
    //linear interpolation between a and b at 100 * f percents
void moveEntity(Entity* entity, int dt, float angle, float speed);
    //moves the entity at the given angle and speed
void movePlayer(int dt);
    //player.angle = lerp (player.angle, input_angle, 0.5);
void getAngleFromKeys();
    //assign the input angle between 0 - 2PI in function of which arrow keys are pressed
void keepPlayerInBox(BoundingBox box);
	//makes sure that the player stays inside the game space
void keepPlayerOutOfWall(Entity wall);
	//makes sure that the player stays out of the given bounding box (for the walls)
void wallsPushPlayer();
	//make sure the player is pushed by the walls
void moveBulletsList(EntityList* list, int dt);
	//moves all the bullets in the list according to their given speed
    
#endif
