#include <stdio.h>
#include "utility.h"
#include "variables.h"
#include "model.h"


//proverava da li je pravac kojim se u tom trenutku krecemo dobar
bool safe_moving(unsigned char key) {
    fflush(stdin);
    float playerCurrentPosition = playerPosX;
    if(key == 'a' || key == 'A') {    	
    	if(playerCurrentPosition < 1.8)
    		return false;
    	else
    		return true;
    }
    if(key == 'd' || key == 'D') { 
    	if(playerCurrentPosition > 3.2)
    		return false;
    	else
    		return true;
    }

    //Ako ni jedan uslov nije ispunjen mi mozemo da se krecemo u tom pravcu pa vracamo false
    return false;
}


void setLighting() {	
	//Podesavamo vektore
	GLfloat position [] = {10,10,10,1};
	GLfloat ambient  [] = {0.6,0.4,0.4,1};
	GLfloat diffuse  [] = {1,1,1,1};
	GLfloat specular [] = {1,1,1,1};

	//Inicijalizujemo osobine svetlosti koje zelimo i poziciju osvetljenja
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
}

// funkcija koja odredjuje da li je doslo do udaranja u prepreku, odvojena je po trakama
int is_crashed() {
	int i;
	if(playerPosX < 2.4) {
		for(i=0; i<500; i++)
			if(leftObstaclearray[i] != 0.0 && (int)leftObstaclearray[i] % 300 != 0){
				if(playerPosZ <= leftObstaclearray[i]+ obstacleLoop +0.7 && playerPosZ >= leftObstaclearray[i]+ obstacleLoop -0.4){
					return 1;
				}
			}
	}
	else if(playerPosX == 2.5){
		for(i=0; i<500; i++){
			if(midObstaclearray[i] != 0.0 && (int)midObstaclearray[i] % 300 != 0){
				if(playerPosZ <= midObstaclearray[i]+obstacleLoop+0.7 && playerPosZ >= midObstaclearray[i]+obstacleLoop -0.4){
					return 1;
				}
			}
		}
	}
	else
		for(i=0; i<500; i++){
			if(rightObstaclearray[i] != 0.0 && (int)rightObstaclearray[i] % 300 != 0){
				if(playerPosZ <= rightObstaclearray[i]+obstacleLoop+0.7 &&playerPosZ >= rightObstaclearray[i]+obstacleLoop -0.4) {
					return 1;
				}
			}
		}
	return 0;
}


void return_virus_bools_to_false() {
for(int i=0; i< 300; i++){
    leftVirusbool[i] = false;
    midVirusbool[i] = false;
    rightVirusbool[i] = false;
  }
}
// ova funkcija prati stanje prikupljenih virusa po trakama
int collected_viruses() {
	int i;
	if(playerPosX < 2.4) {
		for(i=0; i<300; i++)
			if(leftVirusarray[i] != 0.0 && leftVirusbool[i] == false){
				if(playerPosZ <= leftVirusarray[i]+obstacleLoop+0.3 && playerPosZ >= leftVirusarray[i]+obstacleLoop-0.2){
					leftVirusbool[i] = true;
					return 1;
				}
			}
	}
	else if(playerPosX == 2.5){
		for(i=0; i<300; i++){
			if(midVirusarray[i] +obstacleLoop != 0.0 && midVirusbool[i] == false){
				if(playerPosZ <= midVirusarray[i]+obstacleLoop+0.3 && playerPosZ >= midVirusarray[i]+obstacleLoop -0.2){
					midVirusbool[i] = true;
					return 1;
				}
			}
		}
	}
	else
		for(i=0; i<300; i++){
			if(rightVirusarray[i] != 0.0 && (int)rightVirusarray[i] % 300 != 0 && rightVirusbool[i] == false){
				if(playerPosZ <= rightVirusarray[i]+obstacleLoop+0.7 &&playerPosZ >= rightVirusarray[i]+obstacleLoop -0.4) {
					rightVirusbool[i] = true;
					return 1;
				}
			}
		}
	return 0;	
}




void setMaterial(char * option) {
	// leukocit(player)
	if(strcmp("player", option)==0) {
		//Podesavamo vektore
		// preko ovih vektora su takodje obojeni svi materijali, nisam sigurna da li je to ispravno, ali bar radi
		GLfloat specular [] = {0,0,0,0};
		GLfloat ambient  [] = {1, 1, 1,0.7};
		GLfloat diffuse  [] = {1, 1, 1, 1};
    	int shininess   = 100;
		
		//Inicijalizujemo osobine materijala
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
		glMaterialf(GL_FRONT, GL_SHININESS, shininess);	
	}
	else if(strcmp("obstacle", option)==0)
	{
		//Podesavamo vektore
		GLfloat specular [] = {0,0,0,0};
		GLfloat ambient  [] = {0.5, 0, 0,1};
		GLfloat diffuse  [] = {1, 0.1, 0, 1};
    	int shininess   = 100;

		//Inicijalizujemo osobine materijala
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
		glMaterialf(GL_FRONT, GL_SHININESS, shininess);
	}
	else if(strcmp("virus", option)==0) {
		//Podesavamo vektore
		GLfloat specular [] = {0,0,0,0};
		GLfloat ambient  [] = {0.909, 1, 0.552,1};
		GLfloat diffuse  [] = {0, 1, 0,1};
    	int shininess   = 100;

		//Inicijalizujemo osobine materijala
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
		glMaterialf(GL_FRONT, GL_SHININESS, shininess);
	}
	else if(strcmp("artery", option)==0) {
		//Podesavamo vektore
		GLfloat specular [] = {0,0,0,0};
		GLfloat ambient  [] = {1, 0.1, 0.1,0.7};
		GLfloat diffuse  [] = {1, 0, 0,0.9};
    	int shininess   = 100;

		//Inicijalizujemo osobine materijala
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
		glMaterialf(GL_FRONT, GL_SHININESS, shininess);
	}
	
	else if(strcmp("health", option)==0) {
		//Podesavamo vektore
		GLfloat specular [] = {0,0,0,0};
		GLfloat ambient  [] = {1, 1, 1,0.7};
		GLfloat diffuse  [] = {1, 1, 1,0.9};
    	int shininess   = 100;

		//Inicijalizujemo osobine materijala
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
		glMaterialf(GL_FRONT, GL_SHININESS, shininess);
	}				
}
