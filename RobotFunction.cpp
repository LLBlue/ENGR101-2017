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
	}
	int averageReading = totalReading/count;
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
int seeLineX(int Y) {
	take_picture();
	int lostLineLimit = 5; //change to change how little white you need to turn back (noise)
	int color = 3; //change if we test new colors (0 R, 1 G, 2 B, 3 W)
	int whiteDetectionLimit = 127; //change to detect white at different ranges
	int allWhiteLimit = 340; //change to change when it knows when Q3 is, should be all white across but there could be noise)
	int error = 0;
	int totalWhite = 0;
	int w;
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

// Connect to gate server
/*
int gateSequence (){
	char* serverAddress = "Server";
	int serverPort = 000000;
	char* sendMessage = "Hi";
	connect_to_server(serverAddress, serverPort);
	send_to_server(sendMessage);
	char* serverMessage = receive_from_server("asdfghjklqwertyuiopqazw");
	send_to_server(serverMessage);
	return 0;
}
*/
/*takes a picture, converts it to black and white, and displays it
 *use to test colour limit
 */

int testSee() {
	take_picture();
	display_picture(1,0);
	int color = 3;
	int w;
	int y;
	int x;
	int whiteDetectionLimit = 127; //change to detect white at different ranges
	for (y=0; y<240; y++) {
		for (x=0; x<360; x++) {
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
