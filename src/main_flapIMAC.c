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
float level_windowSpeed = 0.02;
float level_windowOffset = 0.00;
float level_bgSpeed=0.75;

BoundingBox game_box;

EntityList level_walls;
EntityList level_mobs;
EntityList level_bonuses;
EntityList level_mobBullets;
EntityList level_playerBullets;
Entity* level_boss;

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
int gameIsRunning=1;

//player
Entity* player;
float player_speed = 0;
int player_goX=0; //1 if going right, -1 if going left
int player_goY=0; //1 if going up, -1 if going down
int player_shooting = 0;
int player_holdAngle = 0; //does the player want to stay at the angle it is ?
float input_angle = 0;

int gameOver = 0;


void loadLevel(int i);
    //chargement du niveau i
void gameUpdate(int dt);
    //all of the game physics calculations for the time dt.
void gameRender();
    //painting the current frame
void globalEvents(SDL_Event e);
    //handling global events
void gameEvents(SDL_Event e);
    //handling events for the game itself
void menuEvents(SDL_Event e);
    //handling menu events


// ------------ MAIN CODE ------------ //
// *********************************** //

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
    initWallsStats();
    initBulletsStats();
    initBonusesStats();
    printf("initiating player\n");
    initPlayerStats();

    // Remplissage du tableau de textures 
    getSurfaces(textures_dir,textures);

    loadLevel(1);

    //Boucle de dessin
    curr_frame_tick = SDL_GetTicks();
    resizeViewport();
    glClearColor(0.1, 0.1, 0.1 ,1.0);
    while(loop) {

        prev_frame_tick = curr_frame_tick;
        curr_frame_tick = SDL_GetTicks();
        
        SDL_Event e;

        
        if (gameIsRunning) { //we are in the game.
            if (!level_isLoaded) {
                loadLevel(1);
                level_isLoaded = 1;
            }

            gameUpdate(curr_frame_tick - prev_frame_tick);
            gameRender();
            gameEvents(e);

        } else { //we are in the menu.

            drawMenu();
            menuEvents(e);
        }

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


// ------------ LEVEL FUNCTIONS ------------ //
// ***************************************** //

void loadLevel(int i) {
    //chargement du niveau

    char levelPath[16];
    sprintf(levelPath, "map/level%d.ppm", i);
    
    makeLevelFromPPM(levelPath);
    printf("level grid : %d, %d\n",level_w, level_h);
    
    game_scale = game_h / (level_h+1);
    game_box = boundingBoxSWNE(0.5, 0.01, (float)level_h+0.5, (level_h+1) * game_ratio - 0.01);

    player = copyEntity(&stats_player);
    player->anchor.x = 2;
    player->anchor.y = level_h/2;

    EntityList tmp = level_mobs;
    EntityList tmp2 = tmp;
    
    //finding boss (it is the last mob)
    while (tmp != NULL) {
        tmp2 = tmp;
        tmp = tmp->next;
    }

    level_boss = tmp2;

    level_windowOffset = 0.00;
}

void gameUpdate(int dt) {
    //all of the game physics calculations for the time dt.
    //player input
    getAngleFromKeys();
    movePlayer(dt);
    keepPlayerInBox(game_box);

    //shooting physics
    if (player_shooting) {
            entityShootsBullet(player, dt, &level_playerBullets);
    }
    if (player->invTime > 0)
        player->invTime -= dt;
    
    doBonusesPhysics(&level_bonuses, dt);
    
    doWallsPhysics(&level_walls, dt);

    doMobsPhysics(&level_mobs, dt, &level_mobBullets);
    doBulletsPhysics(&level_playerBullets, dt,  &level_mobs);
 
    doBulletsPhysics(&level_mobBullets, dt,  &player);

    //moving the viewport
    if (game_box.ne.x < level_w-1) {
        level_windowOffset+=level_windowSpeed*dt;
        game_box.sw.x+=level_windowSpeed*dt;
        game_box.ne.x+=level_windowSpeed*dt;
        player->anchor.x+=level_windowSpeed*dt*level_bgSpeed;
    }

}

void gameRender() {
    //painting the current frame
    //drawing code
    glClear(GL_COLOR_BUFFER_BIT);
        
    //TODO
    //drawVFX();

    // Background
    drawBG(); 
    
    setViewToGameSpace();

        glTranslatef(-(level_windowOffset*game_scale),0,0);
        // drawing player
        drawEntityList(player);
        drawEntityListHitBoxes(player);

        // drawing mobs 
        drawEntityList(level_mobs);
        drawEntityListHitBoxes(level_mobs);

        // drawing walls
        drawEntityList(level_walls);
        drawEntityListHitBoxes(level_walls);

        // drawing bullets
        drawEntityList(level_playerBullets);
        drawEntityListHitBoxes(level_playerBullets);

        // drawing bonuses
        drawEntityList(level_bonuses);
        drawEntityListHitBoxes(level_bonuses);

        drawEntityList(level_mobBullets);
        drawEntityListHitBoxes(level_mobBullets);
        
        drawBoundinBox(game_box);

    exitview();
    
    //dessin des bordures de UI
    drawBorders();

    drawStats(player);

}


void gameEvents(SDL_Event e) {
    //gameEvents handling
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
                
                if (e.key.keysym.sym==273){ //up
                    keyUp = 1;
                    player_goY = 1;
                }
                 if (e.key.keysym.sym==274){ //down
                    keyDown = 1;
                    player_goY = -1;
                }
                 if (e.key.keysym.sym==275){ //right
                    keyRight = 1;
                    player_goX = 1;
                }
                 if (e.key.keysym.sym==276){ //left
                    keyLeft = 1;
                    player_goX = -1;
                }
                if (e.key.keysym.sym==32){ //space
                    player_shooting = 1;
                    player->shootTime = player->shootDelay*0.05; 
                    //so that the player can shoot a bit faster if he presses several times the button instead of holding it down 
                }
                if (e.key.keysym.sym==304){ //shift
                    player_holdAngle = 1;
                }
                 if (e.key.keysym.sym==27){ ///escape
                    loop=0;
                }    

                break;

            case SDL_KEYUP:
                printf("touche levée (code = %d)\n", e.key.keysym.sym);
                
                if (e.key.keysym.sym == 273){ //up
                    keyUp = 0;
                    player_goY = 0;
                    if (keyDown)
                        player_goY = -1;
                }
                 if (e.key.keysym.sym == 274){ //down
                    keyDown=0;
                    player_goY = 0;
                    if (keyUp)
                        player_goY = 1;
                }
                 if (e.key.keysym.sym == 275){ //right
                     keyRight = 0;
                     player_goX = 0;
                     if (keyLeft)
                        player_goX = -1;
                }
                 if (e.key.keysym.sym == 276){ //left
                     keyLeft = 0;
                     player_goX = 0;
                     if (keyRight)
                        player_goX = 1;
                }

                if (e.key.keysym.sym == 32){ //space
                     player_shooting = 0;
                }
                if (e.key.keysym.sym==304){ //shift
                     player_holdAngle = 0;
                }
                break;

            default:
                break;

        }
    }
}

