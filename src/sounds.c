#include "sounds.h"


void initSounds()
{
	 // Import Library 
     if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
   {
      printf("%s", Mix_GetError());
   }
}

void musicBoss()
{ Mix_CloseAudio();
	initSounds();
  Mix_Music *musicboss;
  musicboss = Mix_LoadMUS("./sounds/boss.mp3"); 
  Mix_PlayMusic(musicboss, -1);
}

void musicGame()
{ Mix_CloseAudio();
  initSounds();
  Mix_Music *musicgame;
  musicgame = Mix_LoadMUS("./sounds/game.mp3"); 
  Mix_PlayMusic(musicgame, -1);
}


void musicMenu()
{ Mix_CloseAudio();
  initSounds();
  Mix_Music *musicmenu;
  musicmenu = Mix_LoadMUS("./sounds/menu.mp3"); 
  Mix_PlayMusic(musicmenu, -1);
}
