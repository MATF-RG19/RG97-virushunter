#ifndef VARIABLES_H
#define VARIABLES_H

#include <stdio.h>
#include <stdbool.h> 


float window_height; //visina
float window_width; //sirina


bool just_started;
bool crashed;

//promenljive koje cuvaju poziciju igraca
float playerPosX;
float playerWidth; //sirina torusa odnosno playera
float lengthOfRoad;
float playerPosZ; 
float playerStepBackwards;
float playerStepForward;


float leftObstaclePosX;
float midObstaclePosX;
float rightObstaclePosX;
// niz ya prepreke za svaku traku
float *leftObstaclearray;
float *midObstaclearray;
float *rightObstaclearray;

// u kojoj su traci virusi
float leftVirusPosX;
float midVirusPosX;
float rightVirusPosX;
//za cuvanje pozicije virusa po trakama
float *leftVirusarray;
float *midVirusarray;
float *rightVirusarray;

bool *leftVirusbool;
bool *midVirusbool;
bool *rightVirusbool;

// brojaci
int obstacleCounter;
int virusCounter;

float move;
float obstacleLoop;
int pauseStart;

//animation parametar
bool animation_ongoing;



//kamera 
float cameraOffsetX;
float cameraOffsetY;


float dnFPS; //koristimo ga u on_timer pozivu za kontrolu frejmova po sekundi


//bool promenljive za kretanje
bool pressed_a;
bool pressed_d;

//fullscreen
bool fullscreen;


//Da li je igra restartovana
bool has_been_restarted;

//Score
int score;


#endif