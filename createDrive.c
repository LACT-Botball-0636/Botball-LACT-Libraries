#include <math.h>
#include "createDrive.h"

// Create information: cable download speed of 14.0625 kilobytes/s.
// More info at http://www.irobot.com/~/media/MainSite/PDFs/About/STEM/Create/create_2_Open_Interface_Spec.pdf
// Important notes: Avoid calling create_read_block directly. Using it incorrectly leads to bad things, but the library calls it safely.

// Get the second to rightmost byte.
#define GET_HIGH_BYTE2(a) (((a)>>8)&255)
// Get the rightmost byte.
#define GET_LOW_BYTE2(a) ((a)&255)

// Constants. Don't change these
#define TWO_BYTES 65536
#define PI 3.14159265358979

// FIND VALUES
#define MMToEncoder ???
#define EncoderToMM 1/MMToEncoder

// Adjustable values. You can change these
#define ENCODER_HIGH_LOOP 60000
#define ENCODER_LOW_LOOP TWO_BYTES-1-ENCODER_HIGH_LOOP

/* Sends two bytes to the Create by from the rightmost two bytes of an integer.
 * integer: the integer that the two bytes come from
 */

void create_write_int (int integer) {
  create_write_byte(GET_HIGH_BYTE2(integer));
  create_write_byte(GET_LOW_BYTE2(integer));
}

// Refer to the Create Open Interface to see which bytes should be read as signed or unsigned.

/* Reads a certain amount of bytes from the Create and returns the combined bytes as a signed integer
 * bytes: the amount of bytes to read from the Create. Though I don't think the create has a command which returns more than 2 bytes, the option is available to receive more
 */

int create_read_signed (int byte_count) {
  char bytes[byte_count];
  char *pointer = bytes;
  int total = 0;
  int place = pow(256.,(double)byte_count);

  printf("%d",create_read_block(pointer,byte_count));

  // Summing the bytes here
  int i;
  for (i = 0; i < byte_count; i++) {
    total += bytes[i] * place;
    place /= 256; // Basically shift one byte right
  }
  return total;
}

/* Reads a certain amount of bytes from the Create and returns the combined bytes as an unsigned integer
 * bytes: the amount of bytes to read from the Create. Though I don't think the create has a command which returns more than 2 bytes, the option is available to receive more
 */
int create_read_unsigned (int byte_count) {
  char bytes[byte_count];
  char *pointer = bytes;
  int total = 0;
  int place = pow(256., (double)byte_count);

  create_read_block(pointer, byte_count);

  // summing the bytes here
  int i;
  for (i = 0; i < byte_count; i++) {
    total += bytes[i] * place;
    place /= 256; // Basically shift one byte right
  }

  return total;
}

//Driving. Yay, encoder fun.

/* Waits until the Create has travelled a certain distance.
 * Returns 1 if the robot has successfully stopped by travelling a certain distance. Returns -1 if an irregular stop has occurred.

 * dist: the distance that will be travelled in mm. Reached when average of right and left encoder has passed the dist.

 * TODO: Add a piece of code to stop the program if the robot has not moved. Write the actual code
 */
int create_wait_dist (int dist) {
  create_write_byte(142);
  create_write_byte(41);
  int rvel = create_read_signed(2);
  create_write_byte(142);
  create_write_byte(42);
  int lvel = create_read_signed(2);
  int vel  = (rvel + lvel) / 2;
  printf("\nleft vel is %d, r vel is %d\n",rvel,lvel);
  if (vel == 0) {
    printf("Error, cannot wait dist if robot isn't moving");
    return -1;
  }

  int sum = 0;

  while (sum < dist) {
	create_write_byte(142);
	create_write_byte(19);
    sum += create_read_signed(2);
  }
  return 1;
}

//Most likely gonna borrow from the drive.c black magic wizardry to write this. Doing this later

