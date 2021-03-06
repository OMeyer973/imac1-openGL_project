#ifndef STATISTICS_H_
#define STATISTICS_H_

#include "level.h"
#include "entity.h"

#define NBLEVELS 3
#define MAXSHOOTANGLES 16
#define MAXBEHAVIORS 8
// Statistics of the differents ships types
// ids of each entity type
#define TYPEWALL 0
#define TYPEMOB 1
#define TYPEBONUS 2
#define TYPEBOSS 3

#define TYPEPLAYER 4
#define TYPEBULLET 5
#define TYPEVFX 6

//number of every entity type
#define NBWALLTYPES 7
#define NBMOBTYPES 5
#define NBBONUSTYPES 5
#define NBBULLETTYPES 5
#define NBVFXTYPES 2

#define VFXHIT 0
#define VFXDEAD 1

extern Color4f levelColors[];
extern Entity stats_player;
extern Entity stats_walls[NBWALLTYPES];
extern Entity stats_mobs[NBMOBTYPES];
extern Entity stats_bonuses[NBBONUSTYPES];
extern Entity stats_bullets[NBBULLETTYPES];
extern Entity stats_VFXs[NBVFXTYPES];


void initLevelsColors();
	//initialyse the list of the levels bg colors    
void initPlayerStats();
    //initialize the player at the begining of a level
void initMobsStats();
    //initialize the mob statistics array
void initWallsStats();
void initBonusesStats();
void initBulletsStats();
void initVFXsStats();

#endif
