#include "variables.h"
#include <stdio.h>
#include <stdbool.h>

//promenljive koje se koriste svuda, primetila sam da su ostali cesto na ovaj nacin organizovali kod pa sam to primenila i ja

//Promenljive koje cuvaju velicinu prozora
float window_height; //visina
float window_width; //sirina

bool just_started = true;
bool crashed = false;

//promenljive koje cuvaju poziciju igraca
float playerPosX = 2.5;
float playerWidth = 0.1; //sirina torusa koju koristim i za playera i za prepreke
float lengthOfRoad = 1.5;
float playerPosZ = -5; 
float playerStepBackwards = -0.6;
float playerStepForward = 0.6;

//pomocne promenljive za prepreke
//pokazuje gde se odnosno na kojoj traci nalaze prepreke
float leftObstaclePosX = 2;
float midObstaclePosX = 2.5;
float rightObstaclePosX = 3;
// niz za prepreke za svaku traku
float *leftObstaclearray;
float *midObstaclearray;
float *rightObstaclearray;
// u kojoj su traci virusi
float leftVirusPosX = 2;
float midVirusPosX = 2.5;
float rightVirusPosX = 3;
// nizovi koji cuvaju gde se nalaze virusi po trakama
float *leftVirusarray;
float *midVirusarray;
float *rightVirusarray;

// ovi nizovi su tu kako bi videli da li je player vec prosao odredjen virus
bool *leftVirusbool;
bool *midVirusbool;
bool *rightVirusbool;

int obstacleCounter = 0;
int virusCounter = 0;

float move = 0.1; //brzina kojom se krece
float obstacleLoop = 0; //nove prepreke se ne generisu, samo transliraju stare
int pauseStart = 0;

//animation parametar
bool animation_ongoing = true;

//kamera 
float cameraOffsetX = 0.2;
float cameraOffsetY = 1;


float dnFPS = 1000; //koristimo ga u on_timer pozivu za kontrolu frejmova po sekundi

//bool promenljive za kretanje
bool pressed_a = false;
bool pressed_d = false;

//fullscreen
bool fullscreen = true;


//Da li je igra restartovana
bool has_been_restarted = true;

//Score
int score = 0;