#ifndef MODEL_H
#define MODEL_H

#include <stdlib.h>
#include <GL/glut.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include "callback.h"
#include "utility.h"
#include "variables.h"


//iscrtava leukocit(player)
void drawPlayerModel(float x, float z);

//naredne funkcije su iz naziva jako intuitivne za razumevanje
void drawObstacle();
void drawViruses();
void setObstacle();
void setViruses();
void drawArtery();
void writeHealth();
void drawMenu();
// ispisuje tekst na ekranu
void printText(char *text, float x, float y, float z);

#endif