#ifndef STATISTICS_H_
#define STATISTICS_H_

#include "level.h"
#include "entity.h"

#define NBLEVELS 2
#define MAXSHOOTANGLES 16
#define MAXBEHAVIORS 8
// Statistics of the differents ships types
//identifiants des types d'entités
#define TYPEWALL 0
#define TYPEMOB 1
#define TYPEBONUS 2
#define TYPEBOSS 3

#define TYPEPLAYER 4
#define TYPEBULLET 5

//nombre de chaque type d'entité
#define NBWALLTYPES 7
#define NBMOBTYPES 5
#define NBBONUSTYPES 2
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
