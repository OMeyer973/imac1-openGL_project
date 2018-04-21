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
		//stripping the 2 header characters from the file (P6 or P3)
		if (fscanf(in,"%c", &tmpc) == EOF) return 0;
		if (fscanf(in,"%c", &tmpc) == EOF) return 0;
		//getting img width, height and nb of colors per channel
		if (fscanf(in,"%d", &level_w) == EOF) return 0; //scanning & making sure we haven't reached EOF with 1 line
		if (fscanf(in,"%d", &level_h) == EOF) return 0;
		if (fscanf(in,"%d", &nbcolors) == EOF) return 0;
		/* //debug
			printf("width : %d\n", level_w);
			printf("height : %d\n", level_h);
			printf("nbcolors : %d\n", nbcolors); */
		//getting pixels data
		int x = 0, y = 0;
		for (y=0; y < level_h; y++) {
			for (x=0; x < level_w; x++) {
				//getting the 3 colors channels for the current pixel
				if (fscanf(in,"%d", &r) == EOF) return 0;
				if (fscanf(in,"%d", &g) == EOF) return 0;
				if (fscanf(in,"%d", &b) == EOF) return 0;
				/*//debug : re-draw the basic image in ascii to be sure we didn't do stupid things
					if (r == -1) printf(" ");
					else printf("#");
					if (x % level_w == 0) {
						printf("\n");
					} */
				//if the pixel is not white (background color), add an object
				if (r < 250 || g < 250 || b < 250)
					/*PPM image format : 
						r encodes the object : wall or bonus or foe (50 by 50)
						v encodes the type of the object (for foe or bonus, cf stats) : encoded 20 by 20, hence the division */
					addObjectToLevel(x, level_h - y, r / 50, g / 20);
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

int addObjectToLevel(int x, int y, int type, int subType){
	//add an object to the level in correct list
	switch(type){
		case TYPEWALL:
			addWall(x, y, subType);
			break;
		case TYPEBONUS:
			addBonus(x, y, subType);
			break;
		case TYPEMOB:
			addMob(x, y, subType);
			break;
		default:
			//printf("tried to add invalid object of type %d at %d %d\n", type, x, y);
			return 0;
			break;
	}
	return 1;
}

int addWall(int x, int y, int subType){
	//printf("adding wall\n");
	if (subType < NBWALLTYPES){
		printf("subtype %d\n", subType);
		EntityList tmpEntity = copyEntity(&stats_walls[subType]);
		tmpEntity->anchor = pointXY(x,y);
		addEntityEnd(&level_walls, tmpEntity);
		return 1;
	}
	printf("tried to add invalid wall of subtype %d at %d %d\n", subType, x, y);
	return 0;
}

int addBonus(int x, int y, int subType){
	//printf("adding bonus\n");
	if (subType < NBBONUSTYPES){
		EntityList tmpEntity = copyEntity(&stats_bonuses[subType]);
		tmpEntity->anchor = pointXY(x,y);
		addEntityEnd(&level_bonuses, tmpEntity);
		return 1;
	}
	printf("tried to add invalid bonus of subtype %d at %d %d\n", subType, x, y);
	return 0;
}

int addMob(int x, int y, int subType){
	//printf("adding mob\n");
	if (subType < NBMOBTYPES){
		EntityList tmpEntity = copyEntity(&stats_mobs[subType]);
		tmpEntity->anchor = pointXY(x,y);
		addEntityEnd(&level_mobs, tmpEntity);
		return 1;
	}
	printf("tried to add invalid mob of subtype %d at %d %d\n", subType, x, y);
	return 0;
}

