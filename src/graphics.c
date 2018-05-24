#include "graphics.h"


void resizeViewport() {
    //initial viewport setup
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, screen_w, 0, screen_h);
    SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE);
}


int getImgId(char* filename) {
    // returns image id from the file name (the 2 first char)

    if ('0' <= filename[0] && filename[0] <= '9' &&
    	'0' <= filename[1] && filename[1] <= '9') {
        return 10 * (filename[0] - '0') + filename[1] - '0';
    }
    // Otherwise returns -1
    return -1;
}

int isLoaded (SDL_Surface* image) {
    //returns 1 if the SDL-Surface is corectly loaded
    if (image == NULL) {
        printf("Texture loading failed\n");
        SDL_Quit();
        return 0;
    }
    return 1;
}

int getSurfaces(char* dirPath, GLuint textureIDs[]) {
    // Creates the openGL textures of the folder given and put them on the textureIDs array
    // Open and browse the folder  
    DIR *d;
    struct dirent *dir;
    d = opendir(dirPath);

    if (!d) {
        printf("erreur à l'ouverture du dossier\n");
        return 0;
    }

    // Loads and treats textures
    SDL_Surface* textures[NBTEXTURES];
    glGenTextures(NBTEXTURES, textureIDs);    

    int i = 0;

    //Browse textures folder
    while ((dir = readdir(d)) != NULL) {
        //we want to target our files textures (not the . nor..)
        if (strcmp(dir->d_name, "..") != 0 && strcmp(dir->d_name, ".") != 0) {
            
            i = getImgId(dir->d_name);
            
            //strtmp : full path of the image for loading 
            char strTmp[50];
            strcpy(strTmp, dirPath);
            strcat(strTmp, dir->d_name);
            if (debug) printf("Loading tex %s\n", strTmp);
            
            textures[i] = IMG_Load(strTmp);
            if (!isLoaded(textures[i])) return 0;   
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glBindTexture(GL_TEXTURE_2D, textureIDs[i]);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

            // sends the textures data to the graphic processor
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RGBA,
                textures[i]->w,
                textures[i]->h,
                0,
                GL_RGBA,
                GL_UNSIGNED_BYTE,
                textures[i]->pixels);
            
            // Free CPU data
            SDL_FreeSurface(textures[i]);
            glBindTexture(GL_TEXTURE_2D, 0);
        }   
    }
    closedir(d);
    return 1;
    }


void drawTexturedSquare(GLuint textureID) {
    //draws a textured square of size 1x1
    glEnable(GL_TEXTURE_2D);
     glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, textureID);        
        glBegin(GL_QUADS);
            glTexCoord2f(0, 1);
            glVertex2f(-0.5,-0.5);
            glTexCoord2f(0, 0);
            glVertex2f(-0.5,0.5);
            glTexCoord2f(1, 0);
            glVertex2f(0.5,0.5);
            glTexCoord2f(1, 1);
            glVertex2f(0.5,-0.5);
        glEnd();
    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}


void setViewToGameSpace() {
    //sets the view to the origin of the game space
    glPushMatrix();
        glTranslatef(0, border_bottom, 0);
}

void exitview() {
    //exit a certain view (game space for example)
    glPopMatrix();
}

void drawEntityList(EntityList list) {
    //draws a list of entities on screen. the view must be setup to gamespace prior to this function call
    while(list != NULL) {
        if (list->invTime > 0) {
            float g = 255 -50 - 150 * list->color.g * list->invTime / list->invDelay; 
            float b = 255 -50 - 150 * list->color.b * list->invTime / list->invDelay; 
            float a = list->invTime / list->invDelay;
            if (a <= list->color.a) a = list->color.a;

            glColor4ub(255,g,b,255 * a);
        } else {
            glColor4ub(255 * list->color.r, 255 * list->color.g, 255 * list->color.b, 255 * list->color.a);
        }
        glPushMatrix();
            glTranslatef(
                (list->anchor.x + (list->spriteBox.ne.x+list->spriteBox.sw.x)/2) * game_scale,
                (list->anchor.y + (list->spriteBox.ne.y+list->spriteBox.sw.y)/2) * game_scale, 0);
            glRotatef(list->angle / 2 / M_PI * 360,0,0,1);
            glScalef(
                (list->spriteBox.ne.x-list->spriteBox.sw.x) * game_scale,
                (list->spriteBox.ne.y-list->spriteBox.sw.y) * game_scale,1);
            drawTexturedSquare(textures[list->textureID]);
        glPopMatrix();

        glColor4ub(255,255,255,255);
        list = list->next;
    }       
}

void drawSquare() {
    // draws a 1x1 square centred on the origin
    glBegin(GL_QUADS);
        glVertex2f(-0.5,-0.5);
        glVertex2f(-0.5,0.5);
        glVertex2f(0.5,0.5);
        glVertex2f(0.5,-0.5);
    glEnd();
}

