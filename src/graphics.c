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
    //retourne l'id de l'image à partir de son nom de fichier (inscrit dans les 2 premiers caractères)
    //si les 2 premiers caractère sont des entier, on calcule et on retourne
    if ('0' <= filename[0] && filename[0] <= '9' &&
    	'0' <= filename[1] && filename[1] <= '9') {
        return 10 * (filename[0] - '0') + filename[1] - '0';
    }
    //sinon on retourne -1
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
	//créé les surfaces texturées openGL des textures du dossier donné en entrée et les retourne le tableaux textureIDs
	//ouverture et parcours du dossier contenant les textures    
    DIR *d;
    struct dirent *dir;
    d = opendir(dirPath);

    if (!d) {
        printf("erreur à l'ouverture du dossier\n");
        return 0;
    }

    // Chargement et traitement de la texture
    SDL_Surface* textures[NBTEXTURES];
    glGenTextures(NBTEXTURES, textureIDs);    

    int i = 0;

    //parcours du dossier des textures
    while ((dir = readdir(d)) != NULL) {
        //on veut juste cibler nos fichiers textures (pas le . et ..)
        if (strcmp(dir->d_name, "..") != 0 && strcmp(dir->d_name, ".") != 0) {
            
            i = getImgId(dir->d_name);
            
            //strtmp : chemin complet de l'image pour chargement
            char strTmp[50];
            strcpy(strTmp, dirPath);
            strcat(strTmp, dir->d_name);
            printf("Loading tex %s\n", strTmp);
            
            textures[i] = IMG_Load(strTmp);
            if (!isLoaded(textures[i])) return 0;   
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glBindTexture(GL_TEXTURE_2D, textureIDs[i]);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

            // Envoie des données texture à la carte graphique
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
            
            // Libération des données CPU
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
            float c = 255 -50 - 150 * list->invTime / list->invDelay; 
            glColor3ub(255,c,c);
        }

        glPushMatrix();
            glTranslatef(
                (list->anchor.x + (list->spriteBox.ne.x+list->spriteBox.sw.x)/2) * game_scale,
                (list->anchor.y + (list->spriteBox.ne.y+list->spriteBox.sw.y)/2) * game_scale, 0);
            glScalef(
                (list->spriteBox.ne.x-list->spriteBox.sw.x) * game_scale,
                (list->spriteBox.ne.y-list->spriteBox.sw.y) * game_scale,1);
            glRotatef(list->angle / 2 / M_PI * 360,0,0,1);
            drawTexturedSquare(textures[list->textureID]);
        glPopMatrix();

        glColor3ub(255,255,255);
        list = list->next;
    }       
}

void drawSquare() {
    //dessine un carré de 1x1 centré sur l'origine
    glBegin(GL_QUADS);
        glVertex2f(-0.5,-0.5);
        glVertex2f(-0.5,0.5);
        glVertex2f(0.5,0.5);
        glVertex2f(0.5,-0.5);
    glEnd();
}

void drawBoundinBox(BoundingBox box) {
    //draws a bounding box on screen. the view must be setup to the box parent (entity anchor) prior to this function call
    glColor3ub(255, 0, 0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPushMatrix();
        glTranslatef(
            (box.ne.x+box.sw.x) / 2 * game_scale,
            (box.ne.y+box.sw.y) / 2 * game_scale, 0);
        glScalef(
            (box.ne.x-box.sw.x) * game_scale,
            (box.ne.y-box.sw.y) * game_scale,1);
        drawSquare();
    glPopMatrix();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3ub(255, 255, 255);
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
        drawTexturedSquare(textures[2]);
        drawTexturedSquare(textures[3]);
    glPopMatrix();
    glPushMatrix();
        glTranslatef((int)(-level_windowOffset*game_scale)%(int)(screen_w*2),0,0);
        glTranslatef(screen_w*1.5, screen_h/2,0);
        glScalef(-screen_w, screen_h,1);
        drawTexturedSquare(textures[2]);
        drawTexturedSquare(textures[3]);
    glPopMatrix();

  
}


void drawBG() {
    //draws the background of the game space
    glPushMatrix();
        glTranslatef(screen_w*1.5, screen_h/2,0);
        glTranslatef(-(int)((level_windowOffset*game_scale*(level_bgSpeed))+screen_w)%(int)(screen_w*2),0,0);
        glScalef(screen_w, screen_h,1);
        drawTexturedSquare(textures[1]);
    glPopMatrix();

    glPushMatrix();
        glTranslatef((int)(-level_windowOffset*game_scale*(level_bgSpeed))%(int)(screen_w*2),0,0);
        glTranslatef(screen_w*1.5, screen_h/2,0);
        glScalef(-screen_w, screen_h,1);
        drawTexturedSquare(textures[1]);
    glPopMatrix();

  }

void drawStats(EntityList* targetList) {
                
    int j=0;
    EntityList tmpTargetList = *targetList;

    int maxHeart=(tmpTargetList->hp)/10;
    printf("health %d",tmpTargetList->hp);
    int i=0;
   for (maxHeart;maxHeart>0;maxHeart--){
            
              glPushMatrix(); 
              glTranslatef(50+j,700,0);
              glScalef(20, 20,1);
              drawTexturedSquare(textures[7]);
              glPopMatrix();
              j+=20; 
 }
}