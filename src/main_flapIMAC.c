#include "main_flapIMAC.h"



// ------------ MAIN CODE ------------ //
// *********************************** //

int main(int argc, char** argv) {
    
    // Initialize SDL
    if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
        return EXIT_FAILURE;
    }

    // Initialize audio 
    initSounds();

    // Create new window and Opengl Context
    if(NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE)) {
        fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
        return EXIT_FAILURE;
            }
    SDL_WM_SetCaption("FISHIMAC", NULL);
            
    //initialisation des stats
    if (debug) printf("initiating stats\n");
    initMobsStats();
    initWallsStats();
    initBulletsStats();
    initBonusesStats();
    initPlayerStats();
    initVFXsStats();

    // Fill tab of textures
    getSurfaces(textures_dir,textures);

    loadMusics();
   
    //Drawing loop
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
        SDL_GL_SwapBuffers();
        Uint32 elapsedTime = SDL_GetTicks() - curr_frame_tick;
        if(elapsedTime < FRAMERATE_MILLISECONDS) {
            SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
        }
    }
    
    // Free GPU
    //glDeleteTextures(1, &textureID);

    Mix_CloseAudio(); //Close Audiol'API 
    // Close SDL
    SDL_Quit();

    return EXIT_SUCCESS;   
}
