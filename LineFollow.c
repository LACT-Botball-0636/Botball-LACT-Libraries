#include <kipr/botball.h>
#include "linefollow.h"

void go_to_line(int speed) {
  drive(speed * SPD_L_F / MAX_SPEED, speed * SPD_R_F / MAX_SPEED);
  while (analog(LEFT_LINE) < LEFT_BLACK || analog(RIGHT_LINE) < RIGHT_BLACK) {
    if (analog(RIGHT_LINE) > RIGHT_BLACK)
      drive(speed * SPD_L_F / MAX_SPEED, 0);
    else if (analog(LEFT_LINE) > LEFT_BLACK)
      drive(0, speed * SPD_R_F / MAX_SPEED);
    else if (analog(LEFT_LINE) <= LEFT_BLACK && analog(RIGHT_LINE) <= RIGHT_BLACK)
      drive(speed, speed);
    msleep(1);
  }
  ao();
}

void line_follow(int dist, int speed) {
  drive(speed, speed);
  long leftTarg = gmpc(MOT_LEFT) + dist * CMtoBEMF;
  long rightTarg = gmpc(MOT_RIGHT) + dist * CMtoBEMF;
  while (gmpc(MOT_RIGHT) < rightTarg || gmpc(MOT_LEFT) < leftTarg) {
    if (analog(LEFT_LINE) > LEFT_BLACK)
      drive(speed * .75, speed * 1.25);
    else if (analog(RIGHT_LINE) > RIGHT_BLACK)
      drive(speed * 1.25, speed * .75);
    else
      drive(speed, speed);
    msleep(1);
  }
  ao();
}
