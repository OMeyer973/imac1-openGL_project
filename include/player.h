#ifndef PLAYER_H_
#define PLAYER_H_

#include "statistics.h"

//Player controls (inputs & movement variables)

/*
control keys : up - down - shoot - (shield) [player 1, 2]
ship caracteristics : speed - shooting rate - shooting speed - shooting angles
sprites : ship - bullets - (shield) - (thrust flames)
*/

typedef struct controls {
	//player keys
	char up, down, left, right, shoot, shield;
} Controls;

static Controls playerControls;
	//TODO : initialiser les valeurs par défaut

static ShipStat playerShip; //stats of the player ship
	//TODO : initialiser les valeurs par défaut
static BulletStat playerBullet; //stats of the bulets shot by the player
	//TODO : initialiser les valeurs par défaut

#endif
