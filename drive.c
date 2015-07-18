#include "drive.h"
#include <math.h>

void drive_off(){
	off(MOT_RIGHT);
	off(MOT_LEFT);
}
void clear_all_drive(){ 
	clear_motor_position_counter(MOT_RIGHT);
	clear_motor_position_counter(MOT_LEFT);
}
void drive(int mL,int mR){ 
	motor(MOT_LEFT,mL);
	motor(MOT_RIGHT,mR);
}


/*void right(float degrees, float radius){//turn right a number of degrees with a certain radius
	int turnrspeed;
	long turnl=((2*radius+ks)*CMtoBEMF*PI)*(degrees/360.);
	long turnr=((2*radius-ks)*CMtoBEMF*PI)*(degrees/360.);
	if(turnl == 0l) return;
	turnrspeed = round((float)turnr/(float)turnl*SPD);
	mrp(MOT_LEFT, SPD,turnl);
	if(turnrspeed < 0) turnrspeed = -turnrspeed;
	if(turnrspeed < 50){
		turnrspeed = 0;
		turnr = 0l;
		off(MOT_RIGHT);
		}else{
		mrp(MOT_RIGHT,turnrspeed,turnr);
	}
	bmd(MOT_RIGHT);
	bmd(MOT_LEFT);
}*/

/* \fn void right(int degrees, int radius)
 * \brief turns right degrees degrees at int radius radius
 * \param degrees degrees forward to go
 * \param radius radius at which to turn around
 */
void right(float degrees, float radius){
		int turnrspeed;
		long turnl=((2*radius+ks)*CMtoBEMF*PI)*(degrees/360.);
		long turnr=((2*radius-ks)*CMtoBEMF*PI)*(degrees/360.);
    	if(turnl == 0l) return;
    	turnrspeed = round((float)turnr/(float)turnl*SPD);
    	msleep(30l);
    	if(turnl > 0l)
      		motor(MOT_LEFT, SPD);
    	else
      		motor(MOT_LEFT, -SPD);
    	if(turnrspeed < 0) turnrspeed = -turnrspeed;
		if(turnr > 0l)
			motor(MOT_RIGHT, turnrspeed);
		else
			motor(MOT_RIGHT, -turnrspeed);
    	turnl += gmpc(MOT_LEFT);
    	turnr += gmpc(MOT_RIGHT);
    	if(turnr - gmpc(MOT_RIGHT) > 0l){
        	if(turnl - gmpc(MOT_LEFT) > 0l){
            		while((turnr > gmpc(MOT_RIGHT) && turnrspeed != 0) || turnl > gmpc(MOT_LEFT)){
                		if(turnr < gmpc(MOT_RIGHT) - 10l) off(MOT_RIGHT);
                		if(turnl < gmpc(MOT_LEFT) - 10l) off(MOT_LEFT);
            		}
        	}else{
            		while((turnr > gmpc(MOT_RIGHT) && turnrspeed != 0) || turnl < gmpc(MOT_LEFT)){
                		if(turnr < gmpc(MOT_RIGHT) - 10l) off(MOT_RIGHT);
                		if(turnl > gmpc(MOT_LEFT) + 10l) off(MOT_LEFT);
            }
        }
    }else{
        if(turnl - gmpc(MOT_LEFT) > 0l){
            while((turnr < gmpc(MOT_RIGHT) && turnrspeed != 0) || turnl > gmpc(MOT_LEFT)){
                if(turnr > gmpc(MOT_RIGHT) + 10l) off(MOT_RIGHT);
                if(turnl < gmpc(MOT_LEFT) - 10l) off(MOT_LEFT);
            }
        }else{
            while((turnr < gmpc(MOT_RIGHT) && turnrspeed != 0) || turnl < gmpc(MOT_LEFT)){
                if(turnr > gmpc(MOT_RIGHT) + 10l) off(MOT_RIGHT);
                if(turnl > gmpc(MOT_LEFT) + 10l) off(MOT_LEFT);
            }
        }
    }
    drive_off();
    msleep(30l);
}
/* \fn void left(int degrees, int radius)
 * \brief turns left degrees degrees at int radius radius
 * \param degrees degrees forward to go
 * \param radius radius at which to turn around
 */
