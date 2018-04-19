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

#include "graphics.h"
#include "geometry.h"
#include "color.h"
#include "physics.h"
#include "statistics.h"
#include "level.h"
#include "entity.h"

//global variables
int loop = 1;

//graphics
unsigned int WINDOW_WIDTH = 1080;
unsigned int WINDOW_HEIGHT = 720;
const unsigned int BIT_PER_PIXEL = 32;
const Uint32 FRAMERATE_MILLISECONDS = 1000 / 40;

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
float game_scale = 1; // = game_h / (level_h+1), à initialiser
float border_bottom = 100;
float border_top = 100;

//textures
char* textures_dir = "img/";
GLuint textures[NBTEXTURES];

//physics
int curr_frame_tick = 0;
int prev_frame_tick = 0;

//player
Entity player;
float player_speed = 0;
int keyUp=0;
int keyDown=0;
int keyRight=0;
int keyLeft=0;
float input_angle = 0;


void update(int dt);
    //all of the game physics calculations for the time dt.
void render();
    //painting the current frame
void events(SDL_Event e);
    //events handling

int main(int argc, char** argv) {
    
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


    //initialisation des stats
    initMobsStats();

    //chargement du niveau
    makeLevelFromPPM("map/level1.ppm");
    printf("level grid : %d, %d\n",level_w, level_h);
    game_scale = game_h / (level_h+1);
    printEntity(level_mobs);
    printEntity(level_walls);

    // Remplissage du tableau de textures 
    getSurfaces(textures_dir,textures);

    initPlayer();

    //Boucle de dessin
    curr_frame_tick = SDL_GetTicks();
    resizeViewport();
    glClearColor(0.1, 0.1, 0.1 ,1.0);
    while(loop) {

        prev_frame_tick = curr_frame_tick;
        curr_frame_tick = SDL_GetTicks();
        
        update(curr_frame_tick - prev_frame_tick);

        render();

        SDL_Event e;
        events(e);

        SDL_GL_SwapBuffers();
        Uint32 elapsedTime = SDL_GetTicks() - curr_frame_tick;
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

void update(int dt) {
    //all of the game physics calculations for the time dt.
    getAngleFromKeys();
    movePlayer(dt);

}

void render() {
    //painting the current frame
    //drawing code
    glClear(GL_COLOR_BUFFER_BIT);
        
    //TODO
    //drawBG();
    //drawwalls();
    //drawbonuses();
    //drawfoes();
    //drawplayer();
    //drawVFX();
    //drawfriendlymissiles();
    //drawmobsmissiles();

    setViewToGameSpace();
        // Background
        drawBG(); 

        //dessin du joueur
        drawEntityList(&player);
        drawListHitBoxes(&player);

        // Dessin des mobs 
        drawEntityList(level_mobs);
        drawListHitBoxes(level_mobs);

    exitview();
    
    //dessin des bordures de UI
    drawBorders();
}

void events(SDL_Event e) {
    //events handling
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
                     keyUp = 1;
                     keyDown = 0;
                }
                 if (e.key.keysym.sym==274){
                     keyDown = 1;
                     keyUp = 0;
                }
                 if (e.key.keysym.sym==275){
                     keyRight = 1;
                     keyLeft = 0;
                }
                 if (e.key.keysym.sym==276){
                     keyLeft = 1;
                     keyRight = 0;
                }
                 if (e.key.keysym.sym==27){
                     loop=0;
                }

                break;

            case SDL_KEYUP:
                printf("touche levée (code = %d)\n", e.key.keysym.sym);
                
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
}