#include "RobotFunction.h"
#include "E101.h"
#include <stdio.h>

/*Takes a given number of readings from IR sensor and averages them
 */
int seeIR(int channel) {
  int IR;
  int count = 5; //how many readings?
  int i = 0;
  int totalReading = 0;
  while (i<count) {
    IR = read_analog(channel);
    totalReading = totalReading + IR;
    sleep1(0,100);
    i++;
  }
  int averageReading = totalReading/count;
  return averageReading;
}

/*Turns left for a given time then stops
 */
int turnLeft (int seconds, int microseconds) {
  int speed = 200;
	set_motor(2, speed); //assuming motor 1 is the right motor
	sleep1(0, 100);
	set_motor(1, speed*-1);
	sleep1(seconds, microseconds);
	set_motor(1, 0);
	sleep1(0, 100);
	set_motor(2, 0);
	sleep1(0, 100);
	return 0;
}

/*Turns right for a given time then stops
 */
int turnRight (int seconds, int microseconds) {
  int speed = 200;
	set_motor(1, speed); //assuming motor 2 is the left motor
	sleep1(0, 100);
	set_motor(2, speed*-1);
	sleep1(seconds, microseconds);
	set_motor(1, 0);
	sleep1(0, 100);
	set_motor(2, 0);
	sleep1(0, 100);
  	return 0;
}
/*
int turnRightIR (int wallFront) {
	while (wallFront > 230){ //Needs to find better values for checking
		set_motor(2, 140);
		sleep1(0, 100);
		set_motor(1, -140);
		sleep1(0,10000);
		wallFront = seeIR(2);
}
}
*/

/*Turns right until the difference of the distances between the front IR sensor becomes small
 *should become small if there is a straight wall in front (no longer facing a side wall)
 *or if there is empty space (reaings will be near zero)
 */

int turnRightIR() {
	int maxDiff = 50;
	int dist3 = 3000;
	int dist2 = 2000;
	int dist1 = 1000;
	int dist0;
	int diff2;
	int diff1;
	int diff0;
	while (true) {
			dist0 = seeIR(2);
			diff2 = dist2-dist3;
			diff1 = dist1-dist2;
			diff0 = dist0-dist1;
			if(diff0 >= diff1-maxDiff && diff0 <= diff1+maxDiff && diff0 >= diff2-maxDiff && diff0 <= diff2+maxDiff){
				return 0;
			} else {
				turnLeft(0, 50000); //this works
			}
			dist3 = dist2;
			dist2 = dist1;
			dist1 = dist0;
	}
}

/*
int turnLeftIR(int wallFront) {
	while (wallFront > 230){ //Needs to find better values for checking
		set_motor(1, 140);
		sleep1(0, 100);
		set_motor(2, -140);
		sleep1(0,10000);
		wallFront = seeIR(2);
}
}
*/

/*Turns left until the difference of the distances between the front IR sensor becomes small
 *should become small if there is a straight wall in front (no longer facing a side wall)
 *or if there is empty space (reaings will be near zero)
 */

int turnLeftIR() {
	int maxDiff = 50;
	int dist3 = 3000;
	int dist2 = 2000;
	int dist1 = 1000;
	int dist0;
	int diff2;
	int diff1;
	int diff0;
	while (true) {
			dist0 = seeIR(2);
			diff2 = dist2-dist3;
			diff1 = dist1-dist2;
			diff0 = dist0-dist1;
			if(diff0 >= diff1-maxDiff && diff0 <= diff1+maxDiff && diff0 >= diff2-maxDiff && diff0 <= diff2+maxDiff){
				return 0;
			} else {
				turnRight(0, 50000); //also works
			}
		  dist3 = dist2;
			dist2 = dist1;
			dist1 = dist0;
	}
}


/*Goes backwards slowly for a given time
 */
int slowBackward(int timeSeconds, int timeMicroseconds) {
  set_motor(1, -80);
  sleep1(0, 100);
  set_motor(2, -80);
  sleep1(timeSeconds, timeMicroseconds);
  return 0;
}

/* See a line
 *Input Y coordinate of the line to see
 *Output Error from the centre, negative left, positive right
 *From -160 to 160
 *100000 output means line lost
 *I00001 output means all white horizontal like (Q3 time)
 */
