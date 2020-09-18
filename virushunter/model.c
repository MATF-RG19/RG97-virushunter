#include "model.h"


void drawPlayerModel(float x, float z) {
  //funkcija za kreiranje leukocita (player)
	setMaterial("player");

  glPushMatrix();

    glTranslatef(x, -0.5, z);
    glRotatef(playerPosZ*100, 1, 1, 1);
    glutSolidTorus(0.1, playerWidth, 10, 100);
    
  glPopMatrix();
  
	
}

void drawVirus(float x, float z) {
  // funkcija za kreiranje virusa
  setMaterial("virus");

  glPushMatrix();

    glTranslatef(x, -0.5, z);
    glRotatef(playerPosZ*100, 0, 1, 0);
    //virus je nastao od sfere, parametar slices je postavljen na 8 kako bi imao bodlje i malo vise podsecao na virus
    glutSolidSphere(playerWidth, 8, 2);

  glPopMatrix();

}

void drawObstacle() {
  // funkcija koja crta eritrocite, ako se dobro secam kad sam objasnjavala temu, leukocit bi trebalo da izbegava eritrocite nadam se :)
 for(int j = 0; j< 500; j++){
     //kreiramo prepreke(eritrocite) u 3 razlicite trake
      if(obstacleCounter == 0){
        setObstacle();
        obstacleCounter = 1;
      }
      if(leftObstaclearray[j] != 0.0 && (int)leftObstaclearray[j] % 300 != 0){
        setMaterial("obstacle");

        glPushMatrix();

          glTranslatef((lengthOfRoad-0.9),-0.75, leftObstaclearray[j] + obstacleLoop);
          glRotatef(playerPosZ*100, 1, 1, 1);
          //eritrocit koji je takodje torus ne izgleda lepo i glatko kao leukocit, ali je podesavanje ovih paramatera na vece vrednosti jako usporavalo igru, zbog generisanja tolikog broja torusa pa sam se odlucila da budu pomalo rustic 
          glutSolidTorus(0.1, playerWidth, 10, 30);

        glPopMatrix();
      }

      if(midObstaclearray[j] != 0.0 && (int)midObstaclearray[j] % 300 != 0){
        setMaterial("obstacle");

        glPushMatrix();

          glTranslatef(1.22,-0.75, midObstaclearray[j] + obstacleLoop);
          glRotatef(playerPosZ*100, 1, 1, 1);
          glutSolidTorus(0.1, playerWidth, 10, 30);

        glPopMatrix();
      }
  
      if(rightObstaclearray[j] != 0.0 && (int)rightObstaclearray[j] % 300 != 0){
        setMaterial("obstacle");

        glPushMatrix();

          glTranslatef(1.85,-0.75, rightObstaclearray[j] + obstacleLoop);
          glRotatef(playerPosZ*100, 1, 1, 1);
          glutSolidTorus(0.1, playerWidth, 10, 30);

        glPopMatrix();
      }
  }
}

// postavljanje prepreka
void setObstacle() {
  leftObstaclearray = calloc(500, sizeof(float));
  midObstaclearray= calloc(500, sizeof(float));
  rightObstaclearray = calloc(500, sizeof(float));

  if(leftObstaclearray == NULL || midObstaclearray == NULL || rightObstaclearray == NULL) {
    fprintf(stderr, "Creating obstacles\n");
    exit(EXIT_FAILURE);
  }
  int i = 0, k = 0, l = 0;
  for(int j = 20; (float)j> -1000; j--){

      // dajemo neki random broj od 0 do 1 i ako je manji od 0.3 postojace prepreka u PRVOJ traci (skroz levo)
     
      if(((rand() % 10000) / 10000.0) < 0.3 && j%7 == 0) {
        leftObstaclearray[i] = j-23;
        i++;
      }

      //prepreke u sredini
      if(((rand() % 10000) / 10000.0) < 0.3 && j%7 == 0) {
        midObstaclearray[k] = j-31;
        k++;
      }
      //prepreke skroz desno
      if(((rand() % 10000) / 10000.0) < 0.3 && j%7 == 0) {
       rightObstaclearray[l] = j-27;
       l++;
      }
  }
}

