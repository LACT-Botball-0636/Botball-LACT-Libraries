//Documentation in the createDrive.c file in order to keep this file concise and easier to use for quick reference.
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

//Try to avoid calling this and create_write_byte outside of the libraries. Left in here for convenience.
void create_write_int(int integer);

//There is no longer scripting with the introduction of the create 2, but these will function similarly to how they worked without scripting.
void create_wait_time(int time);//time is in deciseconds
void create_wait_dist(int dist);//dist is in mm
void create_wait_angle(int angle);//degrees, negative = right
void create_wait_event(int event);//see #defines for possible answers.  Use 255-event for the inverse

//Drive commands
void create_drive_direct_dist(int r_speed, int l_speed, int dist);
void create_drive_direct_left(int r_speed, int l_speed, int angle);
void create_drive_direct_right(int r_speed, int l_speed, int angle);
void create_right(int angle, int radius, int speed);
void create_left(int angle, int radius, int speed);
void create_forward(int dist, int speed);
void create_backward(int dist, int speed);
void create_crash();

void output_sen_0();

void stop_output();

void create_send();
void create_recieve();

// blocks program until create finishes
void create_block();
//so long as we are connected to the controller, no reason to use the direct motor command instead of this one
void create_motors(int speed);//speed is from 0 to 128 inclusive

void create_lineup();
#endif