int seeLineX(int Y) {
	take_picture();
	char lostLineLimit = 5; //change to change how little white you need to turn back (noise)
	char color = 3; //change if we test new colors (0 R, 1 G, 2 B, 3 W)
	char whiteDetectionLimit = 127; //change to detect white at different ranges
	int allWhiteLimit = 200; //change to change when it knows when Q3 is, should be all white across but there could be noise)
	double error = 0;
	double totalWhite = 0;
	char w;
	int i;
	for (i = -160; i<160; i++) {
		w = get_pixel(Y, i+160, color);
		if (w>whiteDetectionLimit) {
			totalWhite++;
			error = error+i;
		}
	}
	int totalError = (int)(error/totalWhite);
	if (totalWhite < lostLineLimit) {
		return 100000; //100,000 means go back (error cannot get to 100,000 normally)
		
	} else if (totalWhite > allWhiteLimit) {
		return 100001; //100,001 means switch to Q3 logic
		
	} else {
		return totalError; //error code
		
	}
}

/* See a line at position left or right
 * Input X coordinate of line to see
 * Output position of line on the Y plane
 * Output 100000 if no line
 */

int seeLineY(int X) {
	take_picture();
	char noLineLimit = 5; //change to change how little white you need to determine there is no line
	char color = 3; //change if we test new colors (0 R, 1 G, 2 B, 3 W)
	char whiteDetectionLimit = 127; //change to detect white at different ranges
	double position;
	char w;
	double totalWhite = 0;
	int i;
	for (i = 0; i<240; i++) {
		w = get_pixel(i, X, color);
		if (w<whiteDetectionLimit) {
			w=0;
		} else {
			w=1;
			totalWhite = totalWhite+1;
		}
		position  = position + i*w;
	}
	int averagePosition = (int)(position/totalWhite);
	if (totalWhite < noLineLimit) {
		return 100000; //100,000 means no line on that side (error cannot get to 100,000 normally)
	} else {
		return averagePosition; //error code
	}
}


/*Set Speed
 * Input: speed factor (left negative, right positive)
 * Changes speed to turn at that rate
 */

int setSpeed (int speedFactor) {
  int cruiseControlForCool = 100; //change to modify normal travel speed
  set_motor(1, cruiseControlForCool + speedFactor);
  sleep1(0, 100);
  set_motor(2, cruiseControlForCool - speedFactor);
  sleep1(0, 100);
  return 0;
}

/*Set Speed Slow
 * Input: speed factor (left negative, right positive)
 * Changes speed to turn at that rate
 * Slower version for doing the maze
 */

int setSpeedSlow (int speedFactor) {
  int cruiseControlForCool = 75; //change to modify normal travel speed
  set_motor(1, cruiseControlForCool + speedFactor);
  sleep1(0, 100);
  set_motor(2, cruiseControlForCool - speedFactor);
  sleep1(0, 100);
  return 0;
}


/*Connects to gate server
 *Loops until it works
 */

int gateSequence (){
	int working = -1; 
	while (working == -1){
		char* serverAddress = "130.195.6.196";
		int serverPort = 1024;
		char* sendMessage = "Please Team 2";
		char serverMessage[24] = {0};
		connect_to_server(serverAddress, serverPort);
		send_to_server(sendMessage);
		working = receive_from_server(serverMessage); // -1 output means not working
		send_to_server(serverMessage); 
	}
	return 0; 
}

//Checking for red line
int seeRedLine(int Y){
	take_picture();
	char red = 0;
	char green = 1;
	char blue = 2;
	char redDetectionLimit = 150;
	char greenDetectionLimit = 100;
	char blueDetectionLimit = 100;
	int redTotal;
	int redDetected = 90;
	char r;
	char g;
	char b;
	int i;
	for (i = -160; i<160; i++){
		r = get_pixel(Y, i+160, red);
		g = get_pixel(Y, i+160, green);
		b = get_pixel(Y, i+160, blue);
		if (r>redDetectionLimit && g<greenDetectionLimit && b<blueDetectionLimit){
			redTotal++;
		}
	}
	if (redTotal>redDetected){
		return 100002;
	}
	else{
		return 0;
	}
}
/*

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
	display_picture(10,0);
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
