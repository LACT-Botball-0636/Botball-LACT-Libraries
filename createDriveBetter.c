#include "createDrive.h"
#include <math.h>
/**
 * create_line_follow_center makes the create line follow by using the built-in front cliff sensors. 
 * create_setup_cliff must be run before create_line_follow_center will work
 * Requires following to be defined:
 * lfBlack and lfWhite are the readings for the left front cliff sensor on the create
 * rfBlack and rfWhite are the readings for the right front cliff sensor on the create
 * dist: distance to travel in centimeters
 * speed: speed to drive at on a range from 0-1000
 */
void create_line_follow_center(int dist, int speed)
{
  //create_line_follow_center makes the create line follow for "dist" centimeters at "speed" speed
  
  dist*=10; //Converts centimeters into millimeters
  set_create_distance(0); //Clears create position counter
  create_drive_straight(speed); //Initializes movement
  while(abs(get_create_distance())<abs(dist)) //while distance has not been achieved, perform the following:
  {
    if(lfCliff() < (lfBlack+lfWhite)/2)				  //if the left tophat sensor sees black
    {
      create_drive_direct(speed*.75,speed*1.25); //drive to the left
    }
    else if(rfCliff() < (rfBlack+rfWhite)/2)		  //if the right tophat sensor sees black
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
 * create_line_follow_left makes the create line follow by using the built-in left cliff sensor. 
 * create_setup_cliff must be run before create_line_follow_right will work
 * Requires following to be defined:
 * lBlack and lWhite are the readings for the left cliff sensor on the create
 * dist: distance to travel in centimeters
 * speed: speed to drive at on a range from 0-1000
 */
void create_line_follow_left(int dist, int speed, int side) {
	dist*=10; //Convert centimeters to millimeters
    speed = 100*speed/1000;
    set_create_distance(0);
    
    while(abs(get_create_distance()) < abs(dist)) {
        
        float sens = 0.01;
        if (side == RIGHT) {
        	create_drive_direct(sens*speed*(lWhite - lCliff()), sens*speed*(lCliff() - lBlack));
        } else if (side == LEFT) {
        	create_drive_direct(sens*speed*(lCliff() - lBlack), sens*speed*(lWhite - lCliff()));
        }
    }
    create_stop();
}

/**
 * create_line_follow_right makes the create line follow by using the built-in right cliff sensor. 
 * create_setup_cliff must be run before create_line_follow_right will work
 * Requires following to be defined:
 * rBlack and rWhite are the readings for the right cliff sensor on the create
 * dist: distance to travel in centimeters
 * speed: speed to drive at on a range from 0-1000
 */
void create_line_follow_right(int dist, int speed, int side) {
	dist*=10; //Convert centimeters to millimeters
    speed = 100*speed/1000;
    set_create_distance(0);
    
    while(abs(get_create_distance()) < abs(dist)) {
        
        float sens = 0.01;
        if (side == RIGHT) {
        	create_drive_direct(sens*speed*(rWhite - rCliff()), sens*speed*(rCliff() - rBlack));
        } else if (side == LEFT) {
        	create_drive_direct(sens*speed*(rCliff() - rBlack), sens*speed*(rWhite - rCliff()));
        }
    }
    create_stop();
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

/**
 * create_setup_cliff calibrates the cliff sensors on the create for black and white lines
 * Requires lfWhite, rfWhite, lWhite, rWhite, lfBlack, rfBlack, lBlack, rBlack to be global variables
 */
void create_setup_cliff() 
{
    int accept = 0;
    while (!accept) 
    {
        printf("\n\n------------------------\n\nMove the ENTIRE create over white area of board.\nPress right button to set.\n");
        while (!right_button()) {}
        lfWhite = lfCliff();
        lWhite = lCliff();
        rfWhite = rfCliff();
        rWhite = rCliff();
        printf("Left front cliff value: %d\nLeft cliff value: %d\nRight front cliff value: %d\nRight cliff value: %d\n", lfWhite, lWhite, rfWhite, rWhite);
        msleep(1000);
        printf("Press right button to accept, left button to reject.\n");
        while(!right_button() && !left_button()) {}
        if (right_button()) 
        {
            accept = 1;
        }
    }

    msleep(1000);
    accept = 0;
    while (!accept) 
    {
        printf("\n\n------------------------\n\nMove FRONT cliff sensors over black area of board.\nPress right button to set.\n");
        while (!right_button()) {}
        lfBlack = lfCliff();
        rfBlack = rfCliff();
        printf("Left front cliff value: %d\nRight front cliff value: %d\n", lfBlack, rfBlack);
        msleep(1000);
        printf("Press right button to accept, left button to reject.\n");
        while(!right_button() && !left_button()) {}
        if (right_button()) 
        {
            accept = 1;
        }
    }
    
    msleep(1000);
    accept = 0;
    while (!accept) 
    {
        printf("\n\n------------------------\n\nMove LEFT cliff sensor over black area of board.\nPress right button to set.\n");
        while (!right_button()) {}
        lBlack = lCliff();
        printf("Left cliff value: %d\n", lBlack);
        msleep(1000);
        printf("Press right button to accept, left button to reject.\n");
        while(!right_button() && !left_button()) {}
        if (right_button()) 
        {
            accept = 1;
        }
    }
    
    msleep(1000);
    accept = 0;
    while (!accept) 
    {
        printf("\n\n------------------------\n\nMove RIGHT cliff sensor over black area of board.\nPress right button to set.\n");
        while (!right_button()) {}
        rBlack = lCliff();
        printf("Right cliff value: %d\n", rBlack);
        msleep(1000);
        printf("Press right button to accept, left button to reject.\n");
        while(!right_button() && !left_button()) {}
        if (right_button()) 
        {
            accept = 1;
        }
    }
    
    printf("\n\nCliff setup done!\n");
}

void create_skip_cliff() {
	//Test function to quickly set up cliff sensors
    lfWhite = 2923;
    lWhite = 2894;
    rfWhite = 2865;
    rWhite = 2907;
    
    lfBlack = 1444;
    rfBlack = 1044;
    lBlack = 1166;
    rBlack = 1166;
}
