#ifndef SCORE_H_
#define SCORE_H_

#include <math.h>
#include "graphics.h"


void drawNumber(int i);
void drawScore(int score,int posY);
int writeHighScore();
void drawHighScore();

extern int score;

#endif
