#include "drive.h"
#include <math.h>

void drive_off() {
  off(MOT_RIGHT);
  off(MOT_LEFT);
}

void drive_freeze() {
  freeze(MOT_RIGHT);
  freeze(MOT_LEFT);
}

void drive_clear() {
  cmpc(MOT_RIGHT);
  cmpc(MOT_LEFT);
}

void drive(int left_speed, int right_speed) {
  mav(MOT_LEFT, left_speed);
  mav(MOT_RIGHT, right_speed);
}

void right(float degrees, float radius) {
  long left_arc = ((2 * radius + ROBOT_DIAMETER) * CM_TO_BEMF * M_PI) * (degrees / 360.);
  long right_arc = ((2 * radius - ROBOT_DIAMETER) * CM_TO_BEMF * M_PI) * (degrees / 360.);
  if(left_arc == 0l) {
    printf("Error, no turn. Aborting.");
    return;
  }
  int turn_r_speed = round(((float)right_arc / (float)left_arc) * SPD_R_TURN);
  if(turn_r_speed < 0)
    turn_r_speed = -turn_r_speed;
  if(left_arc > 0l)
    mav(MOT_LEFT, SPD_L_F);
  else
    mav(MOT_LEFT, -SPD_L_B);
  if(right_arc > 0l)
    mav(MOT_RIGHT, turn_r_speed);
  else
    mav(MOT_RIGHT, -turn_r_speed);
  left_arc += gmpc(MOT_LEFT);
  right_arc += gmpc(MOT_RIGHT);
  if(right_arc - gmpc(MOT_RIGHT) > 0l) {
    if(left_arc - gmpc(MOT_LEFT) > 0l) {
      while(right_arc > gmpc(MOT_RIGHT) || left_arc > gmpc(MOT_LEFT)) {
	    if(right_arc < gmpc(MOT_RIGHT))
		  freeze(MOT_RIGHT);
	    if(left_arc < gmpc(MOT_LEFT))
		  freeze(MOT_LEFT);
      }
    } else {
      while(right_arc > gmpc(MOT_RIGHT) || left_arc < gmpc(MOT_LEFT)) {
	    if(right_arc < gmpc(MOT_RIGHT))
		  freeze(MOT_RIGHT);
	    if(left_arc > gmpc(MOT_LEFT))
		  freeze(MOT_LEFT);
      }
    }
  } else {
    if(left_arc - gmpc(MOT_LEFT) > 0l) {
      while(right_arc < gmpc(MOT_RIGHT) || left_arc > gmpc(MOT_LEFT)) {
	    if(right_arc > gmpc(MOT_RIGHT))
		  freeze(MOT_RIGHT);
	    if(left_arc < gmpc(MOT_LEFT))
		  freeze(MOT_LEFT);
      }
    } else {
      while(right_arc < gmpc(MOT_RIGHT) || left_arc < gmpc(MOT_LEFT)) {
	    if(right_arc > gmpc(MOT_RIGHT))
  		  freeze(MOT_RIGHT);
	    if(left_arc > gmpc(MOT_LEFT))
		  freeze(MOT_LEFT);
      }
    }
  }
  drive_freeze();
}

void left (float degrees, float radius) {
  long left_arc = ((2 * radius - ROBOT_DIAMETER) * CM_TO_BEMF * M_PI) * (degrees / 360.);
  long right_arc = ((2 * radius + ROBOT_DIAMETER) * CM_TO_BEMF * M_PI) * (degrees / 360.);
  if(right_arc == 0l) {
    printf("Error, no turn. Aborting.");
    return;
  }
  int turn_l_speed = round((float)left_arc / (float)right_arc * SPD_L_TURN);
  if(turnlspeed < 0)
    turnlspeed = -turnlspeed;
  if(right_arc  > 0l)
    mav(MOT_RIGHT, SPD_R_F);
  else
    mav(MOT_RIGHT, -SPD_R_B);
  if(left_arc > 0l)
    mav(MOT_LEFT, turn_l_speed);
  else
    motor(MOT_LEFT, -turn_l_speed);
  right_arc += gmpc(MOT_RIGHT);
  left_arc += gmpc(MOT_LEFT);
  if(left_arc - gmpc(MOT_LEFT) > 0l) {
    if(right_arc - gmpc(MOT_RIGHT) > 0l) {
      while(left_arc > gmpc(MOT_LEFT) || right_arc > gmpc(MOT_RIGHT)) {
	    if(left_arc < gmpc(MOT_LEFT))
		  freeze(MOT_LEFT);
	    if(right_arc < gmpc(MOT_RIGHT))
		  freeze(MOT_RIGHT);
      }
    } else {
      while(left_arc > gmpc(MOT_LEFT) || right_arc < gmpc(MOT_RIGHT)) {
	    if(left_arc < gmpc(MOT_LEFT))
		  freeze(MOT_LEFT);
	    if(right_arc > gmpc(MOT_RIGHT))
		  freeze(MOT_RIGHT);
      }
    }
  } else {
    if(right_arc - gmpc(MOT_RIGHT) > 0l) {
      while(left_arc < gmpc(MOT_LEFT) || right_arc > gmpc(MOT_RIGHT)) {
	    if(left_arc > gmpc(MOT_LEFT))
		  freeze(MOT_LEFT);
	    if(right_arc < gmpc(MOT_RIGHT))
		  freeze(MOT_RIGHT);
      }
    } else {
      while(left_arc < gmpc(MOT_LEFT) || right_arc < gmpc(MOT_RIGHT)) {
	    if(left_arc > gmpc(MOT_LEFT))
		  freeze(MOT_LEFT);
	    if(right_arc > gmpc(MOT_RIGHT))
		  freeze(MOT_RIGHT);
      }
    }
  }

  drive_off();
  msleep(30l);
}

void forward (int distance, int speed) {
  if(distance < 0) {
    distance = -distance;
    printf("Error, negative distance! Switching to positive\n");
  }
  long move_distance = distance * CM_TO_BEMF;
  long l_target = gmpc(MOT_LEFT) + move_distance;
  long r_target = gmpc(MOT_RIGHT) + move_distance;
  mav(MOT_LEFT, speed);
  mav(MOT_RIGHT, speed);
  while(gmpc(MOT_LEFT) < l_target && gmpc(MOT_RIGHT) < r_target) {
    if(gmpc(MOT_LEFT) >= l_target)
      freeze(MOT_LEFT);
    if(gmpc(MOT_RIGHT) >= r_target)
      freeze(MOT_RIGHT);
  }
  drive_freeze();
}

void backward(int distance, int speed) {
  if(distance < 0) {
    distance = -distance;
    printf("Error, negative distance! Switching to positive\n");
  }
  long move_distance = distance * CM_TO_BEMF;
  long l_target = gmpc(MOT_LEFT) - move_distance;
  long r_target = gmpc(MOT_RIGHT) - move_distance;
  mav(MOT_LEFT, -speed);
  mav(MOT_RIGHT, -speed);
  while(gmpc(MOT_LEFT) > l_target && gmpc(MOT_RIGHT) > r_target) {
    if(gmpc(MOT_LEFT) <= l_target)
	  freeze(MOT_LEFT);
    if(gmpc(MOT_RIGHT) <= r_target)
	  freeze(MOT_RIGHT);
  }
  drive_freeze();
}
