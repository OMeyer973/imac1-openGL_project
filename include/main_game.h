#ifndef MAIN_GAME_H_
#define MAIN_GAME_H_

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>  
#include <unistd.h> 
#include "physics.h"
#include "graphics.h"
#include "sounds.h"
#include "score.h"

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
extern int player_shooting;


//game 
extern int bossTrigger; 
extern int score;


//menu
extern int menu_isLoaded;

extern int debug;

void loadLevel(int i);
    //chargement du niveau i
int gameUpdate(int dt);
    //all of the game physics calculations for the time dt. returns 1 if we can proceed to the render. 0 of not
void gameRender();
    //painting the current frame
void gameEvents(SDL_Event e);
    //handling events for the game




#endif