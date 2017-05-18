#include  <stdio.h>
#include  <time.h>
#include "E101.h"

/* Stops robot
 * doesn't call init() as that was already called and is why we're still running
 */
int  main(){
  init();
  stop(1);
  return  0;
}

/* Put this in the home directory and compile it with
 *g++ RobotStop.cpp -le101 -o stop
 *chmod +x stop
 *sudo ./stop
 */
