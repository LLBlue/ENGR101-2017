#include  <stdio.h>
#include  <time.h>
#include "E101.h"
#include "RobotFunction.h"

/* Test things
*/
int main() {
	init();
	int wallFront;
	int wallLeft;
	int wallRight;
	int redLineValue;
	int linePositionX = 120;
	char Q4 = 0;
	while(Q4 == 0){
		int wallFront = seeIR(1); //Checks distance of wall in front
		if(wallFront >= 520){ //520 is distance we want to turn at
			int wallLeft = seeIR(2); //Checks distance of wall at left
			int wallRight = seeIR(3); //Checks distance of wall at right
			if (wallLeft >= 400 && wallRight >= 400){ //more than 400 means wall there
				turnLeft(1, 25000); //Turns left twice at wall
			}
			else if (wallLeft < 400){ //Turn left
				int maxDiff = 50;
				int dist3 = 3000;
				int dist2 = 2000;
				int dist1 = 1000;
				int dist0;
				int diff2;
				int diff1;
				int diff0;
				char turning = 0;
				while (turning == 0) {
					dist0 = seeIR(1);
					diff2 = dist2-dist3;
					diff1 = dist1-dist2;
					diff0 = dist0-dist1;
					if(diff0 >= diff1-maxDiff && diff0 <= diff1+maxDiff && diff0 >= diff2-maxDiff && diff0 <= diff2+maxDiff){
						turning = 1; //finished turning if all the differences are close enough
					} else {
						turnLeft(0, 50000);
					}
					dist3 = dist2;
					dist2 = dist1;
					dist1 = dist0;
				}
				
			}
			else if (wallRight < 400){ //Code for if wall on left but not right
				int maxDiff = 50;
				int dist3 = 3000;
				int dist2 = 2000;
				int dist1 = 1000;
				int dist0;
				int diff2;
				int diff1;
				int diff0;
				char turning = 0;
				while (turning == 0) {
					dist0 = seeIR(1);
					diff2 = dist2-dist3;
					diff1 = dist1-dist2;
					diff0 = dist0-dist1;
					if(diff0 >= diff1-maxDiff && diff0 <= diff1+maxDiff && diff0 >= diff2-maxDiff && diff0 <= diff2+maxDiff){
						turning = 1; //finished turning if all the differences are close enough
					} else {
						turnRight(0, 50000);
					}
					dist3 = dist2;
					dist2 = dist1;
					dist1 = dist0;
				}
			}
		} else {
			set_motor(1, 75);
			  sleep1(0, 100);
  			set_motor(2, 75);
 			 sleep1(0, 100000);
		}
		redLineValue = seeRedLine(linePositionX);
	  	if (redLineValue == 100002){
			stop(1); //red = stop for now
	  	}
		//Go forward
		//Sleep
	}

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
  
  
  //Q4 solve wall maze
  
	int wallFront;
	int wallLeft;
	int wallRight;
	char Q4 = 0;
	while(Q4 == 0){
		int wallFront = seeWallFront(); //Checks if wall in front
		if(wallFront == 1){
			int wallLeft = seeWallLeft(); //Checks if wall at left
			int wallRight = seeWallRight(); //Checks if wall at right
			if (wallLeft == 1 && wallRight == 1){
				turn_left(1, 25000); //Turns left twice at wall
			}
			else if (wallLeft == 0){ //Code for if no wall on left
				turn_left(0, 625000);
			}
			else if (wallLeft == 1 && wallRight == 0){ //Code for if wall on left but not right
				turn_right(0, 625000);
			}
		}
		redLineValue = seeRedLine(linePositionX);
	  	if (redLineValue == 100002){
		sleep1(0, 500000)'
	  }
		//Go forward
		//Sleep
	}


  
  stop(1);
  return 0;
}

*/
