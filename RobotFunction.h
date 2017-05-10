#ifndef ROBOTFUNCTION_H_INCLUDED
#define ROBOTFUNCTION_H_INCLUDED
int see();
int driveFoward(int time_microseconds);
int turn_left (int time_microseconds);
int turn_right (int time_microseconds);
int slowBackward(int time_microseconds);
int see_and_reverse();
int seeLineX(int Y);
int seeLineY(int X);
int setSpeed();
int gateSequence ();
int followWall();
int detectLeftWall();
int detectRightWall();
int seeWallFront();
int testSee();
int testPrint();
#endif