void drawViruses() {
  // funkcija uz pomoc koje se iscrtavaju virusi
  for(int j = 0; j< 300; j++){
    if(virusCounter == 0){
      setViruses();
      virusCounter = 1;
    }
    if(leftVirusbool[j] == false && leftVirusarray[j] != 0.0)
      drawVirus(0.63, leftVirusarray[j] + obstacleLoop);

    if(midVirusbool[j] == false && midVirusarray[j] != 0.0)
      drawVirus(1.25, midVirusarray[j] + obstacleLoop);
    
    if(rightVirusbool[j] == false && rightVirusarray[j] != 0.0)
      drawVirus(1.85, rightVirusarray[j] + obstacleLoop);
    
  }

}


void setViruses() {
  // postavljamo viruse
  leftVirusarray = calloc(300, sizeof(float));
  midVirusarray = calloc(300, sizeof(float));
  rightVirusarray = calloc(300, sizeof(float));

  leftVirusbool = malloc(300*sizeof(bool));
  midVirusbool = malloc(300*sizeof(bool));
  rightVirusbool = malloc(300*sizeof(bool));

  if(leftVirusarray == NULL || midVirusarray == NULL || rightVirusarray == NULL
    || leftVirusbool == NULL || midVirusbool == NULL || rightVirusbool == NULL) {
    fprintf(stderr, "Creating viruses\n");
    exit(EXIT_FAILURE);
  }

  for(int i=0; i< 300; i++){
    leftVirusbool[i] = false;
    midVirusbool[i] = false;
    rightVirusbool[i] = false;
  }
  // ista funkcija kao za prepreke samo sa malo drugacijim parametrima, tako izbegavam da mi se prepreka i virus pojavljuju na istom mestu, sto mi se desavalo na pocetku
  int i = 0, k = 0, l = 0;
  for(int j = 20; (float)j> -1000; j--){

      // virusi u prvoj traci
      if(((rand() % 10000) / 10000.0) < 0.7 && j%11 == 0) {
        leftVirusarray[i] = j-20;
        i++;
      }

      //virusi u srednjoj traci
      if(((rand() % 10000) / 10000.0) < 0.8 && j%11 == 0) {
        midVirusarray[k] = j-28;
        k++;
      }
      //virusi u trecoj traci
      if(((rand() % 10000) / 10000.0) < 0.75 && j%11 == 0) {
       rightVirusarray[l] = j-24;
       l++;
      }
  }
}


void drawArtery() {
  for(int j = 10; (float)j> -490; j--){
  // iscrtava neku vrstu tunela i pokusava da oponasa kretanje krvi kroz krvni sud
      if(j%10 == 0) {
        setMaterial("artery");
        glPushMatrix();

        glTranslatef((lengthOfRoad - 0.3),-0.75, j+ obstacleLoop);
        glutSolidTorus(lengthOfRoad+10, 14, 30, 30);

        glPopMatrix();
      }
    }
}  
// ispisuje skor
void writeHealth() {
    char *s = malloc(300 * sizeof(char));
    if(s == NULL) {
      fprintf(stderr, "health score\n");
      exit(EXIT_FAILURE);
    }  
    
    sprintf (s, "HEALTH: %i%%  ", score);
    
    setMaterial("health");  
    glRasterPos3f( 0.97, 0.3, playerPosZ-2);
    char * font;
    for( font = s; *font; font++ ) {
        glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, (int)*font );
    }

    free(s);
}
// ispisuje tekst
void printText(char *text, float x, float y, float z){
	
	glPushMatrix();
	
	glRasterPos3f( x,  y,  z);
	int i;
	for(i=0; text[i]!='\0'; i++){
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
	}
    glTranslatef(i/2, 0, 0);
	glPopMatrix();
	
}
