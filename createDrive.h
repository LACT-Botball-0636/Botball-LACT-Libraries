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
#define BUTTON_PLAY 17//TODO: finish all events.  p16 of create docs
#define SEN_0 18

//Try to avoid calling this and create_write_byte outside of the libraries. Left in here for convenience though Same goes for byte reading functions.
void create_write_int(int integer);
int create_read_signed(int bytes);
int create_read_unsigned(int bytes);
	
//There is no longer scripting with the introduction of the create 2, but these will function similarly to how they worked without scripting.
int create_wait_dist(int dist);//dist is in mm
int create_wait_angle(int angle);//degrees, negative = right
void create_wait_event(int event);//see #defines for possible answers.  Use 255-event for the inverse

//Drive commands
int create_drive_direct_dist(int r_speed, int l_speed, int dist);
int create_drive_direct_left(int r_speed, int l_speed, int angle);
int create_drive_direct_right(int r_speed, int l_speed, int angle);
int create_right(int angle, int radius, int speed);
int create_left(int angle, int radius, int speed);
int create_forward(int dist, int speed);
int create_backward(int dist, int speed);

//Not Driving commands
void create_crash();

void create_send();
void create_recieve();

//Blocks program until create finishes
void create_block();
//so long as we are connected to the controller, no reason to use the direct motor command instead of this one
void create_motors(int speed);//speed is from 0 to 128 inclusive

//void create_lineup();
#endif
