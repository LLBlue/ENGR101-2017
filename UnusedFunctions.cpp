
//Drive forward
int driveFoward(int time_microseconds) {
  int time_seconds = 0;
  while(time_microseconds > 1000000) {
    time_microseconds = time_microseconds - 1000000;
    time_seconds++;
  }
  set_motor(1, 255);
  sleep1(0, 100);
  set_motor(2, 255);
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
	set_motor(2, speed); //assuming motor 1 is the right motor
	set_motor(1, speed*-1);
	sleep1(time_seconds, time_microseconds);
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
	set_motor(1, speed); //assuming motor 2 is the left motor
	set_motor(2, speed*-1);
	sleep1(time_seconds, time_microseconds);
  	stop(1);
	stop(2);
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
			set_motor(2,255);
			sleep1(0,100000);
		} else {
			stop(1);
    	stop(2);
			slowBackward(100000); //make sure to fix when u figure out how to call methods in C
		}
		
	}
	return 0;
}
