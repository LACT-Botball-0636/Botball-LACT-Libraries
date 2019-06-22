//
//  Create.h
//

#include <kipr/botball.h>

#define lfCliff get_create_lfcliff_amt
#define rfCliff get_create_rfcliff_amt
#define lCliff get_create_lcliff_amt
#define rCliff get_create_rcliff_amt

/* Line follow constants for single sensor line following
 * LEFT means follow on the left side of the line
 * RIGHT means follow on the right side of the line
 */
#define LEFT 0
#define RIGHT 1

/* Gyro Constants
 * GYRO defines the orientation of the wallaby
 * GYRO_SENS is how sensitive the gyro code is
 * gyro_dev is the average deviation of the gyrometer
 */
#define GYRO $ // 1: x, 2: y, 3: z
#define GYRO_SENS 15 // Usually a value of 15 works quite well for the create. Make this value higher to make it less sensitive.
float gyro_dev; // Use the function calc_dev() to set this variable 

void create_line_follow_center(int speed);
void create_line_follow_center_dist(int dist, int speed);
void create_line_follow_left(int dist, int speed, int side);
void create_line_follow_right(int dist, int speed, int side);
void create_forward(int dist, int speed);
void create_backward(int dist, int speed);
void create_left(int degrees, int speed);
void create_right(int degrees, int speed);

double create_forward_gyro(int speed, double offset);
void create_forward_gyro_dist(int dist, int speed);
void create_square_up_gyro(int ms, int speed);
void create_square_up_fcliff(int speed);
void create_square_up_cliff(int speed);

void calc_dev();

void create_setup_cliff();
void create_skip_cliff();
int lfWhite, lWhite, rfWhite, rWhite;
int lfBlack, lBlack, rfBlack, rBlack;
