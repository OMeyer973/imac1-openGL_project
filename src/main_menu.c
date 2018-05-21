#include "main_menu.h"



void loadMenu() {
    printf("loading menu\n");
    //load the menu

    //music
    Mix_HaltChannel(-1);
    playMusic(MUSICCANAL,0,1);


    // ---- logic reset ---- //
    level_isLoaded = 0;
    menu_isLoaded = 1;

    //input    
    Sourisx=0;
    Sourisy=0;

    //game
    gameIsRunning=0;
    reachedEndOfLevel = 0; 

}

void menuRender() {
    //print the menu frame
    if (!instructions){
    if (gameOver) {
        gameOver = 0;
        sleep(3);
    }
    if (gameWin) {
        printf("YOU WIIIN\n");
        gameWin = 0;
        sleep(3);
    }
    //BACKGROUND
    glPushMatrix();
    glTranslatef(screen_w/2, screen_h/2,0);
    glScalef(screen_w,screen_h,1);
    drawTexturedSquare(textures[13]);
    glPopMatrix();

    //FISHIMAC
    glPushMatrix();
    glTranslatef(screen_w/2,screen_h-100,0);
    glScalef(600,250,1);
    drawTexturedSquare(textures[16]);
    glPopMatrix();

    //BEST SCORE

    glPushMatrix();
    glTranslatef(screen_w/2-5,screen_h-200,0);
    glScalef(250,60,1);    
    drawTexturedSquare(textures[19]);
    glPopMatrix();

    //NUMERAL BEST SCORE
    glPushMatrix();
    glTranslatef(screen_w/2+5,screen_h-78,0);
    glScalef(1.5,2.5,1);
    drawHighScore();
    glPopMatrix();

    //LAST SCORE

    glPushMatrix();
    glTranslatef(screen_w/2-5,screen_h-240,0);
    glScalef(180,30,1);    
    drawTexturedSquare(textures[8]);
    glPopMatrix();

    //NUMERAL LAST SCORE
    glPushMatrix();
    glTranslatef(screen_w/2+35,screen_h-128,0);
    glScalef(1,1.6,1);
    drawScore(score,-70);
    glPopMatrix();


    // NEW GAME
    glPushMatrix();
    glTranslatef(screen_w/2,screen_h/2.5,0);
    glScalef(350,50,1);
    drawTexturedSquare(textures[15]);
    glPopMatrix();

    // INSTRUCTIONS
    glPushMatrix();
    glTranslatef(screen_w/2,screen_h/6,0);
    glScalef(350,50,1);
    drawTexturedSquare(textures[10]);
    glPopMatrix();

    // HOVER NEW GAME
    if (Sourisx>(WINDOW_WIDTH/2)-350/2 && Sourisx<(WINDOW_WIDTH/2)+350/2 && Sourisy>(WINDOW_HEIGHT/1.75)-50/2 && Sourisy<(WINDOW_HEIGHT/1.75)+50/2 && gameIsRunning==0) {
        glPushMatrix();
            glTranslatef(screen_w/2,screen_h/2.5,0);
            glScalef(355,55,1);
            drawTexturedSquare(textures[15]);
        glPopMatrix();        
                }  

    // HOVER INSTRUCTIONS
  if (Sourisx>(WINDOW_WIDTH/2)-350/2 && Sourisx<(WINDOW_WIDTH/2)+350/2 && (float)(Sourisy)/(float)(WINDOW_HEIGHT)>0.80 && (float)(Sourisy)/(float)(WINDOW_HEIGHT)<0.85) {
        glPushMatrix();
            glTranslatef(screen_w/2,screen_h/6,0);
            glScalef(355,55,1);
            drawTexturedSquare(textures[10]);
        glPopMatrix();         
                 }
}
// Ecran d'instructions 
   if(instructions)
      {
       glPushMatrix();
       glTranslatef(screen_w/2, screen_h/2,0);
       glScalef(screen_w,screen_h,1);
       drawTexturedSquare(textures[7]);
       glPopMatrix();
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
                    Sourisx = e.button.x; 
                    Sourisy = e.button.y; 
                    if (Sourisx>(WINDOW_WIDTH/2)-350/2 && Sourisx<(WINDOW_WIDTH/2)+350/2 && Sourisy>(WINDOW_HEIGHT/1.75)-50/2 && Sourisy<(WINDOW_HEIGHT/1.75)+50/2) 
                        gameIsRunning=1;           
                 }

                  if (Sourisx>(WINDOW_WIDTH/2)-350/2 && Sourisx<(WINDOW_WIDTH/2)+350/2 && (float)(Sourisy)/(float)(WINDOW_HEIGHT)>0.80 && (float)(Sourisy)/(float)(WINDOW_HEIGHT)<0.85) {
                   
                        instructions=1;   
        
                 }

                 if ((float)(Sourisx)/(float)(WINDOW_HEIGHT)>1.11 &&(float)(Sourisx)/(float)(WINDOW_HEIGHT)<1.39 && (float)(Sourisy)/(float)(WINDOW_HEIGHT)>0.02 && (float)(Sourisy)/(float)(WINDOW_HEIGHT)<0.16 && instructions==1) {
                   
                        instructions=0;   
        
                 }

                 break;

            case SDL_MOUSEMOTION:
                Sourisx=e.button.x;
                Sourisy=e.button.y;  
                break;

            default:
                break;

        }
    }
}