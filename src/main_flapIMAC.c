#include "main_flapIMAC.h"


// ------------ MAIN CODE ------------ //
// *********************************** //

int main(int argc, char** argv) {
    
    // Initialisation de la SDL
    if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
        return EXIT_FAILURE;
    }

    //Initiation de la SDL Audio
    initSounds();

    // Ouverture d'une fenêtre et création d'un contexte OpenGL
    if(NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE)) {
        fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
        return EXIT_FAILURE;
            }
    SDL_WM_SetCaption("Fimac-o-fish", NULL);
            
    //initialisation des stats
    printf("initiating stats\n");
    initMobsStats();
    initWallsStats();
    initBulletsStats();
    initBonusesStats();
    initPlayerStats();
    initVFXsStats();

    // Remplissage du tableau de textures 
    getSurfaces(textures_dir,textures);

    loadMusics();
   
    //Boucle de dessin
    curr_frame_tick = SDL_GetTicks();
    resizeViewport();
    glClearColor(0.1, 0.1, 0.1 ,1.0);

    while(loop) {

        prev_frame_tick = curr_frame_tick;
        curr_frame_tick = SDL_GetTicks();
        
        
        SDL_Event e;

        muteMusic();
        if (gameIsRunning) { //we are in the game.
            if (!level_isLoaded) {
                if (currLevelId < NBLEVELS) {
                loadLevel(currLevelId);
                    // Set in-game music
                    
                }
                else {
                    gameWin = 1;
                }
            }

            gameUpdate(curr_frame_tick - prev_frame_tick);
            gameRender();
            gameEvents(e);

        } else { //we are in the menu.
            if (!menu_isLoaded) {
                loadMenu();
            }
            menuRender();
            menuEvents(e);
        }
        writeHighScore();
        SDL_GL_SwapBuffers();
        Uint32 elapsedTime = SDL_GetTicks() - curr_frame_tick;
        if(elapsedTime < FRAMERATE_MILLISECONDS) {
            SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
        }
    }
    
    // Libération des données GPU
    //glDeleteTextures(1, &textureID);

    Mix_CloseAudio(); //Fermeture de l'API 
    // Liberation des ressources associées à la SDL
    SDL_Quit();

    return EXIT_SUCCESS;   
}