void left(float degrees, float radius){
int turnlspeed;
	long turnl=((2*radius-ks)*CMtoBEMF*PI)*(degrees/360.);
	long turnr=((2*radius+ks)*CMtoBEMF*PI)*(degrees/360.);
    if(turnr == 0l) return;
    turnlspeed = round((float)turnl/(float)turnr*SPD);
    msleep(30l);
    if(turnr > 0l)
      motor(MOT_RIGHT, SPD);
    else
      motor(MOT_RIGHT, -SPD);
    if(turnlspeed < 0) turnlspeed = -turnlspeed;
	if(turnl > 0l)
	  motor(MOT_LEFT, turnlspeed);
	else
	  motor(MOT_LEFT, -turnlspeed);
    turnr += gmpc(MOT_RIGHT);
    turnl += gmpc(MOT_LEFT);
    if(turnl - gmpc(MOT_LEFT) > 0l){
        if(turnr - gmpc(MOT_RIGHT) > 0l){
            while((turnl > gmpc(MOT_LEFT) && turnlspeed != 0) || turnr > gmpc(MOT_RIGHT)){
                if(turnl < gmpc(MOT_LEFT) - 10l) off(MOT_LEFT);
                if(turnr < gmpc(MOT_RIGHT) - 10l) off(MOT_RIGHT);
            }
        }else{
            while((turnl > gmpc(MOT_LEFT) && turnlspeed != 0) || turnr < gmpc(MOT_RIGHT)){
                if(turnl < gmpc(MOT_LEFT) - 10l) off(MOT_LEFT);
                if(turnr > gmpc(MOT_RIGHT) + 10l) off(MOT_RIGHT);
            }
        }
    }else{
        if(turnr - gmpc(MOT_RIGHT) > 0l){
            while((turnl < gmpc(MOT_LEFT) && turnlspeed != 0) || turnr > gmpc(MOT_RIGHT)){
                if(turnl > gmpc(MOT_LEFT) + 10l) off(MOT_LEFT);
                if(turnr < gmpc(MOT_RIGHT) - 10l) off(MOT_RIGHT);
            }
        }else{
            while((turnl < gmpc(MOT_LEFT) && turnlspeed != 0) || turnr < gmpc(MOT_RIGHT)){
                if(turnl > gmpc(MOT_LEFT) + 10l) off(MOT_LEFT);
                if(turnr > gmpc(MOT_RIGHT) + 10l) off(MOT_RIGHT);
            }
        }
    }
    drive_off();
    msleep(30l);
}

void multforward(float distance, float speedmult){//go forward a number of CM    NOT    backEMF counts
	if(distance < 0l){
		distance = -distance;
	}
	long newdist;
	newdist = distance*CMtoBEMF;//conversion ratio
	long l = gmpc(MOT_LEFT)+newdist;
	long r = gmpc(MOT_RIGHT)+newdist;
	motor(MOT_LEFT,SPDl*speedmult);
	motor(MOT_RIGHT,SPDr*speedmult);
	while(gmpc(MOT_LEFT) < l && gmpc(MOT_RIGHT) < r){
		if (gmpc(MOT_LEFT) >= l)
			off(MOT_LEFT);
		if (gmpc(MOT_RIGHT) >= r)
			off(MOT_RIGHT);
	}
	drive_off();
}
void forward(float distance){//go forward a number of CM    NOT    backEMF counts
	if(distance < 0l){
		distance = -distance;
	}
	long newdist;
	newdist = distance*CMtoBEMF;//conversion ratio
	long l = gmpc(MOT_LEFT)+newdist;
	long r = gmpc(MOT_RIGHT)+newdist;
	motor(MOT_LEFT,SPDl);
	motor(MOT_RIGHT,SPDr);
	while(gmpc(MOT_LEFT) < l && gmpc(MOT_RIGHT) < r){
		if (gmpc(MOT_LEFT) >= l)
			off(MOT_LEFT);
		if (gmpc(MOT_RIGHT) >= r)
			off(MOT_RIGHT);
	}
	drive_off();
	
	/*mrp(MOT_RIGHT,SPDrb,newdist*rdistmultb);
	mrp(MOT_LEFT,SPDlb,newdist);
	bmd(MOT_RIGHT);
	bmd(MOT_LEFT);*/
}
void backward(float distance){//go backward a number of CM    NOT    backEMF counts
	if(distance < 0l){
		distance = -distance;
	}
	long newdist;
	newdist = distance*CMtoBEMF;
	long l = gmpc(MOT_LEFT)-newdist;
	long r = gmpc(MOT_RIGHT)-newdist;
	motor(MOT_LEFT,-SPDlb);
	motor(MOT_RIGHT,-SPDrb);
	while(gmpc(MOT_LEFT) > l && gmpc(MOT_RIGHT) > r){
		if (gmpc(MOT_LEFT) <= l)
			off(MOT_LEFT);
		if (gmpc(MOT_RIGHT) <= r)
			off(MOT_RIGHT);
	}
	drive_off();
}
