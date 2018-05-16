#include "main_game.h"


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
    gameOver = 0;
}

void gameUpdate(int dt) {
    //all of the game physics calculations for the time dt.
    //player input
    getAngleFromKeys();
    movePlayer(dt);
    keepPlayerInBox(game_box);

    //logic update

    if (player->hp <= 0) {
        gameOver = 1;
        musicMenu();

    }

    if (gameWin) {
        currLevelId = 0;
        gameIsRunning = 0;
        level_isLoaded = 0;
        reachedEndOfLevel = 0;
    }

    if (gameOver) {
       // DOESN'T DISPLAY GAME OVER SCREEN , NEED FIX 

       // glDisable(GL_DEPTH_TEST);
       // glClear(GL_DEPTH_BUFFER_BIT);
       // drawGameOver();
       // SDL_Delay(3000);
        currLevelId = 0;
        gameIsRunning = 0;
        level_isLoaded = 0;
        reachedEndOfLevel = 0;
    }
    if (game_box.ne.x >= level_w-1) {
        reachedEndOfLevel = 1;
    }
    
    if (reachedEndOfLevel && level_boss->hp <= 0) {
        currLevelId += 1;
        level_isLoaded = 0;
        reachedEndOfLevel = 0;
    }
    
    //physics update
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
    if (!reachedEndOfLevel) {
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

        // drawing walls
        drawEntityList(level_walls);

        // drawing player
        drawEntityList(player);

        // drawing bonuses
        drawEntityList(level_bonuses);

        // drawing mobs 
        drawEntityList(level_mobs);

        // drawing bullets
        drawEntityList(level_playerBullets);

        drawEntityList(level_mobBullets);
        
        
        drawEntityListHitBoxes(level_mobBullets);
        drawEntityListHitBoxes(level_walls);
        drawEntityListHitBoxes(player);
        drawEntityListHitBoxes(level_bonuses);
        drawEntityListHitBoxes(level_mobs);
        drawEntityListHitBoxes(level_playerBullets);
        drawBoundinBox(game_box);
        
    exitview();
    
    //dessin des bordures de UI
    drawBorders();

    drawStats(player,7);

    if (reachedEndOfLevel){
    glPushMatrix();
        glTranslatef(0,-676,0);   
        drawStats(level_boss,21);
    glPopMatrix();
    }

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
