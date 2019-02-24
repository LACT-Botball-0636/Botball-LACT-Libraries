//
//  Create.h
//

#include <kipr/botball.h>

#define lfCliff get_create_lfcliff_amt
#define rfCliff get_create_rfcliff_amt
#define LEFT_LINE 0
#define RIGHT_LINE 1

/* Gyro Constants
 * GYRO defines the orientation of the wallaby
 * GYRO_SENS is how sensitive the gyro code is
 * gyro_dev is the average deviation of the gyrometer
 */
#define GYRO $ // 1: x, 2: y, 3: z
#define GYRO_SENS 15 // Usually a value of 15 works quite well for the create. Make this value higher to make it less sensitive.
float gyro_dev; // Use the function calc_dev() to set this variable

void create_line_follow(int dist, int speed);
void create_forward(int dist, int speed);
void create_backward(int dist, int speed);
void create_left(int degrees, int speed);
void create_right(int degrees, int speed);

void create_forward_gyro(float dist, int speed);
void calc_dev();
