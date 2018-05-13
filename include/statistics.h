#ifndef STATISTICS_H_
#define STATISTICS_H_

#include "level.h"
#include "entity.h"

// Statistics of the differents ships types
//identifiants des types d'entités
#define TYPEWALL 0
#define TYPEBONUS 1
#define TYPEMOB 2
#define TYPEBOSS 3
#define TYPEEXIT 4

#define TYPEPLAYER 5
#define TYPEBULLET 6

//nombre de chaque type d'entité
#define NBWALLTYPES 1
#define NBMOBTYPES 5
#define NBBONUSTYPES 1
#define NBBULLETTYPES 4
#define NBBOSSTYPES 2



extern Entity stats_player;
extern Entity stats_walls[NBWALLTYPES];
extern Entity stats_mobs[NBMOBTYPES];
extern Entity stats_bonuses[NBBONUSTYPES];
extern Entity stats_bullets[NBBULLETTYPES];

void initPlayerStats();
    //initialize the player at the begining of a level
void initMobsStats();
    //initialize the mob statistics array
void initWallsStats();
void initBonusesStats();
void initBulletsStats();

#endif