void menuEvents(SDL_Event e) {
    //handling menu events
    while(SDL_PollEvent(&e)) {

        switch(e.type) {

            case SDL_KEYDOWN:
                 if (e.key.keysym.sym==27){ ///escape
                    loop=0;
                }    
                break;

            case SDL_QUIT:
                loop = 0;
                break;

            case SDL_VIDEORESIZE:
                WINDOW_WIDTH = e.resize.w;
                WINDOW_HEIGHT = e.resize.h;
                resizeViewport();

            case SDL_MOUSEBUTTONUP:
                if (e.button.button == SDL_BUTTON_LEFT) {
                    printf("koisss %d",Sourisy);
                    Sourisx = e.button.x; 
                    Sourisy = e.button.y; 
                    if (Sourisx>(WINDOW_WIDTH/2)-350/2 && Sourisx<(WINDOW_WIDTH/2)+350/2 && Sourisy>(WINDOW_HEIGHT/1.75)-50/2 && Sourisy<(WINDOW_HEIGHT/1.75)+50/2) 
                        gameIsRunning=1;           
                 }
            break;

            case SDL_MOUSEMOTION:
                if (e.button.x>(WINDOW_WIDTH/2)-350/2 && e.button.x<(WINDOW_WIDTH/2)+350/2 && e.button.y>(WINDOW_HEIGHT/1.75)-50/2 && e.button.y<(WINDOW_HEIGHT/1.75)+50/2 && gameIsRunning==0) {
                    glPushMatrix();
                    glTranslatef(screen_w/2,screen_h/2.5,0);
                    glScalef(355,55,1);
                    drawTexturedSquare(textures[9]);
                    glPopMatrix();        
                }                    
                break;

            default:
                break;

        }
    }
}