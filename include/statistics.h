#ifndef STATISTICS_H_
#define STATISTICS_H_

// Statistics of the differents ships types

typedef struct bulletStat {
	BoundingBox spriteBox; //size of sprite
	BoundingBox hitBox; //size of hitbox
	int textureID; //id of the texture in memory
	float speed; //speed of bullets
	int dmg; //damage caused by the bullet
} BulletStat;

typedef struct shipStat {
	BoundingBox spriteBox; //size of sprite
	int textureID; //id of the texture in memory
	BoundingBox hitBox; //size of hitbox
	int hp; //nb of health points
	
	float shootDelay; //delay between 2 shots
	int shootAnglesNb; //nb of shooting angles
	float* shootAngles; //array of shooting angles
	int burst; //is the ship shooting bursts of bullets ?
} ShipStat;


#define NBFOETYPES 6
#define NBBULLETTYPES 6

static ShipStat foeStats[NBFOETYPES]; 
	//TODO : à définir
static BulletStat bulletStats[NBBULLETTYPES]; 
	//TODO : à définir


#endif
