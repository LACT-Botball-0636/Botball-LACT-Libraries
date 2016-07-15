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

void right(int degrees, double radius) {
  long left_arc = ((2 * radius + ROBOT_DIAMETER) * CM_TO_BEMF * M_PI) * (degrees / 360.);
  long right_arc = ((2 * radius - ROBOT_DIAMETER) * CM_TO_BEMF * M_PI) * (degrees / 360.);
  if (left_arc == 0l) {
    printf("Error, no turn. Aborting.");
    return;
  }
  int turn_r_speed = round(((float)right_arc / (float)left_arc) * SPD_R_TURN);
  if (turn_r_speed < 0)
    turn_r_speed = -turn_r_speed;
  if (left_arc > 0l)
    mav(MOT_LEFT, SPD_L_F);
  else
    mav(MOT_LEFT, -SPD_L_B);
  if (right_arc > 0l)
    mav(MOT_RIGHT, turn_r_speed);
  else
    mav(MOT_RIGHT, -turn_r_speed);
  left_arc += gmpc(MOT_LEFT);
  right_arc += gmpc(MOT_RIGHT);
  if (right_arc - gmpc(MOT_RIGHT) > 0l) {
    if (left_arc - gmpc(MOT_LEFT) > 0l) {
      while (right_arc > gmpc(MOT_RIGHT) || left_arc > gmpc(MOT_LEFT)) {
	    if (right_arc < gmpc(MOT_RIGHT))
		  freeze(MOT_RIGHT);
	    if (left_arc < gmpc(MOT_LEFT))
		  freeze(MOT_LEFT);
      }
    } else {
      while (right_arc > gmpc(MOT_RIGHT) || left_arc < gmpc(MOT_LEFT)) {
	    if (right_arc < gmpc(MOT_RIGHT))
		  freeze(MOT_RIGHT);
	    if (left_arc > gmpc(MOT_LEFT))
		  freeze(MOT_LEFT);
      }
    }
  } else {
    if (left_arc - gmpc(MOT_LEFT) > 0l) {
      while (right_arc < gmpc(MOT_RIGHT) || left_arc > gmpc(MOT_LEFT)) {
	    if (right_arc > gmpc(MOT_RIGHT))
		  freeze(MOT_RIGHT);
	    if (left_arc < gmpc(MOT_LEFT))
		  freeze(MOT_LEFT);
      }
    } else {
      while (right_arc < gmpc(MOT_RIGHT) || left_arc < gmpc(MOT_LEFT)) {
	    if (right_arc > gmpc(MOT_RIGHT))
  		  freeze(MOT_RIGHT);
	    if (left_arc > gmpc(MOT_LEFT))
		  freeze(MOT_LEFT);
      }
    }
  }
  drive_freeze();
}

