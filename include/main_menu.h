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
int Sourisx;
int Sourisy;

//game
int gameIsRunning;

void menuEvents(SDL_Event e);
    //handling menu events



#endif