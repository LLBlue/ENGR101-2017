#ifndef ROBOTFUNCTION_H_INCLUDED
#define ROBOTFUNCTION_H_INCLUDED
int seeIR();
int slowBackward(int timeSeconds, int timeMicroseconds);
int seeLineX(int Y);
int seeLineY(int X);
int setSpeed(int speedFactor);
int gateSequence ();
int detectLeftWall();
int detectRightWall();
int seeWallFront();
int testSee();
int testPrint();
#endif