/* Waits until the create turns a certain angle.
 * Returns 1 if the robot has successfully stopped by turning a certain distance. Returns -1 if an irregular stop has occurred.

 * angle: the angle to be travelled, in degrees, negative degrees is turning right.
 */

int create_wait_angle (int angle) {
  create_write_byte(142);
  create_write_byte(41);
  int rvel = create_read_signed(2);
  create_write_byte(142);
  create_write_byte(42);
  int lvel = create_read_signed(2);
  int vel  = (rvel + lvel) / 2;

  if (vel == 0) {
    printf("Error, cannot wait angle if robot isn't moving");
    return -1;
  }

  int sum = 0;

  while (sum < angle) {
	create_write_byte(142);
	create_write_byte(20);
    sum += create_read_signed(2);
  }
  return 1;
}

// Not sure if usable any more, will check later
// See the event constants in the header file for possible events. Use 255-event for the inverse.
void create_wait_event(int event) {
  create_write_byte(158);
  create_write_byte(event);
}

/* Drives moving the left and right motors at a certain speed. Ends when it reaches a distance. Returns an int showing if it drove correctly
 * r_speed/l_speed: speed of the left and right motors.
 * dist: distance it drives.
 */

int create_drive_direct_dist (int r_speed, int l_speed, int dist) {
  create_write_byte(145);
  create_write_int(r_speed);
  create_write_int(l_speed);

  int success = create_wait_dist(dist);
  create_stop();

  return success;
}
/* Drives moving the left and right motors at a certain speed. Ends when it reaches an angle
 * r_speed/l_speed: speed of the left and right motors.
 * angle: angle it drives until.
 */
int create_drive_direct_left (int r_speed, int l_speed, int angle) {
  create_write_byte(145);
  create_write_int(r_speed);
  create_write_int(l_speed);

  int success = create_wait_angle(angle);
  create_stop();

  return success;
}
/* Drives moving the left and right motors at a certain speed. Ends when it reaches an angle
 * r_speed/l_speed: speed of the left and right motors.
 * angle: angle it drives until. -angle means right turn
 */
int create_drive_direct_right (int r_speed, int l_speed, int angle) {
  create_write_byte(145);
  create_write_int(r_speed);
  create_write_int(l_speed);

  int success = create_wait_angle(-angle);
  create_stop();

  return success;
}
/* Turns right at a certain angle, radius, and speed.
 * angle: the angle to turn, calculated in degrees.
 * radius: the radius of the turn, PROBABLY in MM
 * speed: the speed to turn. Range of 0-500. For negative values use create_left.
 */
int create_right (int angle, int radius, int speed) {
  create_write_byte(137);
  create_write_int(speed);

  if (radius == 0) {
    create_write_int(-1);
  } else {
    create_write_int(-radius);
  }

  int success = create_wait_angle(-angle);
  create_stop();
  return success;
}
/* Turns left at a certain angle, radius, and speed.
 * angle: the angle to turn, calculated in degrees.
 * radius: the radius of the turn, PROBABLY in MM
 * speed: the speed to turn. Range of 0-500. For negative values use create_right.
 */
int create_left (int angle, int radius, int speed) {
  create_write_byte(137);
  create_write_int(speed);

  if (radius == 0) {
    create_write_int(1);
  } else {
    create_write_int(radius);
  }

  int success = create_wait_angle(angle);
  create_stop();

  return success;
}
/* Drives forward a certain distance. Returns an int showing if it drove properly.
 * dist: the distance to travel
 * speed: the speed to travel at
 */
int create_forward (int dist, int speed) {
  create_write_byte(145);
  create_write_int(speed);
  create_write_int(speed);

  int success = create_wait_dist(dist);
  printf("Create will stop\n");
  create_stop();
  printf("\n\n%d",success);
  return success;
}
/* Drives backward a certain distance. Returns an int showing if it drove properly
 * dist: the distance to travel
 * speed: the speed to travel at
 */
int create_backward (int dist, int speed) {
  create_write_byte(145);
  create_write_int(-speed);
  create_write_int(-speed);

  int success = create_wait_dist(-dist);
  create_stop();

  return success;
}