void right_speed(int degrees, double radius, int speed) {
  long left_arc = ((2 * radius + ROBOT_DIAMETER) * CM_TO_BEMF * M_PI) * (degrees / 360.);
  long right_arc = ((2 * radius - ROBOT_DIAMETER) * CM_TO_BEMF * M_PI) * (degrees / 360.);
  if (left_arc == 0l) {
    printf("Error, no turn. Aborting.");
    return;
  }
  int turn_r_speed = round(((float)right_arc / (float)left_arc) * SPD_R_TURN);
  if (turn_r_speed < 0)
    turn_r_speed = -turn_r_speed;
  if (left_arc > 0l)
    mav(MOT_LEFT, SPD_L_F * speed / MAX_SPEED);
  else
    mav(MOT_LEFT, -SPD_L_B * speed / MAX_SPEED);
  if (right_arc > 0l)
    mav(MOT_RIGHT, turn_r_speed * speed / MAX_SPEED);
  else
    mav(MOT_RIGHT, -turn_r_speed * speed / MAX_SPEED);
  left_arc += gmpc(MOT_LEFT);
  right_arc += gmpc(MOT_RIGHT);
  if (right_arc - gmpc(MOT_RIGHT) > 0l) {
    if (left_arc - gmpc(MOT_LEFT) > 0l) {
      while (right_arc > gmpc(MOT_RIGHT) || left_arc > gmpc(MOT_LEFT)) {
	    if (right_arc < gmpc(MOT_RIGHT))
		  freeze(MOT_RIGHT);
	    if (left_arc < gmpc(MOT_LEFT))
		  freeze(MOT_LEFT);
      }
    } else {
      while (right_arc > gmpc(MOT_RIGHT) || left_arc < gmpc(MOT_LEFT)) {
	    if (right_arc < gmpc(MOT_RIGHT))
		  freeze(MOT_RIGHT);
	    if (left_arc > gmpc(MOT_LEFT))
		  freeze(MOT_LEFT);
      }
    }
  } else {
    if (left_arc - gmpc(MOT_LEFT) > 0l) {
      while (right_arc < gmpc(MOT_RIGHT) || left_arc > gmpc(MOT_LEFT)) {
	    if (right_arc > gmpc(MOT_RIGHT))
		  freeze(MOT_RIGHT);
	    if (left_arc < gmpc(MOT_LEFT))
		  freeze(MOT_LEFT);
      }
    } else {
      while (right_arc < gmpc(MOT_RIGHT) || left_arc < gmpc(MOT_LEFT)) {
	    if (right_arc > gmpc(MOT_RIGHT))
  		  freeze(MOT_RIGHT);
	    if (left_arc > gmpc(MOT_LEFT))
		  freeze(MOT_LEFT);
      }
    }
  }
  drive_freeze();
}

void left(int degrees, double radius) {
  long left_arc = ((2 * radius - ROBOT_DIAMETER) * CM_TO_BEMF * M_PI) * (degrees / 360.);
  long right_arc = ((2 * radius + ROBOT_DIAMETER) * CM_TO_BEMF * M_PI) * (degrees / 360.);
  if (right_arc == 0l) {
    printf("Error, no turn. Aborting.");
    return;
  }
  int turn_l_speed = round((float)left_arc / (float)right_arc * SPD_L_TURN);
  if (turn_l_speed < 0)
    turn_l_speed = -turn_l_speed;
  if (right_arc  > 0l)
    mav(MOT_RIGHT, SPD_R_F);
  else
    mav(MOT_RIGHT, -SPD_R_B);
  if (left_arc > 0l)
    mav(MOT_LEFT, turn_l_speed);
  else
    mav(MOT_LEFT, -turn_l_speed);
  right_arc += gmpc(MOT_RIGHT);
  left_arc += gmpc(MOT_LEFT);
  if (left_arc - gmpc(MOT_LEFT) > 0l) {
    if (right_arc - gmpc(MOT_RIGHT) > 0l) {
      while (left_arc > gmpc(MOT_LEFT) || right_arc > gmpc(MOT_RIGHT)) {
	    if (left_arc < gmpc(MOT_LEFT))
		  freeze(MOT_LEFT);
	    if (right_arc < gmpc(MOT_RIGHT))
		  freeze(MOT_RIGHT);
      }
    } else {
      while (left_arc > gmpc(MOT_LEFT) || right_arc < gmpc(MOT_RIGHT)) {
	    if (left_arc < gmpc(MOT_LEFT))
		  freeze(MOT_LEFT);
	    if (right_arc > gmpc(MOT_RIGHT))
		  freeze(MOT_RIGHT);
      }
    }
  } else {
    if (right_arc - gmpc(MOT_RIGHT) > 0l) {
      while (left_arc < gmpc(MOT_LEFT) || right_arc > gmpc(MOT_RIGHT)) {
	    if (left_arc > gmpc(MOT_LEFT))
		  freeze(MOT_LEFT);
	    if (right_arc < gmpc(MOT_RIGHT))
		  freeze(MOT_RIGHT);
      }
    } else {
      while (left_arc < gmpc(MOT_LEFT) || right_arc < gmpc(MOT_RIGHT)) {
	    if (left_arc > gmpc(MOT_LEFT))
		  freeze(MOT_LEFT);
	    if (right_arc > gmpc(MOT_RIGHT))
		  freeze(MOT_RIGHT);
      }
    }
  }
  drive_off();
}

