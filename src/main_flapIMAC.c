#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>  
#include <string.h>
#include <dirent.h>
#include <time.h> 

#include "main_functions.h"
#include "geometry.h"
#include "color.h"
#include "physics.h"
#include "statistics.h"
#include "level.h"
#include "entity.h"



void resizeViewport() {
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1., 1., -1., 1.);
    SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE);
}


int main(int argc, char** argv) {
    
    //mes tests de back tu peux tout commenter si tu veux (c'est pour ça que j'utilise que des // pour les commentaires ! comme ça tu peux encadrer tout ce que tu veux aps avec des /* */)
    //test de la fonction de chargement
    makeLevelFromPPM("map/test.ppm");

    //test de de l'allocation d'entity
    BoundingBox spriteBox;
    spriteBox.sw.x = 0;
    spriteBox.sw.y = 0;
    spriteBox.ne.x = 1;
    spriteBox.ne.y = 1;
    float shootAngles[4] = {0.0,1.0,20.0};

    EntityList testList = instantiateEntity(
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
