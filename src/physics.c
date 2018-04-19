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

int colision(BoundingBox A, BoundingBox B) {
	//returns true if the 2 bounding boxes overlap
	return
		(A.sw.x <= B.ne.x &&  B.sw.x <= A.ne.x &&
		 A.sw.y <= B.ne.y &&  B.sw.y <= A.ne.y);
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



void clampPlayerToGame() {
	//makes sure that the player stays inside the game space
    float d = game_box.sw.x - player.anchor.x - player.hitBox.sw.x;
    if (d > 0)
        player.anchor.x += d;
    else {
        d = game_box.ne.x - player.anchor.x - player.hitBox.ne.x;
        if (d < 0)
            player.anchor.x += d;
    }
    d = game_box.sw.y - player.anchor.y - player.hitBox.sw.y;
    if (d > 0)
        player.anchor.y += d;
    else {
        d = game_box.ne.y - player.anchor.y - player.hitBox.ne.y;
        if (d < 0)
            player.anchor.y += d;    
    }    
}
