#include "callback.h"
#include "variables.h"
#include "model.h"


void set_callback(void) {
    setKeyboardFunc(); //iz keyboard.h
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);
    glutTimerFunc(1000/dnFPS, on_timer, 0);
}



void on_display(void) {
    //cistimo bafere
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Podesava se viewport
    glViewport(0, 0, window_width, window_height);

    // Podesava se projekcija. 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, window_width/(float)window_height, 0.7, 10);

    // Podesava se vidna tacka
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();   
    //podesavamo pogled kamere
    gluLookAt(1.2, 0.5, playerPosZ+2, 1.2, 0, playerPosZ+1, 0, 1, 0);

    srand(time(NULL));
    glScalef(1, 1, 1);

    switch(animation_ongoing){
       case 0:
            
        glPushMatrix();
      
        // kada player udari u prepreku, igra se zavrsava, a na ekranu se prikazuje poslednja pozicija playera, zajedno sa rezultatom i porukom
        drawPlayerModel((float)(playerPosX / 2), playerPosZ);
        // Podesavanje parametara
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
        glEnable(GL_LINE_SMOOTH);
           
        // za razlicite intervale skora, prikazuje razlicite poruke
        if(crashed && score<=25){

            glPushMatrix();
                
                glColor3f(1,1,1);
                writeHealth();
                printText("GAME OVER!", 1.1, 0.3, playerPosZ+0.1);
                printText("Your human is still under attack!", 1, 0.3, playerPosZ+0.5);
                printText("Press 'R' or 'r' to play again.", 1.09, 0.3, playerPosZ+0.9);

            glPopMatrix();
        }
        else if(crashed && (score>=26 && score<=50))
        {
            glPushMatrix();
                
                glColor3f(1,1,1);
                writeHealth();
                printText("GAME OVER!", 1.1, 0.3, playerPosZ+0.1);
                printText("Your human is still weak!", 1.05, 0.3, playerPosZ+0.5);
                printText("Press 'R' or 'r' to play again.", 1.09, 0.3, playerPosZ+0.9);
                
            glPopMatrix();
        }
        else if(crashed && (score>=51 && score<=75))
        {
            glPushMatrix();

                glColor3f(1,1,1);
                writeHealth();
                printText("GAME OVER!", 1.1, 0.3, playerPosZ+0.1);
                printText("Your human is getting better!", 1.02, 0.3, playerPosZ+0.5);
                printText("Press 'R' or 'r' to play again.", 1.09, 0.3, playerPosZ+0.9);
              
            glPopMatrix();
        }
        else if(crashed && (score>=76 && score<100)){

            glPushMatrix();
                
                glColor3f(1,1,1);
                writeHealth();
                printText("GAME OVER!", 1.1, 0.3, playerPosZ+0.1);
                printText("So close! Your human is almost fully healthy!", 0.9, 0.3, playerPosZ+0.5);
                printText("Press 'R' or 'r' to play again.", 1.09, 0.3, playerPosZ+0.9);
                
            glPopMatrix();
        }
        else if(crashed && score==100){

            glPushMatrix();
                
                glColor3f(1,1,1);
                writeHealth();
                printText("GAME OVER!", 1.1, 0.3, playerPosZ+0.1);
                printText("Congratulations! Your human is completely healed!", 0.85, 0.3, playerPosZ+0.5);
                printText("But you can still play the game :)", 1.09, 0.3, playerPosZ+0.9);
                // printText("Press 'R' or 'r' to play again.", 1.09, 0.3, playerPosZ+0.11);
                
            glPopMatrix();
        }
        glPopMatrix();
        break;

        case 1:
          // dok traje animacija, ovo je deo sa igrom
          glPushMatrix();
        	// Iscrtavamo igraca
   	      drawPlayerModel((float)(playerPosX / 2), playerPosZ);
          // iscrtavamo viruse
          drawViruses();
          // posto mi je score u procentima kada se ispisuje, u trenutku kada neko skupi 100 poena brojac prestaje sa radom, medjutim moze i dalje da se nastavi sa igrom 
          // najvise bi imalo smisla da se tada ne iscrtavaju virusi, ali onda igra ne bi imala smisla, pa kad god neko stigne do 100 moze i dalje da sakuplja viruse
          if(collected_viruses() && score < 100) {
            score += 1; 
          }
          else if(collected_viruses() && score==100){
            
          }
          // iscrtavamo prepreke i tunel
          drawObstacle();
          drawArtery();
   
          if(is_crashed()) {
          animation_ongoing = false;
          crashed = true;
          }
          //ispisujemo score
         writeHealth();
         glPopMatrix();
         break;
    }

   glutSwapBuffers();
}


void on_timer(int value) {  

  if(animation_ongoing) {


   if((int)playerPosZ % 298 == 0){
      return_virus_bools_to_false();
    }

   if((int)playerPosZ % 300 == 0){
      obstacleLoop = playerPosZ;
    }
    // simulira se kretanje lopte po z osi, odnosno ona se tom brzinom krece po putu
    playerPosZ -= move;


    if((int)playerPosZ % 50 == 0){
      move = move + 0.003;
    }


    if(pressed_a) {
       //Ako pritisnemo 'a' zelimo da igrac skrene u levo
    //  printf("left; current position: %f\n", playerPosX);
     if(safe_moving('a')) 
        playerPosX += playerStepBackwards;

      pressed_a = false;
      // printf("left; current position: %f\n\n", playerPosX);
    }
    else if(pressed_d) {
      // printf("right; current position: %f\n", playerPosX);
       //Ako pritisnemo 'd' zelimo da igrac skrene u desno
      if(safe_moving('d'))
          playerPosX += playerStepForward;

      pressed_d = false;
      // printf("right; current position: %f\n\n", playerPosX);
    }  
	}
  
  glutPostRedisplay(); //nanovo ucitavamo prozor u odredjenim intervalima
  glutTimerFunc(1000/dnFPS, on_timer, 0); //funkcija on_timer sama sebe poziva 
}


void on_reshape(int width, int height) {
 //Postavlja se viewport. 
  glViewport(0, 0, width, height);

  /* Postavljaju se parametri projekcije. */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60, (float) width / height, 1, 1500);

  window_width = width;
  window_height = height;
}

