#include "physics.h"

BoundingBox boundingBoxSWNE(float s, float w, float n, float e) {
	//returns a boundingbox defined by its sides
	Point2D sw = pointXY(w,s);
	Point2D ne = pointXY(e,n);
	BoundingBox boundingBox;
	boundingBox.sw = sw;
	boundingBox.ne = ne;
	return boundingBox;
}

float lerp(float a, float b, float f) {
    //linear interpolation between a and b at 100 * f percents
    return a * (1 - f) + (b * f);
}

void moveEntity(Entity* entity, int dt, float angle, float speed) {
    //moves the entity at the given angle and speed
    entity->anchor.x += (float)dt/200 * speed * cos(angle);
    entity->anchor.y += (float)dt/200 * speed * sin(angle);
}

void movePlayer(int dt) {
    //player.angle = lerp (player.angle, input_angle, 0.5);
    if (keyUp || keyDown || keyRight || keyLeft) {
        player.angle = atan2(lerp(sin(player.angle), sin(input_angle), 0.5),
                            lerp(cos(player.angle), cos(input_angle), 0.5));
        player_speed = lerp (player_speed, player.speed, 0.5);
    } else
        player_speed = lerp (player_speed, 0, 0.5);
        
    moveEntity(&player, dt, input_angle, player_speed);
}

void getAngleFromKeys() {
    //assign the input angle between 0 - 2PI in function of which arrow keys are pressed
    //atan 2 donne un angle à partir d'un vecteur (y,x)
    if (keyUp || keyDown || keyRight || keyLeft)
    	input_angle = atan2(keyUp - keyDown, keyRight - keyLeft);
}


void keepPlayerInBox(BoundingBox box) {
	//makes sure that the player stays inside the given bounding box (the game box)
    float d = box.sw.x - player.anchor.x - player.hitBox.sw.x;
    if (d > 0)
        player.anchor.x += d;
    else {
        d = box.ne.x - player.anchor.x - player.hitBox.ne.x;
        if (d < 0)
            player.anchor.x += d;
    }
    d = box.sw.y - player.anchor.y - player.hitBox.sw.y;
    if (d > 0)
        player.anchor.y += d;
    else {
        d = box.ne.y - player.anchor.y - player.hitBox.ne.y;
        if (d < 0)
            player.anchor.y += d;    
    }    
}

void keepPlayerOutOfWall(Entity wall) {
	//makes sure that the player stays out of the given bounding box (for the walls)
    
    float dw = wall.anchor.x + wall.hitBox.sw.x - player.anchor.x - player.hitBox.ne.x;
    float de = wall.anchor.x + wall.hitBox.ne.x - player.anchor.x - player.hitBox.sw.x;
    float ds = wall.anchor.y + wall.hitBox.sw.y - player.anchor.y - player.hitBox.ne.y;
    float dn = wall.anchor.y + wall.hitBox.ne.y - player.anchor.y - player.hitBox.sw.y;
    //we calculate the distance between the 4 sides of the player & the 4 sides of the wall
	
	if (dw < 0 && de > 0 && ds < 0 && dn > 0) {
		//if the player & wall collide

    	//minimum of the 4 distances
    	float m = fmin(fmin(-dw, de), fmin(-ds, dn))+0.001;
    	//we push the player out of the wall in the direction of the minimum distance
    	if (-dw <= m)
        	player.anchor.x += dw;
    	else if (de <= m)
        	player.anchor.x += de;
    	else if (-ds <= m)
        	player.anchor.y += ds;
    	else if (dn <= m)
        	player.anchor.y += dn;
        	
	}
}

void wallsPushPlayer() {
	//make sure the player is pushed by the walls
	EntityList tmp = level_walls;
	while (tmp != NULL) {
		keepPlayerOutOfWall(*tmp);
		tmp = tmp->next;
	}
}

