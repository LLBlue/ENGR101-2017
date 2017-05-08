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
  working = gateSequence();
  printf("%d", working);
  testPrint();
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
  //Q3 solve line maze
  //Q4 solve wall maze
  return 0;
}
*/
