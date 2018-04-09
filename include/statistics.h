#ifndef STATISTICS_H_
#define STATISTICS_H_

#include "level.h"
#include "physics.h"

// Statistics of the differents ships types
//identifiants des types d'entités
#define TYPEWALL 0
#define TYPEBONUS 1
#define TYPEMOB 2

//nombre de chaque type d'entité
#define NBWALLTYPES 0
#define NBMOBTYPES 2
#define NBBONUSTYPES 0
#define NBBULLETTYPES 0

extern Entity stats_walls[NBWALLTYPES];
extern Entity stats_mobs[NBMOBTYPES];
extern Entity stats_bonuses[NBBONUSTYPES];
extern Entity stats_bullets[NBBULLETTYPES];

void initMobsStats();
    //initialize the mob statistics array
void initBonusesStats();
void initBulletsStats();

#endif
