#include "RobotFunction.h"
#include "E101.h"
#include <stdio.h>

//Average 5 Readings
int see() {
	int IR;
  int count = 5;
  int i = 0;
  int totalReading = 0;
	while (i<count) {
		IR = read_analog(0);
    totalReading = totalReading + IR;
		sleep1(0,100);
		i++;
	}
	int averageReading = totalReading/count;
	printf("%d", averageReading);
	return averageReading;
}

//Drive forward
int driveFoward(int time_microseconds) {
  int time_seconds = 0;
  while(time_microseconds > 1000000) {
    time_microseconds = time_microseconds - 1000000;
    time_seconds++;
  }
  set_motor(1, 255);
  sleep1(0, 100);
  set_motor(2, -255);
  sleep1(time_seconds, time_microseconds);
  return 0;
}

//Turn Left
int turn_left (int time_microseconds) {
  int speed = 225;
	int time_seconds = 0;
	while(time_microseconds > 1000000) {
	  time_microseconds = time_microseconds - 1000000;
	  time_seconds++;
	}
	stop(1);
	stop(2); //stops robot in case its going too fast
	set_motor(1, speed); //assuming motor 1 is the right motor
	sleep1(time_seconds, time_microseconds);
	set_motor(2, speed*-1);
  stop(1);
	stop(2);
	return 0;
}

//Turn Right
int turn_right (int time_microseconds) {
  int speed = 225;
	int time_seconds = 0;
	while(time_microseconds > 1000000) {
	  time_microseconds = time_microseconds - 1000000;
	  time_seconds++;
	}
	stop(1);
	stop(2); //stops robot in case its going too fast
	set_motor(2, speed); //assuming motor 2 is the left motor
	sleep1(time_seconds, time_microseconds);
	set_motor(1, speed*-1);
  stop(1);
	stop(2);
	return 0;
}

//Go back slowly
int slowBackward(int time_microseconds) {
  int time_seconds = 0;
	while(time_microseconds > 1000000) {
	  time_microseconds = time_microseconds - 1000000;
	  time_seconds++;
	}
	set_motor(1, -127);
	sleep1(0, 100);
	set_motor(2, 127);
	sleep1(time_seconds, time_microseconds);
	return 0;
}

//go backwards when you see a thing
int see_and_reverse() {
	int IR;
	int detection_limit = 200;
	while (true) {
		IR = read_analog(0);
		if (IR > detection_limit){
			set_motor(1,255);
			sleep1(0,100);
			set_motor(2,-255);
			sleep1(0,100000);
		} else {
			stop(1);
    	stop(2);
			slowBackward(100000); //make sure to fix when u figure out how to call methods in C
		}
		
	}
	return 0;
}

/* See a line
 *Input Y coordinate of the line to see
 *Output Error from the centre, negative left, positive right
 *100000 output means line lost
 *I00001 output means all white horizontal like (Q3 time)
 */
/*
int seeLineX(int Y) {
	take_picture();
	char lostLineLimit = 5; //change to change how little white you need to turn back (noise)
	char color = 3; //change if we test new colors (0 R, 1 G, 2 B, 3 W)
	char whiteDetectionLimit = 127; //change to detect white at different ranges
	char allWhiteLimit = 310; //change to change when it knows when Q3 is, should be all white across but there could be noise)
	int error = 0;
	char totalWhite = 0;
	char w;
	int i;
	for (i = -160; i<160; i++) {
		w = get_pixel(i+160, Y, color);
		if (w<whiteDetectionLimit) {
			w=0;
		} else {
			w=1;
			totalWhite++;
		}
		error  = error + i*w;
	}
	if (totalWhite < lostLineLimit) {
		return 100000; //100,000 means go back (error cannot get to 100,000 normally)
	} else if (totalWhite > allWhiteLimit) {
		return 100001; //100,001 means switch to Q3 logic
	} else {
		return error; //error code
	}
}
*/
/* See a line at position left or right
 * Input X coordinate of line to see
 * Output position of line on the Y plane
 * Output 100000 if no line
 */

/*
int seeLineY(int X) {
	take_picture();
	char noLineLimit = 5; //change to change how little white you need to determine there is no line
	char color = 3; //change if we test new colors (0 R, 1 G, 2 B, 3 W)
	char whiteDetectionLimit = 127; //change to detect white at different ranges
	char position;
	char w;
	int i;
	for (i = 0; i<240; i++) {
		w = get_pixel(X, i, color);
		if (w<whiteDetectionLimit) {
			w=0;
		} else {
			w=1;
			totalWhite++;
		}
		position  = position + i*w;
	}
	position = (int)((double)position/(double)totalWhite))
	if (totalWhite < lostLineLimit) {
		return 100000; //100,000 means go back (error cannot get to 100,000 normally)
	} else {
		return position; //error code
	}
}
*/

/*Set Speed
 * Input: speed factor (left negative, right positiuve)
 * Changes speed to turn at that rate
 */
int setSpeed (int speedFactor) {
  int cruiseControlForCool = 80; //change to modify normal travel speed
  set_motor(1, cruiseControlForCool + speedFactor);
  sleep1(0, 100);
  set_motor(2, -cruiseControlForCool + speedFactor);
  sleep1(0, 100);
  return 0;
}


// Connect to gate server

int gateSequence (){
	int working = -1; 
	while (working == -1){
		char* serverAddress = "130.195.6.196";
		int serverPort = 1024;
		char* sendMessage = "Hi";
		char* serverMessage = "";
		connect_to_server(serverAddress, serverPort);
		send_to_server(sendMessage);
		receive_from_server(serverMessage);
		working = send_to_server(serverMessage); // -1 output means not working
	}
	return 0; 
}

/*
// Follow the left wall
int followWall(){
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
}

//Checking if wall on left
int detectWallLeft(){
	int switchContact;
	int switchReading = read_analog() //Switch input
	if(){ //Switch is touching wall 
		switchContact = 1; //Sets to 1 if touching wall
	}
	else{
		switchContact = 0; //Sets to 0 if not touching wall
	}
	return switchContact; //Returns 1 or 0 for use in followWall
}

//Checking if wall on right
int detectWallRight(){
	int switchContact;
	int switchReading = read_analog() //Switch input
	if(){ //Switch is touching wall 
		switchContact = 1; //Sets to 1 if touching wall
	}
	else{
		switchContact = 0; //Sets to 0 if not touching wall
	}
	return switchContact; //Returns 1 or 0 for use in followWall
}

//Checking if wall in front
int seeWallFront(){
	int wallFront;
	int cameraReading = read_analog() //Camera's input;
	if (cameraReading => ) //Insert a distance value{
		wallFront = 1;
	}
	else{
		wallFront = 0;
	}
	return wallFront;
}
*/

/*takes a picture, converts it to black and white, and displays it
 *use to test colour limit
*/ 

int testSee() {
	take_picture();
	display_picture(5,0);
	int color = 3;
	char w;
	int y;
	int x;
	int whiteDetectionLimit = 127; //change to detect white at different ranges
	for (y=0; y<320; y++) {
		for (x=0; x<240; x++) {
			w = get_pixel(x, y, color);
			if (w<whiteDetectionLimit) {
			w=0;
			} else {
			w=255;
			}
			set_pixel(x, y, w, w, w);
		}
	}
	display_picture(5,0);
	return 0;
}

//print some stuff (testing)
int testPrint() {
	int i;
	for (i=0; i<=5; i++) {
		printf("%d\n", i);
	}
	return 0;
}
