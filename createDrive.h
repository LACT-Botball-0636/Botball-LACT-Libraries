//Documentation in the createDrive.c file in order to keep this file concise and easier to use for quick reference.
//Todo list: Constants, create_wait_angle, create_wait_dist, check create_wait_event
#ifndef _FINALCREATE
#define _FINALCREATE

//required for buffering and scripting
#define WHEEL_DROP 1
#define CLIFF 10
#define BUMP 5
#define LEFT_BUMP 6
#define RIGHT_BUMP 7
#define BUTTON_ADVANCED 16
#define BUTTON_PLAY 17
#define SEN_0 18
#define WHEEL_FRONT_DROP 2
#define WHEEL_LEFT_DROP 3
#define WHEEL_RIGHT_DROP 4
#define VIRTUAL_WALL 8
#define WALL 9
#define CLIFF_LEFT 11
#define CLIFF_LEFT_FRONT 12
#define CLIFF_RIGHT_FRONT 13
#define CLIFF_RIGHT 14
#define HOME_BASE 15
#define DIGITAL_INPUT_0 18
#define DIGITAL_INPUT_1 19
#define DIGITAL_INPUT_2 20
#define DIGITAL_INPUT_3 21
#define OI_MODE_PASSIVE 22

//Try to avoid calling this and create_write_byte outside of the libraries. Left in here for convenience though Same goes for byte reading functions.
void create_write_int(int integer);
int create_read_signed(int bytes);
int create_read_unsigned(int bytes);

//There is no longer scripting with the introduction of the create 2, but these will function similarly to how they worked without scripting.
int create_wait_dist(int dist); //dist is in mm
int create_wait_angle(int angle); //degrees, negative = right
void create_wait_event(int event); //see #defines for possible answers.  Use 255-event for the inverse

//Drive commands
int create_drive_direct_dist(int r_speed, int l_speed, int dist);
int create_drive_direct_left(int r_speed, int l_speed, int angle);
int create_drive_direct_right(int r_speed, int l_speed, int angle);
int create_right(int angle, int radius, int speed);
int create_left(int angle, int radius, int speed);
int create_forward(int dist, int speed);
int create_backward(int dist, int speed);

// Drive PWM commands
int create_drive_pwm_left(int r_speed, int l_speed, int dist);
int create_drive_pwm_right(int r_speed, int l_speed, int dist);
int create_forward_pwm(int dist, int speed);
int create_backward_pwm(int dist, int speed);

//Not Driving commands
void create_crash();

void create_send();
void create_recieve();

//Blocks program until create finishes
void create_block();
//so long as we are connected to the controller, no reason to use the direct motor command instead of this one
void create_vacuum (int speed); //speed is from 0 to 128 inclusive

void create_square (int speed, int time);


//void create_lineup();
#endif
