#ifndef MAIN_H_
#define MAIN_H_

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>  
#include <string.h>
#include <dirent.h>
#include <time.h> 
#include <math.h>

#include "graphics.h"
#include "physics.h"
#include "statistics.h"
#include "level.h"
#include "entity.h"
#include "sounds.h"
#include "main_menu.h"
#include "main_game.h"

// ------------ VARIABLES ------------ //
// *********************************** //

//global variables
int loop = 1;

//graphics
unsigned int WINDOW_WIDTH = 1080;
unsigned int WINDOW_HEIGHT = 720;
const unsigned int BIT_PER_PIXEL = 32;
const Uint32 FRAMERATE_MILLISECONDS = 1000 / 30;

//statistics
Entity stats_player;
Entity stats_walls[NBWALLTYPES];
Entity stats_mobs[NBMOBTYPES];
Entity stats_bonuses[NBBONUSTYPES];
Entity stats_bullets[NBBULLETTYPES];
Entity stats_bosses[NBBOSSTYPES];

//level
int level_isLoaded = 0;
int level_w = 0;
int level_h = 0;
float level_windowSpeed = 0.002;
float level_windowOffset = 0.00;
float level_bgSpeed=0.75;

BoundingBox game_box;
BoundingBox load_box;

EntityList level_walls;
EntityList level_mobs;
EntityList level_bonuses;
EntityList level_mobBullets;
EntityList level_playerBullets;
Entity* level_boss;

//menu
int menu_isLoaded = 0;

//screen layout
float screen_w = 1080;
float screen_h = 720;
float screen_ratio = 1080.0/720;
float game_w = 1080;
float game_h = 600;
float game_ratio = 1080.0/600;
float game_scale = 1; // = game_h / (level_h+1), à initialiser
float border_bottom = 80;
float border_top = 40;

//textures
char* textures_dir = "img/";
GLuint textures[NBTEXTURES];

//physics
int curr_frame_tick = 0;
int prev_frame_tick = 0;

//input
int keyUp=0;
int keyDown=0;
int keyRight = 0;
int keyLeft = 0;
int Sourisx=0;
int Sourisy=0;

//player
Entity* player;
float player_speed = 0;
int player_goX=0; //1 if going right, -1 if going left
int player_goY=0; //1 if going up, -1 if going down
int player_shooting = 0;
int player_holdAngle = 0; //does the player want to stay at the angle it is ?
float input_angle = 0;

//game
int currLevelId = 0;
int gameIsRunning=0;
int gameOver = 0;
int gameWin = 0;
int reachedEndOfLevel = 0;
int bossTrigger=1;

//sound
Mix_Chunk* sounds[NBSOUNDS]; //Créer un tableau pointeur pour stocker des .WAV
int currCanal = 1; //changement de canal pour jouer des sfx les uns par dessus les autres

#endif