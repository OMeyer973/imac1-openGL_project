#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>  
#include <string.h>
#include <dirent.h>
#include <time.h> 


#include "main_functions.h"


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