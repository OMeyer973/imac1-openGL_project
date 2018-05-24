#ifndef MAIN_MENU_H_
#define MAIN_MENU_H_

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h> 
#include <unistd.h> 
#include "graphics.h" 
#include "sounds.h" 
#include "score.h"

//global variables
int loop;

//input
extern int Sourisx;
extern int Sourisy;

//game
extern int gameIsRunning;
extern int gameOver;
extern int gameWin;
extern int reachedEndOfLevel; 

//level
extern int level_isLoaded;

//menu
extern int menu_isLoaded;
extern int instructions;

//sound
extern int mute;

//debug
extern int debug;

void loadMenu();
    //load the menu
void menuRender();
    //print the menu frame
void menuEvents(SDL_Event e);
    //handling menu events




#endif