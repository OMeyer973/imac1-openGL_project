#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>  
#include <string.h>
#include <dirent.h>
#include <time.h> 

#include "graphics.h"
#include "geometry.h"
#include "color.h"
#include "physics.h"
#include "statistics.h"
#include "level.h"
#include "entity.h"

//global variables
//graphics
unsigned int WINDOW_WIDTH = 1;
unsigned int WINDOW_HEIGHT = 1;
const unsigned int BIT_PER_PIXEL = 32;
const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

//statistics
Entity stats_mobs[NBMOBTYPES];
Entity stats_bounses[NBBONUSTYPES];
Entity stats_bullets[NBBULLETTYPES];

//level
int level_w = 0;
int level_h = 0;

EntityList level_walls;
EntityList level_mobs;
EntityList level_bonuses;
EntityList level_mobBulets;
EntityList level_playerBulets;




int main(int argc, char** argv) {
    //mes tests de back tu peux tout commenter si tu veux (c'est pour ça que j'utilise que des // pour les commentaires ! comme ça tu peux encadrer tout ce que tu veux aps avec des /* */)
    //test de la fonction de chargement
    makeLevelFromPPM("map/test.ppm");
    printf("level grid : %d, %d\n",level_w, level_h);
    //test de de l'allocation d'entity
    /*
    Point2D center;
    center.x = 3;
    center.y = 4;
    BoundingBox spriteBox;
    spriteBox.sw.x = 0;
    spriteBox.sw.y = 0;
    spriteBox.ne.x = 1;
    spriteBox.ne.y = 1;
    float shootAngles[4] = {0.0,1.0,20.0};

    EntityList testList = instantiateEntity(
        center,
        spriteBox,
        0,
        spriteBox,
        1,
        2,
        100,
        3,
        3.1,
        4.1,
        4,
        shootAngles);

    printEntity(testList);
    EntityList testList2 = copyEntity(testList);
    testList2->textureID = 2;

    EntityList testList3 = copyEntity(testList);
    testList3->textureID = 3;

    EntityList testList4 = copyEntity(testList);
    testList4->textureID = 4;


    addEntityEnd(&testList, testList2);
    addEntityStart(&testList, testList4);
    addEntityEnd(&testList, testList3);
    printEntity(testList);

    removeEntity(&(testList->next->next->next));
    printEntity(testList);
    */
    //tests des stats
    initMobsStats();
    printEntity(&(stats_mobs[0]));
    printEntity(&(stats_mobs[1]));

    //fin de mes tests lol

    /*
    //vrai code
    // Initialisation de la SDL
    if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
        return EXIT_FAILURE;
    }

    // Ouverture d'une fenêtre et création d'un contexte OpenGL
    if(NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE)) {
        fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
        return EXIT_FAILURE;
    }
    SDL_WM_SetCaption("flapIMAC", NULL);
    resizeViewport();


    //Boucle de dessin
    int loop = 1;
    glClearColor(0.1, 0.1, 0.1 ,1.0);
    while(loop) {

        Uint32 startTime = SDL_GetTicks();

        // Code de dessin
        glClear(GL_COLOR_BUFFER_BIT);
        //TODO
        //drawBG();
        //drawwalls();
        //drawbonuses();
        //drawfoes();
        //drawplayer();
        //drawVFX();
        //drawfriendlymissiles();
        //drawfoemissiles();

        // Fin du code de dessin

        SDL_Event e;
        while(SDL_PollEvent(&e)) {

            switch(e.type) {

                case SDL_QUIT:
                    loop = 0;
                    break;

                case SDL_VIDEORESIZE:
                    WINDOW_WIDTH = e.resize.w;
                    WINDOW_HEIGHT = e.resize.h;
                    resizeViewport();

                default:
                    break;
            }
        }

        SDL_GL_SwapBuffers();
        Uint32 elapsedTime = SDL_GetTicks() - startTime;
        if(elapsedTime < FRAMERATE_MILLISECONDS) {
            SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
        }
    }
    

    // Libération des données GPU
    //glDeleteTextures(1, &textureID);

    // Liberation des ressources associées à la SDL
    SDL_Quit();

    return EXIT_SUCCESS;
    */
}
