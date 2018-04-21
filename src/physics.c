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
    if (player_goX || player_goY){
        if  (!player_holdAngle) {
		    player.angle = atan2(lerp(sin(player.angle), player_goY, 0.5),
        						lerp(cos(player.angle), player_goX, 0.5));
        }
        player_speed = lerp (player_speed, player.speed, 0.5);
    } else
        player_speed = lerp (player_speed, 0, 0.5);
        
    moveEntity(&player, dt, input_angle, player_speed);
}

void getAngleFromKeys() {
    //assign the input angle between 0 - 2PI in function of which arrow keys are pressed
    //atan 2 donne un angle à partir d'un vecteur (y,x)
    if (player_goX || player_goY) //note : for a int --> 0 = false; anything else = true (ie -1 = true)
    	input_angle = atan2(player_goY, player_goX);
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

void moveBulletsList(EntityList* list, int dt) {
	//moves all the bullets in the list according to their given speed
    EntityList tmp = *list;
    while (tmp != NULL) {
        moveEntity(tmp, dt, tmp->angle, tmp->speed);
        tmp = tmp->next;
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

void entityListShootsBullet(EntityList list, EntityList* bulletList, int dt) {
	//manage the shooting in the dt time interval for the given entity list and add the bullets to the given bulletList 
	while (list != NULL) {
        list->time += dt;
        if (list->time > list->delay) {
			int i =0;
			//printf("shootanglesnb %d\n",list->shootAnglesNb);
			for (i=0; i<list->shootAnglesNb; i++) {
				//printf("list->angle %f list->shootAngles[%d] %f\n",list->angle,i,list->shootAngles[i]);
			    EntityList tmpEntity = copyEntity(&stats_bullets[list->bulletType]);
			    
			    tmpEntity->anchor = pointXY(list->anchor.x,list->anchor.y);
			    tmpEntity->angle = list->angle + list->shootAngles[i];
			    addEntityStart(bulletList, tmpEntity);
			}
            list->time -= list->delay;
		}
		list = list->next;
	}
}

int collision(Entity A, Entity B) {
	//Are the 2 entity overlaping ?
	return (A.anchor.x + A.hitBox.sw.x < B.anchor.x + B.hitBox.ne.x &&
			A.anchor.x + A.hitBox.ne.x > B.anchor.x + B.hitBox.sw.x &&
			A.anchor.y + A.hitBox.sw.y < B.anchor.y + B.hitBox.ne.y &&
			A.anchor.y + A.hitBox.ne.y > B.anchor.y + B.hitBox.sw.y);
}

void bulletsDamageList(EntityList bulletList, EntityList* victimList) {
	//browse the bullet list & damage the victimList if they touch a bullet
	while (bulletList != NULL) {		
		EntityList tmpVictimList = *victimList;
		while (tmpVictimList != NULL) {		

			if (collision(*bulletList, *tmpVictimList)) {
				printf("collision\n");
				tmpVictimList->hp -= bulletList->hp;
				if (tmpVictimList->hp <= 0)
					removeEntity(victimList, &tmpVictimList);			
			}
			if (tmpVictimList != NULL)	
				tmpVictimList = tmpVictimList->next;
		}
	if (bulletList != NULL)	
		bulletList = bulletList->next;
	}
}