void drawBoundinBox(BoundingBox box) {
    //draws a bounding box on screen. the view must be setup to the box parent (entity anchor) prior to this function call
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3ub(255, 0, 0);
    glPushMatrix();
        glTranslatef(
            (box.ne.x+box.sw.x) / 2 * game_scale,
            (box.ne.y+box.sw.y) / 2 * game_scale, 0);
        glScalef(
            (box.ne.x-box.sw.x) * game_scale,
            (box.ne.y-box.sw.y) * game_scale,1);
        drawSquare();
    glPopMatrix();
    glColor3ub(255, 255, 255);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void drawEntityListHitBoxes(EntityList list) {
    //draws a list of entities bounding boxes. the view must be setup to gamespace prior to this function call
    while(list != NULL) {
        glPushMatrix();
            glTranslatef(
                list->anchor.x * game_scale,
                list->anchor.y * game_scale, 0);
                drawBoundinBox(list->hitBox);
            drawSquare();
        glPopMatrix();
        list = list->next;
    }
}

void drawBorders() {
    //draws the top & bottom borders -> needs to be in screen space prior to call (!not gamespace!)
    glPushMatrix();
        glTranslatef(screen_w*1.5, screen_h/2,0);
        glTranslatef(-(int)(level_windowOffset*game_scale+screen_w)%(int)(screen_w*2),0,0);
        glScalef(screen_w, screen_h,1);
        drawTexturedSquare(textures[12]);
        drawTexturedSquare(textures[11]);
    glPopMatrix();
    glPushMatrix();
        glTranslatef((int)(-level_windowOffset*game_scale)%(int)(screen_w*2),0,0);
        glTranslatef(screen_w*1.5, screen_h/2,0);
        glScalef(-screen_w, screen_h,1);
        drawTexturedSquare(textures[12]);
        drawTexturedSquare(textures[11]);
    glPopMatrix();
}

void drawBG() {
    //draws the background of the game space
    glPushMatrix();
        glTranslatef(screen_w*1.5, screen_h/2,0);
        glTranslatef(-(int)((level_windowOffset*game_scale*(level_bgSpeed))+screen_w)%(int)(screen_w*2),0,0);
        glScalef(screen_w, screen_h,1);
        drawTexturedSquare(textures[14]);
    glPopMatrix();

    glPushMatrix();
        glTranslatef((int)(-level_windowOffset*game_scale*(level_bgSpeed))%(int)(screen_w*2),0,0);
        glTranslatef(screen_w*1.5, screen_h/2,0);
        glScalef(-screen_w, screen_h,1);
        drawTexturedSquare(textures[14]);
    glPopMatrix();
}

void drawStats(EntityList player, int Id, int posY) {
    int j=0;
    int maxHeart=(player->hp)/10;
    glPushMatrix();     
        for (maxHeart=(player->hp)/10; maxHeart>0; maxHeart--) {
            glPushMatrix(); 
                glTranslatef(50+j,posY,0);
                glScalef(20, 20,1);
                drawTexturedSquare(textures[Id]);
            glPopMatrix();
            j+=20; 
        }
    glPopMatrix();
}

void drawGameOver(){
    // GAME OVER
      glPushMatrix();
        glTranslatef(screen_w/2,screen_h/2.5+50,0);
        glScalef(650,650,1);
        drawTexturedSquare(textures[17]);
    glPopMatrix();
}


void drawGameWin() {
    // GAME WIN
    glPushMatrix();
        glTranslatef(screen_w/2,screen_h/2.5+50,0);
        glScalef(650,650,1);
        drawTexturedSquare(textures[18]);
    glPopMatrix();
}

void drawMute() {
    glPushMatrix(); 
        glTranslatef(1040,680,0);
        glScalef(60, 60,1);
        if (mute==0){    
        drawTexturedSquare(textures[5]);
        }
        if (mute==1){
        drawTexturedSquare(textures[6]);
        }
    glPopMatrix();

}

void drawLevelWin() {
    // LEVEL WIN
    glPushMatrix();
        glTranslatef(screen_w/2,screen_h/2.5+50,0);
        glScalef(650,350,1);
        drawTexturedSquare(textures[4]);
    glPopMatrix();
}

void drawCurrentLevel() {
    // LEVEL WIN
    glPushMatrix();
        glTranslatef(screen_w/2+470,screen_h/2.5+400,0);
        glScalef(60,30,1);
        drawTexturedSquare(textures[3]);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(screen_w/2+510,screen_h/2.5+400,0);
        glScalef(20,30,1);
        drawNumber(currLevelId+1); 
    glPopMatrix();
}