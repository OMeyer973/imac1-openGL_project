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

//------------ GENERAL FUNCTIONS ------------//

float lerp(float a, float b, float f) {
    //linear interpolation between a and b at 100 * f percents
    return a * (1 - f) + (b * f);
}

int collision(Entity A, Entity B) {
    //Are the 2 entity overlaping ?
    return (A.anchor.x + A.hitBox.sw.x < B.anchor.x + B.hitBox.ne.x &&
            A.anchor.x + A.hitBox.ne.x > B.anchor.x + B.hitBox.sw.x &&
            A.anchor.y + A.hitBox.sw.y < B.anchor.y + B.hitBox.ne.y &&
            A.anchor.y + A.hitBox.ne.y > B.anchor.y + B.hitBox.sw.y);
}

int collisionEB(Entity E, BoundingBox B) {
    //Are the 2 entity overlaping ?
    return (E.anchor.x + E.hitBox.sw.x < B.ne.x &&
            E.anchor.x + E.hitBox.ne.x > B.sw.x &&
            E.anchor.y + E.hitBox.sw.y < B.ne.y &&
            E.anchor.y + E.hitBox.ne.y > B.sw.y);
}

void moveEntity(Entity* entity, int dt, float angle, float speed) {
    //moves the entity at the given angle and speed
    entity->anchor.x += (float)dt/200 * speed * cos(angle);
    entity->anchor.y += (float)dt/200 * speed * sin(angle);
}

//------------ PLAYER FUNCTIONS ------------//

void getAngleFromKeys() {
    //assign the input angle between 0 - 2PI in function of which arrow keys are pressed
    //atan 2 donne un angle à partir d'un vecteur (y,x)
    if (player_goX || player_goY) //note : for a int --> 0 = false; anything else = true (ie -1 = true)
    	input_angle = atan2(player_goY, player_goX);
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

//------------ BULLETS FUNCTIONS ------------//

void hurtEntity(EntityList entity, float dmg) {
	// hurt the entity if touched by a bullet or else
	//if (entity->invTime <= 0) {
		entity->invTime = entity->invDelay;
		entity->hp -= dmg;
	//}
}

void killDeadEntity(EntityList* entity, EntityList* list) {
    // check if an entity is dead and kill it
	if ((*entity)->hp <= 0)
		removeEntity(entity, list);
}

void bulletDamageList(Entity* bullet, EntityList* targetList) {
	// damage the targetList if they touch a bullet
	EntityList tmpTargetList = *targetList;
	while (tmpTargetList != NULL) {		

		if (collision(*bullet, *tmpTargetList)) {
            printf("collision\n");
			hurtEntity(tmpTargetList, bullet->hp);
            bullet->hp = 0;
            printf("tmpTargetList->hp %d\n", tmpTargetList->hp );

		}
		if (tmpTargetList != NULL)	
			tmpTargetList = tmpTargetList->next;
	}
}

void doBulletsPhysics(EntityList* list, int dt, EntityList* targetList) {
	// do all of the physics computation for the given bulletList during the time dt, and affecting the target list
    EntityList tmp = *list;
    EntityList tmp2 = tmp;
    while (tmp != NULL) {
        moveEntity(tmp, dt, tmp->angle, tmp->speed);
        bulletDamageList(tmp, targetList);
        
        tmp2 = tmp;
        tmp = tmp->next;
        
        killDeadEntity(&tmp2, list);
        if (tmp2 !=NULL && !collisionEB(*tmp2, game_box)) {
            removeEntity(&tmp2, list);
        }
    }
}

//------------ MOBS (and player) FUNCTIONS ------------//

void doMobsPhysics(EntityList* list, int dt, EntityList* bulletList) {
    // do all of the physics computation for the given Mob list during the time dt, and affecting the target list
    EntityList tmp = *list;
    EntityList tmp2 = tmp;
    
    int screenPassed = 0;

    while (tmp != NULL) {
        entityShootsBullet(tmp, dt, bulletList);
        tmp2 = tmp;
        tmp = tmp->next;
        
        killDeadEntity(&tmp2, list);
        if (tmp2 != NULL) {
            if (!collisionEB(*tmp2, game_box)) {

                if (!screenPassed) {

                    removeEntity(&tmp2, list);
                } 
                else tmp = NULL; 

            } else {
                screenPassed = 1;
            }
        }
    }
}

void entityShootsBullet(EntityList entity, int dt, EntityList* bulletList) {
	//manage the shooting in the dt time interval for the given entity and add the bullet to the given bulletList 
    if (entity->shootTime < 0) {
		int i =0;
		//printf("shootanglesnb %d\n",entity->shootAnglesNb);
		for (i=0; i<entity->shootAnglesNb; i++) {
			//printf("entity->angle %f entity->shootAngles[%d] %f\n",entity->angle,i,entity->shootAngles[i]);
		    EntityList tmpEntity = copyEntity(&stats_bullets[entity->bulletType]);
		    
		    tmpEntity->anchor = pointXY(entity->anchor.x,entity->anchor.y);
		    tmpEntity->angle = entity->angle + entity->shootAngles[i];
		    addEntityStart(bulletList, tmpEntity);
		}
        entity->shootTime += entity->shootDelay;
	}
    entity->shootTime -= dt;
}

