#include  <stdio.h>
#include  <time.h>
#include "E101.h"
#include "RobotFunction.h"

//setting this up now where the main logic and stuff goes idk

/* Test things
*/
/*
int  main(){
  bool debug = true;
  init();
	
	
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
	
  if(debug) {
    printf("Q3 start\n");
  }
	
	
	
  double speedMultiplier = 0.95; //change this during testing
  int linePositionX=120; //change line position
  int linePositionLeft = 80; //change where it looks for the left and right lines
  int linePositionRight = 120;
  int lineError;
  int lineOutputLeft;
  int lineOutputRight;
  char Q3 = 0;
  while(Q3==0) {
    lineError = seeLineX(linePositionX);
	  if(debug) {
      printf("Line Error: %d\n", lineError);
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
        turnLeft(0, 625000);
      } else if (lineOutputRight !=100000) {
        //turn right
        if(debug){
  	  printf("turning right\n");
        }
        turnRight(1, 250000);
      } else {
        //turn around
        turnLeft(1, 250000);
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
      setSpeed(lineError*speedMultiplier) ;
      sleep1(0,10000);
    }
  }
	
	
	
	
	
	
	
	
	
  
  
  
   
  return  0;
}
*/

/* Real Code
*/

int main() {
  bool debug = true;
  init();
  
  /*
  //Q1 open gate logic
  gateSequence();
  sleep1(1,0);
  */
  
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
        turnLeft(0, 625000);
      } else if (lineOutputRight !=100000) {
        //turn right
        if(debug){
  	  printf("turning right\n");
        }
        turnRight(1, 250000);
      } else {
        //turn around
        turnLeft(1, 250000);
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
      setSpeed(lineError*speedMultiplier) ;
      sleep1(0,10000);
    }
  }
  
  /*
  //Q4 solve wall maze
  
	int wallFront;
	int wallLeft;
	int wallRight;
	while(true){
		int wallFront = seeWallFront(); //Checks if wall in front
		if(wallFront == 1){
			int wallLeft = seeWallLeft(); //Checks if wall at left
			int wallRight = seeWallRight(); //Checks if wall at right
			if (wallLeft == 1 && wallRight == 1){
				turn_left(); //Turns left twice at wall
				turn_left();
			}
			else if (wallLeft == 0){ //Code for if no wall on left
				turn_left();
			}
			else if (wallLeft == 1 && wallRight == 0){ //Code for if wall on left but not right
				turn_right();
			}
		}
		//Go forward
		//Sleep
	}

*/
  
  
  return 0;
}


