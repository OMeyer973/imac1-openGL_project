#ifndef MAIN_MENU_H_
#define MAIN_MENU_H_

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h> 
#include "graphics.h" 

//global variables
int loop;

//input
extern int Sourisx;
extern int Sourisy;

//game
extern int gameIsRunning;

//level
extern int level_isLoaded;

//menu
extern int menu_isLoaded;

void menuRender();
    //print the menu frame
void menuEvents(SDL_Event e);
    //handling menu events



#endif