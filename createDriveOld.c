#define get_high_byte2(a) (((a)>>8)&255)
#define get_low_byte2(a) ((a)&255)
#include "createDrive.h"

void create_write_int(int integer)
{
	create_write_byte(get_high_byte2(integer));
	create_write_byte(get_low_byte2(integer));
}

//this is for just good old plain scripting
void create_wait_time(int time)//time is in deciseconds
{
	create_write_byte(155);
	create_write_byte(time);
}
/*void create_special_connect(){
	serial_init();
	create_write_byte(128);
	create_write_byte(132);
	create_power_led(250,254);
	atexit(create_disconnect);
}*/
void create_wait_dist(int dist)//dist is in mm
{
	create_write_byte(156);
	create_write_int(dist);
}
void create_wait_angle(int angle)//degrees, negative = right
{
	create_write_byte(157);
	create_write_int(angle);
}
void create_wait_event(int event)//see #defines for possible answers.  Use 255-event for the inverse
{
	create_write_byte(158);
	create_write_byte(event);
}

void create_drive_direct_dist(int r_speed, int l_speed, int dist)
{
	create_write_byte(145);
	create_write_int(r_speed);
	create_write_int(l_speed);
	create_wait_dist(dist);
}
void create_drive_direct_left(int r_speed, int l_speed, int angle)
{
	create_write_byte(145);
	create_write_int(r_speed);
	create_write_int(l_speed);
	create_wait_angle(angle);
}
void create_drive_direct_right(int r_speed, int l_speed, int angle)
{
	create_write_byte(145);
	create_write_int(r_speed);
	create_write_int(l_speed);
	create_wait_angle(-angle);
}
void create_right(int angle, int radius, int speed)
{
	create_write_byte(137);
	create_write_int(speed);
	if (radius == 0){
		create_write_int(-1);
	}else{
		create_write_int(-radius);
	}
	create_wait_angle(-angle);
}
void create_left(int angle, int radius, int speed)
{
	create_write_byte(137);
	create_write_int(speed);
	if (radius == 0){
		create_write_int(1);
	}else{
		create_write_int(radius);
	}
	create_wait_angle(angle);
}
void create_forward(int dist, int speed)
{
	create_write_byte(145);
	create_write_int(speed);
	create_write_int(speed);
	create_wait_dist(dist);
}
void create_backward(int dist, int speed)
{
	create_write_byte(145);
	create_write_int(-speed);
	create_write_int(-speed);
	create_wait_dist(-dist);
}
void create_backward_fast(int dist,int speed)
{
	create_write_byte(145);
	create_write_int(-speed*lSpeedMult/100);
	create_write_int(-speed*rSpeedMult/100);
	create_wait_dist(-dist);
}
void create_crash()
{
	create_write_byte(7);
}

void output_sen_0()
{
	create_write_byte(147);
	create_write_byte((0*1)+(0*2)+(1*4));
}

void stop_output()
{
	create_write_byte(147);
	create_write_byte(0);
}

void create_send(){
	//gogo OI mode data!
	create_write_byte(142);
	create_write_byte(35);
	
}
void create_recieve(){
	
	char buffer[1];
	char *bptr = buffer;
	create_read_block(bptr,1);
}

// blocks program until create finishes
void create_block()
{
	create_stop();
	create_send();
	create_recieve();
}
/*void create_motors(int byte){
	create_write_byte(138);
	create_write_byte(byte);
	//1*(pin 23)+2*(pin 22)+4*pin(24)
	//so, pin 24 on = send 4
	//off = send 0
}*/
//so long as we are connected to the controller, no reason to use the direct motor command instead of this one
void create_motors(int speed)//speed is from 0 to 128 inclusive
{
	create_write_byte(144);
	create_write_byte(speed);
	create_write_byte(speed);
	create_write_byte(speed);
}

/*void create_connectauto(){//automatically connects with a servo on the power button
	if (!create_connect_once()){
		CREATE_POWERPRESS();
		msleep(500);
		CREATE_POWERUNPRESS();
		msleep(500);
		disable_servo(serv);
		create_connect_once();
	}
}
void create_off(){
	CREATE_POWERPRESS();
	msleep(200);
}*/

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