// PWM Drive Functions

/* Drives forward a certain distance. Returns an int showing if it drove properly
 * dist: the distance to travel
 * speed: the speed to travel at - range between -255 to 255
 */
int create_forward_pwm (int dist, int speed) {
  create_write_byte(146);
  create_write_int(speed);
  create_write_int(speed);

  int success = create_wait_dist(dist);
  create_stop();

  return success;
}
/* Drives backward a certain distance. Returns an int showing if it drove properly
 * dist: the distance to travel
 * speed: the speed to travel at - range between -255 to 255
 */
int create_backward_pwm (int dist, int speed) {
  create_write_byte(146);
  create_write_int(-speed);
  create_write_int(-speed);

  int success = create_wait_dist(-dist);
  create_stop();

  return success;
}

// TODO: create_wait_angle doesnt work with PWM because it uses ID: 41, which is only compatible with Drive Direct, not Drive PWM

// /* Drives moving the left and right motors at a certain speed. Ends when it reaches an angle
//  * r_speed/l_speed: speed of the left and right motors.
//  * angle: angle it drives until. -angle means right turn
//  */
// int create_drive_pwm_right (int r_speed, int l_speed, int angle) {
//   create_write_byte(146);
//   create_write_int(r_speed);
//   create_write_int(l_speed);
//
//   int success = create_wait_angle(-angle);
//   create_stop();
//
//   return success;
// }
// /* Drives moving the left and right motors at a certain speed. Ends when it reaches an angle
//  * r_speed/l_speed: speed of the left and right motors.
//  * angle: angle it drives until.
//  */
// int create_drive_pwm_left (int r_speed, int l_speed, int angle) {
//   create_write_byte(146);
//   create_write_int(r_speed);
//   create_write_int(l_speed);
//
//   int success = create_wait_angle(angle);
//   create_stop();
//
//   return success;
// }

//Functions unrelated to driving

// Reboots the Create
void create_crash () {
  create_write_byte(7);
}

// Requests the Create to send a byte indicating which mode it is in.
void create_send () {
  // gogo OI mode data!
  create_write_byte(142);
  create_write_byte(35);
}

// Receives one byte from the Create and does nothing with it.
void create_recieve () {
  char buffer[1];
  char *bptr = buffer;

  create_read_block(bptr,1);
}

// Blocks program until create finishes
void create_block () {
  create_stop();
  create_send();
  create_recieve();
}

// Runs the create vacuum at speed
// speed is from 0 to 128 inclusive
void create_vacuum (int speed) {
  create_write_byte(144);
  create_write_byte(speed);
  create_write_byte(speed);
  create_write_byte(speed);
}

/* Create squares up against a flat surface
 * speed: the speed to travel at
 * time: the time needed to square up
 */
void create_square (int speed, int time) {
  	create_drive_direct(-speed, -speed);
  	msleep(time);
  	create_stop();
}

/*
#define lcliff get_create_lcliff_amt(.002)
#define rcliff get_create_rcliff_amt(.002)
void create_lineup(){//lines up the create on a black line
  int done = 0;
  float tstart = seconds();
  int retry = 1;//don't retry ever
  while(done < 4){//WORK ON THIS
    msleep(5);
    int lspd,rspd;
    lspd = rspd = 0;
    if (lcliff > 800) lspd = 20;
    if (lcliff < 500) lspd = -20;
    if (rcliff > 800) rspd = 20;
    if (rcliff < 500) rspd = -20;

    if (seconds()-tstart > 4){lspd/=2;rspd/=2;}
    if (seconds()-tstart > 6){
      create_stop();
      return;//failure, timeout
    }
    //printf("\n%6d%6d",lcliff,rcliff);
    create_drive_direct(lspd,rspd);
    if (lspd == rspd && lspd == 0)
      done++;
    else
      done=0;
  }
  create_stop();
}
*/
