#ifndef ROBOTFUNCTION_H_INCLUDED
#define ROBOTFUNCTION_H_INCLUDED
int seeIR();
int turnLeft (int seconds, int microseconds);
int turnRight (int seconds, int microseconds);
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
