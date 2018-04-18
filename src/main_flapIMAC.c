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
unsigned int WINDOW_WIDTH = 600;
unsigned int WINDOW_HEIGHT = 400;
const unsigned int BIT_PER_PIXEL = 32;
const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

//statistics
Entity stats_walls[NBWALLTYPES];
Entity stats_mobs[NBMOBTYPES];
Entity stats_bonuses[NBBONUSTYPES];
Entity stats_bullets[NBBULLETTYPES];

//level
int level_w = 0;
int level_h = 0;

EntityList level_walls;
EntityList level_mobs;
EntityList level_bonuses;
EntityList level_mobBulets;
EntityList level_playerBulets;

//screen layout
float screen_w = 1080;
float screen_h = 720;
float screen_ratio = 16/9;
float game_w = 1080;
float game_h = 520;
float border_bottom = 100;
float border_top = 100;


//textures
char* textures_dir = "img/";
GLuint textures[NBTEXTURES];

//player
float xplayer = -3, yplayer = 0;
int keyUp=0;
int keyDown=0;
int keyRight=0;
int keyLeft=0;

void controlsMouvment() {
    if ((yplayer>=-4. && yplayer<=4. && xplayer>=-4. && xplayer<=4.))        
        if (keyUp)
            yplayer+=0.1;
        if (keyDown)
            yplayer-=0.1;
        if (keyRight)
            xplayer+=0.1;
        if (keyLeft)
            xplayer-=0.1;

    else if (yplayer>4)
        yplayer=4;
    else if (yplayer<-4)
        yplayer=-4;

    else if (xplayer>4)
        xplayer=4;
    else if (xplayer<-4)
        xplayer=-4;
}

int main(int argc, char** argv) {
    //mes tests de back tu peux tout commenter si tu veux (c'est pour ça que j'utilise que des // pour les commentaires ! comme ça tu peux encadrer tout ce que tu veux aps avec des /* */)
    
    //tests des stats
    initMobsStats();
    //printEntity(&(stats_mobs[0]));
    //printEntity(&(stats_mobs[1]));

    //test de la fonction de chargement
    makeLevelFromPPM("map/level1.ppm");
    printf("level grid : %d, %d\n",level_w, level_h);

    printEntity(level_mobs);
    printEntity(level_walls);
    //test de de l'allocation d'entity
    /*
    Point2D anchor;
    anchor.x = 3;
    anchor.y = 4;
    BoundingBox spriteBox;
    spriteBox.sw.x = 0;
    spriteBox.sw.y = 0;
    spriteBox.ne.x = 1;
    spriteBox.ne.y = 1;
    float shootAngles[4] = {0.0,1.0,20.0};

    EntityList testList = instantiateEntity(
        anchor,
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

    //fin de mes tests lol

    
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
    SDL_WM_SetCaption("Fimac-o-fish", NULL);

    // Remplissage du tableau de textures 
    getSurfaces(textures_dir,textures);

    //Boucle de dessin
    int loop = 1;
    resizeViewport();
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


        setViewToGameSpace();
            // Background
            drawBG(); 
            // Dessin des mobs 
            drawEntityList(level_mobs);


            // Dessin du joueur

            controlsMouvment();
        exitview();
        
        //dessin des bordures de UI
        drawBorders();

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

                    case SDL_KEYDOWN:
                    printf("touche pressée (code = %d)\n", e.key.keysym.sym);
                    
                    if (e.key.keysym.sym==273){
                         keyUp=1;
                    }
                     if (e.key.keysym.sym==274){
                         keyDown=1;
                    }
                     if (e.key.keysym.sym==275){
                         keyRight=1;
                    }
                     if (e.key.keysym.sym==276){
                         keyLeft=1;
                    }
                     if (e.key.keysym.sym==27){
                         loop=0;
                    }

                    break;

                         case SDL_KEYUP:
                    printf("touche pressée (code = %d)\n", e.key.keysym.sym);
                    
                    if (e.key.keysym.sym==273){
                         keyUp=0;
                    }
                     if (e.key.keysym.sym==274){
                         keyDown=0;
                    }
                     if (e.key.keysym.sym==275){
                         keyRight=0;
                    }
                     if (e.key.keysym.sym==276){
                         keyLeft=0;
                    }
                    break;




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
    
}
