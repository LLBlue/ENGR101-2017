#include  <stdio.h>
#include  <time.h>
#include "E101.h"
#include "RobotFunction.h"

//setting this up now where the main logic and stuff goes idk

/* Test things
*/
int  main(){
  int working;
  init();
  testSee();
  return  0;
}
/* Real Code
*/
/*
int main() {
  init();
  //Q1 open gate logic
  gateSequence();
  //Q2 follow line logic
  double speedMultiplier = 0.5; //change this during testing
  int linePosition;
  lineError = seeLineX(120); //change line position 
  if (lineError == 100000) {
    //go backwards
    sleep1(0,10000);
  } else if (lineError == 100001) {
    //goto Q3
  } else {
    setSpeed(lineError*speedMultiplier) 
    sleep1(0,10000);
  }
  //Q3 solve line maze
  //Q4 solve wall maze
  return 0;
}
*/
