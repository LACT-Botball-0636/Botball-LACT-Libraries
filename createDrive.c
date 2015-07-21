#include <math.h>
#include "createDrive.h"

//Create information: cable download speed of 14.0625 kilobytes/s.
//More info at http://www.irobot.com/~/media/MainSite/PDFs/About/STEM/Create/create_2_Open_Interface_Spec.pdf

//Get the second to rightmost byte.
#define get_high_byte2(a) (((a)>>8)&255)
//Get the rightmost byte.
#define get_low_byte2(a) ((a)&255)

/*
Sends two bytes to the Create by from the rightmost two bytes of an integer.
integer: the integer that the two bytes come from
*/
void create_write_int(int integer)
{
	create_write_byte(get_high_byte2(integer));
	create_write_byte(get_low_byte2(integer));
}

//Refer to the Create Open Interface to see which bytes should be read as signed or unsigned.

/*
Reads a certain amount of bytes from the Create and returns the combined bytes as a signed integer
bytes: the amount of bytes to read from the Create. Though I don't think the create has a command which returns more than 2 bytes, the option is available to receive more
*/
int create_read_signed(int bytes)
{
	signed char bytes[bytes];
	signed char *pointer = bytes;
	create_read_block(pointer,bytes);
	int total = 0;
	int place = pow(256,bytes);
	//summing the bytes here
	for(i=0;i<bytes;i++)
	{
		total += bytes[i]*place;
		place/=256; //Basically shift one byte right
	}
	return total;
}

/*
Reads a certain amount of bytes from the Create and returns the combined bytes as an unsigned integer
bytes: the amount of bytes to read from the Create. Though I don't think the create has a command which returns more than 2 bytes, the option is available to receive more
*/
int create_read_unsigned(int bytes)
{
	char bytes[bytes];
	char *pointer = bytes;
	create_read_block(pointer,bytes);
	int total = 0;
	int place = pow(256,bytes);
	//summing the bytes here
	for(i=0;i<bytes;i++)
	{
		total += bytes[i]*place;
		place/=256; //Basically shift one byte right
	}
	return total;
}
//Driving. Yay, encoder fun. 

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

//Not driving stuff. Hopefully this remains the same

//Reboots the Create
void create_crash()
{
	create_write_byte(7);
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
