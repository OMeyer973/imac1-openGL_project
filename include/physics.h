#ifndef PHYSICS_H_
#define PHYSICS_H_

#include <boolean.h>
#include "geometry.h"

//define physics elements : bounding boxes, internections

typedef struct boundingBox {
	//the 2 bounding box corners : north-west & south-east
	//sw.x < ne.x, sw.y < ne.y
	point2D sw, ne;
} BoundingBox;

bool colision(BoundingBox A, BoundingBox B) {
	return
		((B.sw.y < A.sw.y && A.sw.y < B.ne.y &&
		  B.sw.x < A.sw.x && A.sw.x < B.ne.x) ||
		 
		 (B.sw.y < A.ne.y && A.ne.y < B.ne.y &&
		  B.sw.x < A.ne.x && A.ne.x < B.ne.x))
}


#endif
