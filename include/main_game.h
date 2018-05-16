#ifndef MAIN_GAME_H_
#define MAIN_GAME_H_

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>  
#include "physics.h"
#include "graphics.h"
#include "sounds.h"

//global variables
extern int loop;

//screen layout
extern float game_ratio;

//input
extern int keyUp;
extern int keyDown;
extern int keyRight;
extern int keyLeft;

//level
extern int level_isLoaded;
extern EntityList level_walls;
extern EntityList level_mobs;
extern EntityList level_bonuses;
extern EntityList level_mobBullets;
extern EntityList level_playerBullets;
extern Entity* level_boss;

//level
int player_shooting;

void loadLevel(int i);
    //chargement du niveau i
void gameUpdate(int dt);
    //all of the game physics calculations for the time dt.
void gameRender();
    //painting the current frame
void gameEvents(SDL_Event e);
    //handling events for the game




#endif