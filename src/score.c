#include "score.h"




void drawNumber(int i)
{
switch (i) {

case 0 :
	drawTexturedSquare(textures[60]);
	break;
case 1 :
	drawTexturedSquare(textures[61]);
	break;
case 2 :
	drawTexturedSquare(textures[62]);
	break;
case 3 :
	drawTexturedSquare(textures[63]);
	break;
case 4 :
	drawTexturedSquare(textures[64]);
	break;
case 5 :
	drawTexturedSquare(textures[65]);
	break;
case 6 :
	drawTexturedSquare(textures[66]);
	break;
case 7 :
	drawTexturedSquare(textures[67]);
	break;
case 8 :
	drawTexturedSquare(textures[68]);
	break;
case 9 :
	drawTexturedSquare(textures[69]);
	break;
default: 
	break;
	}
}


void drawScore(int i)
{ glPushMatrix();
  glTranslatef(60,680,0);
  glScalef(20, 20,1);
  drawNumber((i%1000)/100);
  glPopMatrix();

  glPushMatrix();	
  glTranslatef(80,680,0);
  glScalef(20, 20,1);
  drawNumber((i%100)/10);	
  glPopMatrix();

  glPushMatrix();
  glTranslatef(100,680,0);
  glScalef(20, 20,1);
  drawNumber(i%10);glPopMatrix();
}

