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
    //sets the wiew to the origin of the game space
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
        glPushMatrix();
            glTranslatef(
                (list->anchor.x + (list->hitBox.ne.x+list->hitBox.sw.x)/2) * game_w / level_h,
                (list->anchor.y + (list->hitBox.ne.y+list->hitBox.sw.y)/2) * game_h / (level_h+0.5), 0);
            glScalef(
                (list->hitBox.ne.x-list->hitBox.sw.x) * game_h / level_h,
                (list->hitBox.ne.y-list->hitBox.sw.y) * game_h / level_h,1);
            glRotatef(list->angle / 2 / M_PI * 360,0,0,1);
            drawTexturedSquare(textures[list->textureID]);
        glPopMatrix();
        list = list->next;
    }       
}


void drawBorders() {
    //draws the top & bottom borders background needs to be in screen space prior to call (!not gamespace!)
    glPushMatrix();
        glTranslatef(screen_w/2, screen_h/2,0);
        glScalef(screen_w, screen_h,1);
        drawTexturedSquare(textures[2]);
        drawTexturedSquare(textures[3]);
    glPopMatrix();
}


void drawBG() {
    //draws the background of the game space
    glPushMatrix();
        glTranslatef(game_w/2, game_h/2,0);
        glScalef(game_w, game_h,1);
        drawTexturedSquare(textures[1]);
    glPopMatrix();
}