#include "physics.h"

BoundingBox boundingBoxSWNE(float s, float w, float n, float e) {
	//returns a boundingbox defined by its sides
	Point2D sw = pointXY(s,w);
	Point2D ne = pointXY(n,e);
	BoundingBox boundingBox;
	boundingBox.sw = sw;
	boundingBox.ne = ne;
	return boundingBox;
}

int colision(BoundingBox A, BoundingBox B) {
	//returns true if the 2 bounding boxes overlap
	return
		(A.sw.x <= B.ne.x &&  B.sw.x <= A.ne.x &&
		 A.sw.y <= B.ne.y &&  B.sw.y <= A.ne.y);
}