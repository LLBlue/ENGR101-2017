#ifndef ROBOTFUNCTION_H_INCLUDED
#define ROBOTFUNCTION_H_INCLUDED
int seeIR(int channel);
int turnLeft (int seconds, int microseconds);
int turnRight (int seconds, int microseconds);
int turnRightIR(int wallLeft, int wallFront);
int turnLeftIR(int wallRight, int wallFront);
int slowBackward(int timeSeconds, int timeMicroseconds);
int seeLineX(int Y);
int seeLineY(int X);
int setSpeed(int speedFactor);
int setSpeedSlow (int speedFactor);
int gateSequence ();
int detectLeftWall();
int detectRightWall();
int seeWallFront();
int seeRedLine(int Y);
int testSee();
int testPrint();
#endif
