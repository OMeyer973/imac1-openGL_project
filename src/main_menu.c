#include "main_menu.h"



void loadMenu() {
    printf("loading menu\n");
    //load the menu

    //music
    musicMenu();

    // ---- logic reset ---- //
    level_isLoaded = 0;
    menu_isLoaded = 1;

    //input    
    int Sourisx=0;
    int Sourisy=0;

    //game
    int gameIsRunning=0;
    int gameOver = 0;
    int gameWin = 0;
    int reachedEndOfLevel = 0; 

}

void menuRender() {
    //print the menu frame
    if (gameOver) {
        gameOver = 0;
        sleep(3);
    }
    //BACKGROUND
    glPushMatrix();
    glTranslatef(screen_w/2, screen_h/2,0);
    glScalef(screen_w,screen_h,1);
    drawTexturedSquare(textures[8]);
    glPopMatrix();

    //FISHIMAC
    glPushMatrix();
    glTranslatef(screen_w/2,screen_h-100,0);
    glScalef(600,250,1);
    drawTexturedSquare(textures[11]);
    glPopMatrix();

    // NEW GAME
    glPushMatrix();
    glTranslatef(screen_w/2,screen_h/2.5,0);
    glScalef(350,50,1);
    drawTexturedSquare(textures[9]);
    glPopMatrix();

    // INSTRUCTIONS
    glPushMatrix();
    glTranslatef(screen_w/2,screen_h/6,0);
    glScalef(350,50,1);
    drawTexturedSquare(textures[10]);
    glPopMatrix();
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