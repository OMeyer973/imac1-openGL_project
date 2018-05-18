#include "level.h"



//functions for handling a level

int makeLevelFromPPM(char* filename) {
	//takes a PPM filepath as input and add objects to the 3 lists describing a level : walls list, mobs list, bonus list
	printf("lecture du fichier PPM ... \n");
	FILE *in = NULL;
	in = fopen(filename, "r");

	if (in != NULL) {
		int r, g, b;
		char tmpc;
		int nbcolors; //img height, width and number of colors for each chanel
		//début du traitement du fichier ppm
		//stripping the 2 header characters from the file (P6 or P3) && the gimp header
		int i =0;
		for (i=0; i < 42; i++) {
			if (fscanf(in,"%c", &tmpc) == EOF) return 0;
		}
		//getting img width, height and nb of colors per channel
		if (fscanf(in,"%d", &level_h) == EOF) return 0; //scanning & making sure we haven't reached EOF with 1 line
		if (fscanf(in,"%d", &level_w) == EOF) return 0;
		if (fscanf(in,"%d", &nbcolors) == EOF) return 0;
		//w & h are inverted in order to rotate the image
		/* //debug
			printf("width : %d\n", level_w);
			printf("height : %d\n", level_h);
			printf("nbcolors : %d\n", nbcolors); */
		//getting pixels data
		int x = 0, y = 0;
		for (x=0; x < level_w; x++) {
			for (y=0; y < level_h; y++) {
				//getting the 3 colors channels for the current pixel
				if (fscanf(in,"%d", &r) == EOF) return 0;
				if (fscanf(in,"%d", &g) == EOF) return 0;
				if (fscanf(in,"%d", &b) == EOF) return 0;
				//if the pixel is not white (background color), add an object
				if (r <= 254 && g <= 254 && b <= 254)
					/*PPM image format : 
						r encodes the object : wall or bonus or foe (50 by 50)
						v encodes the type of the object (for foe or bonus, cf stats) : encoded 20 by 20, hence the division */
					addObjectToLevel(x, 1+y, r / 100, g / 20, (float)b / 50);
			}
		}
		fclose(in);
	} else { 
		printf("Impossible de charger le fichier \"%s\" \n", filename);
		return 0;
	}
	printf("OK\n");
	return 1;
}

int addObjectToLevel(int x, int y, int type, int subType, float scale){
	//add an object to the level in correct list
	switch(type){
		case TYPEWALL:
			addWall(x, y, subType, scale);
			break;
		case TYPEMOB:
			addMob(x, y, subType, scale);
			break;
		case TYPEBONUS:
			addBonus(x, y, subType, scale);
			break;
		default:
			//printf("tried to add invalid object of type %d at %d %d\n", type, x, y);
			return 0;
			break;
	}
	return 1;
}

int addWall(int x, int y, int subType, float scale){
	//printf("adding wall\n");
	if (subType < NBWALLTYPES){
		//printf("subtype %d\n", subType);
		EntityList tmpEntity = copyEntity(&stats_walls[subType]);
		tmpEntity->anchor = pointXY(x,y);
		if (scale < 0.2) scale = 0.2;
		scaleBoundingBox(&(tmpEntity->hitBox), scale);
		scaleBoundingBox(&(tmpEntity->spriteBox), scale);
		addEntityEnd(&level_walls, tmpEntity);
		return 1;
	}
	printf("tried to add invalid wall of subtype %d at %d %d\n", subType, x, y);
	return 0;
}

int addBonus(int x, int y, int subType, float scale){
	if (subType < NBBONUSTYPES){
		printf("adding bonus\n");
		EntityList tmpEntity = copyEntity(&stats_bonuses[subType]);
		tmpEntity->anchor = pointXY(x,y);
		if (scale < 0.2) scale = 0.2;
		scaleBoundingBox(&(tmpEntity->hitBox), scale);
		scaleBoundingBox(&(tmpEntity->spriteBox), scale);
		addEntityEnd(&level_bonuses, tmpEntity);
		return 1;
	}
	printf("tried to add invalid bonus of subtype %d at %d %d\n", subType, x, y);
	return 0;
}

int addMob(int x, int y, int subType, float scale){
	//printf("adding mob\n");
	if (subType < NBMOBTYPES){
		EntityList tmpEntity = copyEntity(&stats_mobs[subType]);
		tmpEntity->anchor = pointXY(x,y);
		if (scale < 0.2) scale = 0.2;
		tmpEntity->hp *= scale;
		scaleBoundingBox(&(tmpEntity->hitBox), scale);
		scaleBoundingBox(&(tmpEntity->spriteBox), scale);
		addEntityEnd(&level_mobs, tmpEntity);
		return 1;
	}
	printf("tried to add invalid mob of subtype %d at %d %d\n", subType, x, y);
	return 0;
}
