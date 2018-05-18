#include "score.h"




void drawNumber(int i) {
	drawTexturedSquare(textures[60+i]);
}


void drawScore(int score) {
	float puiss=0;
	while (score / (int)pow(10,puiss) > 0) {
		puiss ++;
	}
	int i = 0;
	for (i=puiss; i>0; i--) {
	glPushMatrix();
		glTranslatef(60 + 20 * (puiss - i), 680, 0);
		glScalef(20, 20, 1);
		drawNumber(score % (int)pow(10, i) / pow(10, i - 1));
	glPopMatrix();
	}
}

