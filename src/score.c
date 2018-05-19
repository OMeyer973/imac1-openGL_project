#include "score.h"




void drawNumber(int i) {
	drawTexturedSquare(textures[60+i]);
}


void drawScore(int score,int posY) {
	float puiss=1;
	while (score / (int)pow(10,puiss) > 0) {
		puiss ++;
	}
	int i = 0;
    int start=60;
    if(posY==100){
    glPushMatrix();
        glTranslatef(90 , posY, 0);
        glScalef(100, 20, 1);
        drawTexturedSquare(textures[9]);
    glPopMatrix();
    start=220;
    }
	for (i=puiss; i>0; i--) {
	glPushMatrix();
		glTranslatef(start + 20 * (puiss - i), posY, 0);
		glScalef(20, 20, 1);
		drawNumber(score % (int)pow(10, i) / pow(10, i - 1));
	glPopMatrix();
	}
}


int writeHighScore()
{	
 FILE* fichier, *fichier1, *fichier2 = NULL;

    int currentHighscore=0; // Tableau des 3 meilleurs scores
    fichier = fopen("./highscore.txt", "r");
    if (fichier != NULL)
    {   
        if (fscanf(fichier, "%d ", &currentHighscore));
        fclose(fichier);

	
    }

    if(score>currentHighscore)
    {
    	int temp=score;

    	// We empty the file 
    	fichier1=fopen("./highscore.txt","w");
    	fclose(fichier1);


    	// We put the new highscore in the file
    	fichier2=fopen("./highscore.txt","w");
    	printf("Nv record battu %d",temp);
    	fprintf(fichier2, "%d", temp);  
    	fclose(fichier2);
    }

    return currentHighscore;
}

void drawHighScore()
{
  	int best=writeHighScore();
	drawScore(best,-50);
}
