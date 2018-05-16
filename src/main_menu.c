#include "main_menu.h"





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