#include "sounds.h"


void initSounds()
{
	 // Import Library 
     if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
   {
      printf("%s", Mix_GetError());
   }
}



void loadMusics() {
    Mix_AllocateChannels(32); //Allouer 32 canaux
    sounds[0] = Mix_LoadWAV("./sounds/menu.wav"); //Charger un wav dans un pointeur
    sounds[1] = Mix_LoadWAV("./sounds/game.wav");
    sounds[2] = Mix_LoadWAV("./sounds/boss.wav");
    sounds[3] = Mix_LoadWAV("./sounds/bullets.wav");
}

void playMusic(int canal, int musique) {
    Mix_VolumeChunk(sounds[musique], 100);
    Mix_PlayChannel(canal,sounds[musique], 0);
}

