#ifndef UTILITY_H
#define UTILITY_H


#include <stdlib.h>
#include <GL/glut.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "callback.h"
#include "keyboard.h"
#include "variables.h"

//funkcije
bool safe_moving(unsigned char key);
void setLighting();
void setMaterial(char* option);
int is_crashed();
int collected_viruses();
void return_virus_bools_to_false();

#endif 