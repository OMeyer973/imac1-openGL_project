#ifndef PHYSICS_H_
#define PHYSICS_H_

#include "geometry.h"

//define physics elements : bounding boxes, internections

typedef struct boundingBox {
	//the 2 bounding box corners : north-west & south-east
	//sw.x < ne.x, sw.y < ne.y
	Point2D sw, ne;
} BoundingBox;

int colision(BoundingBox A, BoundingBox B) {
	//returns true if the 2 bounding boxes overlap
	return
		(A.sw.x <= B.ne.x &&  B.sw.x <= A.ne.x &&
		 A.sw.y <= B.ne.y &&  B.sw.y <= A.ne.y);
}


#endif