void left_speed(int degrees, double radius, int speed) {
  long left_arc = ((2 * radius - ROBOT_DIAMETER) * CM_TO_BEMF * M_PI) * (degrees / 360.);
  long right_arc = ((2 * radius + ROBOT_DIAMETER) * CM_TO_BEMF * M_PI) * (degrees / 360.);
  if (right_arc == 0l) {
    printf("Error, no turn. Aborting.");
    return;
  }
  int turn_l_speed = round((float)left_arc / (float)right_arc * SPD_L_TURN);
  if (turn_l_speed < 0)
    turn_l_speed = -turn_l_speed;
  if (right_arc  > 0l)
    mav(MOT_RIGHT, SPD_R_F * speed / MAX_SPEED);
  else
    mav(MOT_RIGHT, -SPD_R_B * speed / MAX_SPEED);
  if (left_arc > 0l)
    mav(MOT_LEFT, turn_l_speed * speed / MAX_SPEED);
  else
    mav(MOT_LEFT, -turn_l_speed * speed / MAX_SPEED);
  right_arc += gmpc(MOT_RIGHT);
  left_arc += gmpc(MOT_LEFT);
  if (left_arc - gmpc(MOT_LEFT) > 0l) {
    if (right_arc - gmpc(MOT_RIGHT) > 0l) {
      while (left_arc > gmpc(MOT_LEFT) || right_arc > gmpc(MOT_RIGHT)) {
	    if (left_arc < gmpc(MOT_LEFT))
		  freeze(MOT_LEFT);
	    if (right_arc < gmpc(MOT_RIGHT))
		  freeze(MOT_RIGHT);
      }
    } else {
      while (left_arc > gmpc(MOT_LEFT) || right_arc < gmpc(MOT_RIGHT)) {
	    if (left_arc < gmpc(MOT_LEFT))
		  freeze(MOT_LEFT);
	    if (right_arc > gmpc(MOT_RIGHT))
		  freeze(MOT_RIGHT);
      }
    }
  } else {
    if (right_arc - gmpc(MOT_RIGHT) > 0l) {
      while (left_arc < gmpc(MOT_LEFT) || right_arc > gmpc(MOT_RIGHT)) {
	    if (left_arc > gmpc(MOT_LEFT))
		  freeze(MOT_LEFT);
	    if (right_arc < gmpc(MOT_RIGHT))
		  freeze(MOT_RIGHT);
      }
    } else {
      while (left_arc < gmpc(MOT_LEFT) || right_arc < gmpc(MOT_RIGHT)) {
	    if (left_arc > gmpc(MOT_LEFT))
		  freeze(MOT_LEFT);
	    if (right_arc > gmpc(MOT_RIGHT))
		  freeze(MOT_RIGHT);
      }
    }
  }
  drive_off();
}

void forward(int distance) {
  if (distance < 0) {
    distance = -distance;
    printf("Error, negative distance! Switching to positive\n");
  }
  long move_distance = distance * CM_TO_BEMF;
  long l_target = gmpc(MOT_LEFT) + move_distance;
  long r_target = gmpc(MOT_RIGHT) + move_distance;
  mav(MOT_LEFT, SPD_L_F);
  mav(MOT_RIGHT, SPD_R_F);
  while (gmpc(MOT_LEFT) < l_target && gmpc(MOT_RIGHT) < r_target) {
    if (gmpc(MOT_LEFT) >= l_target)
      freeze(MOT_LEFT);
    if (gmpc(MOT_RIGHT) >= r_target)
      freeze(MOT_RIGHT);
  }
  drive_freeze();
}

