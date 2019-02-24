#include "createDrive.h"
#include <math.h>
/**
 * create_line_follow makes the create line follow. It sticks to the line by slowing down to arc back to the line. 
 * Requires following to be defined:
 * RIGHT_LINE for the tophat sensor on the right side
 * LEFT_LINE for the tophat sensor on the left side
 * dist: distance to travel in centimeters
 * speed: speed to drive at on a range from 0-1000
 */
void create_line_follow(int dist, int speed)
{
  //create_line_follow makes the create line follow for "dist" centimeters at "speed" speed
  
  dist*=10; //Converts centimeters into millimeters
  set_create_distance(0); //Clears create position counter
  create_drive_straight(speed); //Initializes movement
  while(abs(get_create_distance())<abs(dist)) //while distance has not been achieved, perform the following:
  {
    if(analog(LEFT_LINE)>2500)				  //if the left tophat sensor sees black
    {
      create_drive_direct(speed*.75,speed*1.25); //drive to the left
    }
    else if(analog(RIGHT_LINE)>2500)		  //if the right tophat sensor sees black
    {
      create_drive_direct(speed*1.25,speed*.75); //drive to the right
    }
    else									  //if none of the tophat sensors see black
    {
      create_drive_straight(speed);			  //drive straight forward
    }
    msleep(5);
  }
  create_stop();							  //stop the create once distance has been achieved
}
/**
 * create_forward makes the create go forward straight. 
 * Requires no predefined constants
 * dist: distance to travel in centimeters
 * speed: speed to drive at on a range from 0-1000
 */
void create_forward(int dist, int speed)
{
  dist*=10; //Converts centimeters into millimeters
  set_create_distance(0); //Clears create position counter
  create_drive_straight(speed); //Initializes movement
  while(get_create_distance()<dist) //Waits until distance traveled reaches distance
  {
    msleep(1);
  }
  create_stop(); //Stops movement
}
/**
 * create_backward makes the create go backward straight. 
 * Requires no predefined constants
 * dist: distance to travel in centimeters
 * speed: speed to drive at on a range from 0-1000
 */
void create_backward(int dist, int speed)
{
  dist*=10; //Converts centimeters into millimeters
  set_create_distance(0); //Clears create position counter
  create_drive_straight(-speed); //Initializes movement 
  while(get_create_distance()>-dist) //Waits until distance traveled reaches distance
  {
    msleep(1);
  }
  create_stop(); //Stops movement
}
/**
 * create_left makes the create turn left in place. 
 * Requires no predefined constants
 * degrees: angle to turn in degrees
 * speed: speed to drive at on a range from 0-1000
 */
void create_left(int degrees, int speed)
{
  set_create_total_angle(0); //Clears create angle counter
  create_drive_direct(-speed,speed); //Initializes movement
  while(get_create_total_angle()<degrees) //Waits until angle turned reaches degrees
  {
    msleep(5);
  }
  create_stop(); //Stops movement
}
/**
 * create_right makes the create turn right in place. 
 * Requires no predefined constants
 * degrees: angle to turn in degrees
 * speed: speed to drive at on a range from 0-1000
 */
void create_right(int degrees, int speed)
{
  set_create_total_angle(0); //Clears create angle counter
  create_drive_direct(speed,-speed); //Initializes movement
  while(get_create_total_angle()>-degrees) //Waits until angle turned reaches degrees
  {
    msleep(5);
  }
  create_stop(); //Stops movement
}

/**
 * create_forward_gyro makes the create go forward straight using the gyrometer 
 * Requires GYRO and GYRO_SENS to be defined
 * dist: distance to travel in centimeters
 * speed: speed to drive at on a range from 0-1000
 */
void create_forward_gyro(float dist, int speed) {
  float left_speed = speed;
  float right_speed = speed;
  double offset = 0;
  gyro_x(); gyro_y(); gyro_z();
  set_create_distance(0);
  while(get_create_distance() < dist) {
    double val = ((double) {(abs(GYRO) == 1 ? gyro_x() : (abs(GYRO) == 2 ? gyro_y() : gyro_z()))} - gyro_dev) * -1;
    create_drive_direct(left_speed, right_speed);
    offset += val;
    left_speed = speed - ((double){offset} / GYRO_SENS);
    right_speed = speed + ((double){offset} / GYRO_SENS);
    msleep(40);
  }
}

/**
 * calc_dev calibrates the gyrometer
 * Requires gyro_dev to be a global variable
 */
void calc_dev() {
  printf("please keep robot still for 6 seconds\n press r_button when ready\n");
  while (!right_button()) msleep(50);
  printf("calculating...\n");
  int time = 6000;
  int interval = 80;
  double sum = 0;
  double i;
  gyro_x(); gyro_y(); gyro_z();
  for (i = 0; i < time / interval; ++i) {
    // determine gyro value based on wallaby orientation
    double val = (double) {(abs(GYRO) == 1 ? gyro_x() : (abs(GYRO) == 2 ? gyro_y() : gyro_z()))};
    sum += val;
    msleep(interval);
  }
  gyro_dev = sum / i;
  printf("average deviation of %d \n", (int) {gyro_dev});
  printf("gyro calib done\n");
}
