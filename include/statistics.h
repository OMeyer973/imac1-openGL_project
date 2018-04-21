#ifndef STATISTICS_H_
#define STATISTICS_H_

#include "level.h"
#include "entity.h"

// Statistics of the differents ships types
//identifiants des types d'entités
#define TYPEWALL 0
#define TYPEBONUS 1
#define TYPEMOB 2
#define TYPEPLAYER 3
#define TYPEBULLET 4

//nombre de chaque type d'entité
#define NBWALLTYPES 1
#define NBMOBTYPES 2
#define NBBONUSTYPES 0
#define NBBULLETTYPES 1

extern Entity player;
extern Entity stats_walls[NBWALLTYPES];
extern Entity stats_mobs[NBMOBTYPES];
extern Entity stats_bonuses[NBBONUSTYPES];
extern Entity stats_bullets[NBBULLETTYPES];

void initPlayer();
    //initialize the player at the begining of a level
void initMobsStats();
    //initialize the mob statistics array
void initWallsStats();
void initBonusesStats();
void initBulletsStats();

#endif