void forward_speed(int distance, int speed) {
  if (distance < 0) {
    distance = -distance;
    printf("Error, negative distance! Switching to positive\n");
  }
  long move_distance = distance * CM_TO_BEMF;
  long l_target = gmpc(MOT_LEFT) + move_distance;
  long r_target = gmpc(MOT_RIGHT) + move_distance;
  mav(MOT_LEFT, speed * SPD_L_F / MAX_SPEED);
  mav(MOT_RIGHT, speed * SPD_R_F / MAX_SPEED);
  while (gmpc(MOT_LEFT) < l_target && gmpc(MOT_RIGHT) < r_target) {
    if (gmpc(MOT_LEFT) >= l_target)
      freeze(MOT_LEFT);
    if (gmpc(MOT_RIGHT) >= r_target)
      freeze(MOT_RIGHT);
  }
  drive_freeze();
}

void backward(int distance) {
  if (distance < 0) {
    distance = -distance;
    printf("Error, negative distance! Switching to positive\n");
  }
  long move_distance = distance * CM_TO_BEMF;
  long l_target = gmpc(MOT_LEFT) - move_distance;
  long r_target = gmpc(MOT_RIGHT) - move_distance;
  mav(MOT_LEFT, -SPD_L_B);
  mav(MOT_RIGHT, -SPD_R_B);
  while (gmpc(MOT_LEFT) > l_target && gmpc(MOT_RIGHT) > r_target) {
    if (gmpc(MOT_LEFT) <= l_target)
	  freeze(MOT_LEFT);
    if (gmpc(MOT_RIGHT) <= r_target)
	  freeze(MOT_RIGHT);
  }
  drive_freeze();
}

void backward_speed(int distance, int speed) {
  if (distance < 0) {
    distance = -distance;
    printf("Error, negative distance! Switching to positive\n");
  }
  long move_distance = distance * CM_TO_BEMF;
  long l_target = gmpc(MOT_LEFT) - move_distance;
  long r_target = gmpc(MOT_RIGHT) - move_distance;
  mav(MOT_LEFT, -speed * SPD_L_B / MAX_SPEED);
  mav(MOT_RIGHT, -speed * SPD_R_B / MAX_SPEED);
  while (gmpc(MOT_LEFT) > l_target && gmpc(MOT_RIGHT) > r_target) {
    if (gmpc(MOT_LEFT) <= l_target)
	  freeze(MOT_LEFT);
    if (gmpc(MOT_RIGHT) <= r_target)
	  freeze(MOT_RIGHT);
  }
  drive_freeze();
}

void forward_gyro(int distance, int speed) {
  if (distance < 0) {
    distance = -distance;
    printf("Error, negative distance! Switching to positive\n");
  }
  if (speed >= 1450) {
    speed = 1400;  // Cannot be full speed or slightly less otherwise gyro corrections won't work
  }

  // TODO: Some gyro calibration code here - Kipr has a function but hasn't implemented yet

  long move_distance = distance * CM_TO_BEMF;
  long l_target = gmpc(MOT_LEFT) + move_distance;
  long r_target = gmpc(MOT_RIGHT) + move_distance;

  mav(MOT_LEFT, speed);
  mav(MOT_RIGHT, speed);

  while (gmpc(MOT_LEFT) > l_target && gmpc(MOT_RIGHT) > r_target) {
    // Not sure which one to use here
    double gyroX = gyro_x();
    if (gyroX > 0.1) {
      mav(MOT_RIGHT, speed*Kp);
      mav(MOT_LEFT, speed);
      msleep(10);
    }
    if (gyroX < 0.1) {
      mav(MOT_LEFT, speed*Kp);
      mav(MOT_RIGHT, speed);
      msleep(10);
    }

    if (gmpc(MOT_LEFT) <= l_target)
	  freeze(MOT_LEFT);
    if (gmpc(MOT_RIGHT) <= r_target)
	  freeze(MOT_RIGHT);
  }
}
