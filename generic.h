
#ifndef _GENERIC_H_
#define _GENERIC_H_

//UTILITY
float bound(float num, float max);
int in_range(int input, int wanted, int fudge);
float ET_distance(int X);
int et_avg(int port);

#define WAIT(thing); while(!(thing)){msleep(1);}
#define LIMIT(thing,time); {double _tmptime = seconds()+time; while(!(thing) && (_tmptime > seconds())){msleep(1);}}
#define gmpc(port) get_motor_position_counter(port)


//LIGHT START
void light_start(int sensor);

//TIMING
void start();
float curr_time();
void now();
void nowstr(char *s);
void wait_till(float t);

//SERVOS
//servo_off(int) is replaced with the KIPR library function disable_servo(int)
void servo_set(int port,int end,float time);//,float increment)

//camera stuff
int cam_area(int channel);//returns largest blob in channel, or 0 if none
void update_wait();
void next(int State);
void multicamupdate(int reps);

//State system
int currstate;
#define state(State) if (currstate == State)
void next(int State);


int getabbutton();
int getabcbutton();
#endif
