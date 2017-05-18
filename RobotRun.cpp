#include  <stdio.h>
#include  <time.h>
#include "E101.h"
#include "RobotFunction.h"

//setting this up now where the main logic and stuff goes idk

/* Test things
*/
int  main(){
  init();
  gateSequence();
  sleep1(1,0);
	
	
  char Q2 = 0;
  while (Q2 == 0) {
    double speedMultiplier = 0.8; //change this during testing
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
  stop(1);
  stop(2);
  
  
  
   
  return  0;
}
/* Real Code
*/
/*
int main() {
  init();
  //Q1 open gate logic
  gateSequence();
  sleep1(1,0);
  //Q2 follow line logic
  char Q2 = 0;
  while (Q2 == 0) {
    double speedMultiplier = 0.5; //change this during testing
    int linePosition = 120; //change line position
    int lineError = seeLineX(linePosition); 
    if (lineError == 100000) {
      slowBackward(0, 100000);
      sleep1(0,10000);
    } else if (lineError == 100001) {
      Q2 = 1;
    } else {
      int speedGo = lineError*speedMultiplier;
      setSpeed(speedGo);
      sleep1(0,10000);
    }
  }
  //Q3 solve line maze
  //need to make it check for a red square at some point for Q4
  double speedMultiplier = 0.5; //change this during testing
  int linePositionX=120; //change line position
  int linePositionLeft = 80; //change where it looks for the left and right lines
  int linePositionRight 240;
  int lineError = seeLineX(linePositionX);
  int lineOutputLeft;
  int lineOutputRight;
  if (lineError == 100000) {
    //if no more line ahead then try turning left or right
    lineOutputLeft = seeLineY(linePositionLeft);
    lineOutputRight = seeLineY(linePositionRight);
    if(lineOutputLeft != 100000) {
      //turn left
      turn_left(100000);
    } else if (lineOutputRight !=100000) {
      //turn right
      turn_right(100000);
    } else {
      //go backwards
      slowBackward(100000);
    }
    sleep1(0,10000);
  } else {
    setSpeed(lineError*speedMultiplier) 
    sleep1(0,10000);
  }
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

  
  
  return 0;
}
*/

