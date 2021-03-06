#include  <stdio.h>
#include  <time.h>
#include "E101.h"
#include "RobotFunction.h"

int main() {
	init();
	bool debug = false;
			
			
  
  //Q1 open gate logic
	gateSequence();
	sleep1(1,0);
  
  
  //Q2 follow line logic
	char Q2 = 0;
	while (Q2 == 0) {
		double speedMultiplier = 0.95; //change this during testing
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
	double speedMultiplier = 1.05; //change this during testing
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
		if(debug) {printf("Line Error: %d", lineError);}
		if (lineError == 100000) {//if no more line ahead then try turning left or right
			lineOutputLeft = seeLineY(linePositionLeft);
			if(debug) {printf("output left: %d\n", lineOutputLeft);}
			lineOutputRight = seeLineY(linePositionRight);
			if(debug){printf("output right: %d\n", lineOutputRight);}
			if(lineOutputLeft != 100000) {//turn left
				if(debug){printf("turning left\n");}
				turnLeft(0, 100000);
				while(seeLineX(linePositionX)== 100000 || seeLineX(linePositionX) <= -10) {
					turnLeft(0, 30000);
				}
			} else if (lineOutputRight !=100000) {//turn right
				if(debug){printf("turning right\n");}
				turnRight(0, 100000);
				while(seeLineX(linePositionX)== 100000 || seeLineX(linePositionX) >= 10) {
					turnRight(0, 30000);
				}
			} else {//turn around
				turnRight(0, 100000);
				while(seeLineX(linePositionX)== 100000 || seeLineX(linePositionX) >= 10) {
					turnRight(0, 30000);
				}
				if(debug){printf("turning around\n");}
			}
			sleep1(0,10000);
		} else {
			if(lineError == 100001) {
				lineError = 0;
			}
			if(debug){printf("going straigt\n");}
			setSpeedSlow(lineError*speedMultiplier) ;
			sleep1(0,10000);
		}
	  
		redLineValue = seeRedLine(linePositionX);
		if (redLineValue == 100002){
			Q3 = 1;
		}
	}


	//Q4 Clusterfuck
	setSpeed(0);
	sleep1(0, 500000);
	int wallLeft;
	int wallRight;
	int wallFront;
	linePositionX = 120;
	bool redLine = false;
	bool waiting = true;
	while(true){
		while(!redLine){
			wallFront = seeIR(2); //Checks distance of wall in front
			if(wallFront >= 220){ //220 is distance we want to turn at
				//If there is a wall in front and we need to turn
				wallLeft = seeIR(3); //Checks distance of wall at left
				wallRight = seeIR(1); //Checks distance of wall at right
			
				if (wallLeft > 200){ //Turn Right (Possibly need smaller value)
					turnRightIR();
				}
				else if (wallRight > 200){ //Turn Left (Possibly need smaller value)
					turnLeftIR();
				}
			} else {
				//If there isn't a wall in front and we want to turn
				wallLeft = seeIR(3); //Checks distance of wall at left
				wallRight = seeIR(1); //Checks distance of wall at right
				if(wallLeft > 600){
					while(wallLeft > 550){
						set_motor(2, 140);
						sleep1(0, 100);
						set_motor(1, -140);
						sleep1(0,10000);
						wallLeft = seeIR(3);
					}
				
				}
				if(wallRight > 600){
					while(wallRight > 550){
						set_motor(1, 140);
						sleep1(0, 100);
						set_motor(2, -140);
						sleep1(0,10000);
						wallRight = seeIR(1);
					}
				}else{
				
					set_motor(1, 80);
  					sleep1(0, 100);
  					set_motor(2, 80);
  					sleep1(0, 100000);
					redLineValue = seeRedLine(linePositionX);
	 				if (redLineValue == 100002){
						redLine = true;
					}
				}
			}
		}
		//if we see the gate do this
		if(debug){printf("Red Line Detected\n");}
		set_motor(1, 0);
		sleep1(0,100);
		set_motor(2, 0);
		wallFront = seeIR(2);
		while(waiting){
			if(wallFront > 200){ //Need different value
				while(wallFront > 150){
					sleep1(0, 20000);
					wallFront= seeIR(2);
					if(debug){printf("Seen Gate Waiting\n");}
				}
				waiting = false;	
			} else if(wallFront < 151){
				sleep1(0,20000);
				if(debug){printf("Waiting for gate\n");}
			}
			wallFront= seeIR(2);
		}
		redLine = false;
		setSpeed(0);
		sleep1(0, 200000);
		if(debug){printf("Moving on\n");}
	}	
	
	return 0;
}

