#ifndef PHYSICS_H_
#define PHYSICS_H_

#include <math.h>
#include "entity.h"
#include "statistics.h"
#include "sounds.h"

//behaviors ids
#define YSINE 0
#define XSINE 1
#define ROTATE 2
#define AIMPLAYER 3 
#define AIMTGTPLAYER 4
#define GOFWD 5
#define GOBKWD 6
#define GROW 7
#define DISAPEAR 8

extern int player_goX;
extern int player_goY;

extern float player_speed;
extern float input_angle;
extern int player_holdAngle;

extern EntityList level_walls;
extern EntityList level_VFXs;	
extern BoundingBox game_box;
extern BoundingBox load_box;

extern EntityList player;

extern Entity stats_bullets[];


extern Entity stats_player;
extern int curr_frame_tick;

extern int score;


extern int debug;

//define physics elements : bounding boxes, internections

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
void doBulletsPhysics(EntityList* list,  int dt,  EntityList* targetList);
	// do all of the physics computation for the given bulletList during the time dt, and affecting the target list
void moveBulletsList(EntityList* list, int dt);
	//moves all the bullets in the list according to their given speed
void doMobsPhysics(EntityList* list, int dt, EntityList* bulletList);
	// do all of the physics computation for the given Mob list during the time dt, and affecting the target list
void doWallsPhysics(EntityList* list, int dt);
    // do all of the physics computation for the given Wall list during the time dt
void doVFXsPhysics(EntityList * list, int dt);
	// do all of the physics computation for the given VFX list during the time dt	
void entityInstantiateVFX(EntityList entity, int VFXType);
	//instantiate a vfx emited by an entity
void entityShootsBullet(EntityList entity, int dt, EntityList* bulletList);
	//manage the shooting in the dt time interval for the given entity and add the bullet to the given bulletList 
int collision(Entity A, Entity B);
	//Are the 2 entity overlaping ?
void killDeadEntity(EntityList* entity, EntityList* list);
    // check if an entity is dead and kill it
void bulletsDamageList(EntityList bulletList, EntityList* victimList);
	//browse the bullet list & damage the victimList if they touch a bullet
void doBonusesPhysics(EntityList* list, int dt);
    // do all of the physics computation for the given Bonus list during the time dt
void applyBonus(Entity bonus);
    //apply the bonus to the player
#endif
