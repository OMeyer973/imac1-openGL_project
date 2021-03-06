#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>  
#include <string.h>
#include <dirent.h>
#include <time.h> 
#include <math.h> 
#include "entity.h"
#include "score.h"


extern unsigned int WINDOW_WIDTH;
extern unsigned int WINDOW_HEIGHT;
extern const unsigned int BIT_PER_PIXEL;
extern const Uint32 FRAMERATE_MILLISECONDS;

extern float screen_w;
extern float screen_h;

extern int level_w;
extern int level_h;
extern Color4f levelColors[];

extern float level_windowSpeed;
extern float level_windowOffset;
extern float level_bgSpeed;

//screen layout
extern float screen_w;
extern float screen_h;
extern float screen_ratio;
extern float game_w;
extern float game_h;
extern float game_scale;
extern float border_bottom;
extern float border_top;


//textures
#define NBTEXTURES 75
extern char* textures_dir;
extern GLuint textures[NBTEXTURES];

//sound
extern int mute; 

//game 
extern int currLevelId;

extern int debug;



void resizeViewport();
    //initial viewport setup

int getImgId(char* filename);
    // returns image id from the file name (the 2 first char)

int isLoaded (SDL_Surface* image);
    //returns 1 if the SDL-Surface is corectly loaded
int getSurfaces(char* dirPath, GLuint textureIDs[]);
    // Creates the openGL textures of the folder given and put them on the textureIDs array
    // Open and browse the folder
	
void drawTexturedSquare(GLuint textureID);
    //draws a textured square of size 1x1

void setViewToGameSpace();
    //sets the wiew to the origin of the game space
void exitview();
    //exit a certain view (game space for example)

void drawEntityList(EntityList list);
    //draws a list of entities on screen. the view must be setup to gamespace prior to this function call

void drawSquare();
    //draws a 1x1 square at the origin

void drawBoundinBox(BoundingBox box);
    //draws a bounding box on screen. the view must be setup to the box parent (entity anchor) prior to this function call

void drawEntityListHitBoxes(EntityList list);
    //draws a list of entities on screen. the view must be setup to gamespace prior to this function call

void drawBorders();
    //draws the top & bottom borders background needs to be in screen space prior to call (!not gamespace!)
void drawBG();
    //draws the background of the game space


void drawStats(EntityList player, int Id, int posY);
    // draws Health Points remaining

void drawMenu();
    //draws Menu

void drawGameOver();
    // draws Game Over Screen

void drawGameWin();
    // draws Game Win Screen

void drawMute();
    // draws volume/mute sign

void drawLevelWin();
    // draws when a level is won 

void drawCurrentLevel();
    // indicate current level
#endif