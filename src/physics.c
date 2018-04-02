#include "physics.h"

int colision(BoundingBox A, BoundingBox B) {
	//returns true if the 2 bounding boxes overlap
	return
		(A.sw.x <= B.ne.x &&  B.sw.x <= A.ne.x &&
		 A.sw.y <= B.ne.y &&  B.sw.y <= A.ne.y);
}
