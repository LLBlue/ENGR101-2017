#include  <stdio.h>
#include  <time.h>
#include "E101.h"

/* Stops robot
 * doesn't call init() as that was already called and is why we're still running
 */
int  main(){
  init();
  set_motor(1, 0);
  sleep1(0, 100);
  set_motor(2, 0);
  return  0;
}

/* Put this in the home directory and compile it with
 *g++ RobotStop.cpp -le101 -o stop
 *chmod +x stop
 *sudo ./stop
 */
