#ifndef SOUNDS_H_
#define SOUNDS_H_

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

#define MUSICCANAL 0
#define SFXCANAL 1

#define NBSOUNDS 5  
#define MAXVOLUME 100

//Game options 
extern int currLevelId;
extern int gameOver;
extern int gameWin;
extern int reachedEndOfLevel;
extern int gameIsRunning;

//sound
extern Mix_Chunk* sounds[NBSOUNDS];
extern int currCanal;
extern int mute;


void initSounds();
	 // Import Library 
void loadMusics();
    //loads the differents sound files on memory 
void playMusic(int canal, int musique, float volume) ;
    //plays a given music on a given canal
void muteMusic();


#endif
