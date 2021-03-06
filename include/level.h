#ifndef LEVEL_H_
#define LEVEL_H_

#include <stdio.h>
#include <stdlib.h>

#include "physics.h"
#include "entity.h"
#include "statistics.h"

//Description of the level : walls, enemy ships, bulets in the air etc...

//width & height of the level grid

extern int level_w;
extern int level_h;

extern int debug;

//different entities in the level

extern EntityList level_walls;
extern EntityList level_mobs;
extern EntityList level_bonuses;
extern EntityList level_mobBulets;
extern EntityList level_playerBullets;

int makeLevelFromPPM(char* filename);
	//takes a PPM filepath as input and add objects to the 3 lists describing a level : walls list, foes list, bonus list
int addObjectToLevel(int x, int y, int obj, int type, float scale);
	//add an object to the level in correct list


int addWall(int x, int y, int subType, float scale);
int addBonus(int x, int y, int subType, float scale);
int addMob(int x, int y, int subType, float scale);
#endif
