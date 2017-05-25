#include  <stdio.h>
#include  <time.h>
#include "E101.h"
#include "RobotFunction.h"

/* Test things
*/
int main() {
	init();
	setSpeed(0);
	sleep1(1, 0);
	turnLeft(1, 0);
	turnRight(1, 0);
	slowBackwards(1, 0);
	stop(1);
	return 0;
}



/* Real Code
*/
/*
int main() {
  bool debug = false;
  init();
  
  
  //Q1 open gate logic
  gateSequence();
  sleep1(1,0);
  
  
  //Q2 follow line logic
  char Q2 = 0;
  while (Q2 == 0) {
    double speedMultiplier = .95; //change this during testing
    int linePosition = 120; //change line position
    int lineError = seeLineX(linePosition); 
    if (lineError == 100000) {
      //go backwards
      slowBackward(0, 100000);
      sleep1(0,10000);
    } else if (lineError == 100001) {
      Q2 = 1;
    } else {
      int speedGo = int ((double)lineError*speedMultiplier);
      setSpeed(speedGo);
      sleep1(0,10000);
    }
  }
  
  
  //Q3 solve line maze
  //need to make it check for a red square at some point for Q4
  double speedMultiplier = 0.95; //change this during testing
  int linePositionX=120; //change line position
  int linePositionLeft = 80; //change where it looks for the left and right lines
  int linePositionRight = 120;
  int lineError;
  int lineOutputLeft;
  int lineOutputRight;
  int redLineValue;
  char Q3 = 0;
  while(Q3==0) {
    lineError = seeLineX(linePositionX);
	  if(debug) {
      printf("Line Error: %d", lineError);
    }
    if (lineError == 100000) {
      //if no more line ahead then try turning left or right
      lineOutputLeft = seeLineY(linePositionLeft);
      if(debug) {
        printf("output left: %d\n", lineOutputLeft);
      }
      lineOutputRight = seeLineY(linePositionRight);
      if(debug){
        printf("output right: %d\n", lineOutputRight);
      }
      if(lineOutputLeft != 100000) {
        //turn left
        if(debug){
	        printf("turning left\n");
        }
        turnLeft(0, 100000);
        while(seeLineX(linePositionX)== 100000 || seeLineX(linePositionX) <= -10) {
          turnLeft(0, 30000);
        }
      } else if (lineOutputRight !=100000) {
        //turn right
        if(debug){
  	      printf("turning right\n");
        }
        turnRight(0, 100000);
        while(seeLineX(linePositionX)== 100000 || seeLineX(linePositionX) >= 10) {
          turnRight(0, 30000);
        }
      } else {
        //turn around
        turnRight(0, 100000);
        while(seeLineX(linePositionX)== 100000 || seeLineX(linePositionX) >= 10) {
          turnRight(0, 30000);
        }
        if(debug){
          printf("turning around\n");
        }
      }
    sleep1(0,10000);
    } else {
      if(lineError == 100001) {
        lineError = 0;
      }
      if(debug){
       printf("going straigt\n");
      }
      setSpeedSlow(lineError*speedMultiplier) ;
      sleep1(0,10000);
    }
	  
	  redLineValue = seeRedLine(linePositionX);
	  if (redLineValue == 100002){
		Q3 = 1;
	  }
  }




	int wallFront;
	int wallLeft;
	int wallRight;
	//int redLineValue;
	linePositionX = 120;
	char Q4 = 0;
	while(Q4 == 0){
		wallFront = seeIR(2); //Checks distance of wall in front
		printf("Wall Front: %d\n", wallFront);
		if(wallFront >= 250){ //520 is distance we want to turn at
			printf("Turning\n");
			wallLeft = seeIR(3); //Checks distance of wall at left
			wallRight = seeIR(1); //Checks distance of wall at right
			if (wallLeft >= 400 && wallRight >= 400){ //more than 400 means wall there
				turnLeftIR();
			}
			else if (wallLeft < 400){ //Turn left
				turnLeftIR();
			}
			else if (wallRight < 400){ //Code for if wall on left but not right
				turnRightIR();
			}
		} else {
			
			
			set_motor(1, 120);
  			sleep1(0, 100);
  			set_motor(2, 120);
  			sleep1(0, 100000);
			
			/*
	    		double speedMultiplier = .5; //change this during testing
		    	wallLeft = seeIR(3); //Checks distance of wall at left
			wallRight = seeIR(1); //Checks distance of wall at right		
			int lineError = wallRight - wallLeft; //positive means closer to right negative means closer to left 
      			int speedGo = int ((double)lineError*speedMultiplier);
     			setSpeedSlow(speedGo);
      			sleep1(0,10000);
			
		}
	  	//redLineValue = seeRedLine(linePositionX);
	  	//if (redLineValue == 100002){
		//	stop(1); //red = stop for now
	 	//}
	}
	return 0;
}


*/
