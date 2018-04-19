#ifndef PHYSICS_H_
#define PHYSICS_H_

#include <math.h>
#include "geometry.h"
#include "entity.h"

extern int keyRight;
extern int keyLeft;
extern int keyUp;
extern int keyDown;

extern float player_speed;
extern float input_angle;

extern Entity player;

//define physics elements : bounding boxes, internections


BoundingBox boundingBoxSWNE(float s, float w, float n, float e);
	//returns a boundingbox defined by its sides
int colision(BoundingBox A, BoundingBox B);
	//returns true if the 2 bounding boxes overlap
int colision(BoundingBox A, BoundingBox B);
	//returns true if the 2 bounding boxes overlap
float lerp(float a, float b, float f);
    //linear interpolation between a and b at 100 * f percents
void moveEntity(Entity* entity, int dt, float angle, float speed);
    //moves the entity at the given angle and speed
void movePlayer(int dt);
    //player.angle = lerp (player.angle, input_angle, 0.5);
void getAngleFromKeys();
    //assign the input angle between 0 - 2PI in function of which arrow keys are pressed


#endif
