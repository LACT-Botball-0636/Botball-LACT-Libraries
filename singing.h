#include "createDrive.h"

//NOTEb = NOTE flat
#define Eb 63
#define E 64
#define F 65
#define G 67
#define Ab 68
#define A 69
#define Bb 70
#define B 71
#define C 72
#define Db 73
#define D 74
#define O +12
#define o -12

//ceil(X) only works on positive values
int notes[255],times[255],notenum;
float waits[16];
void initsong()
{
	int i;
	notenum = 0;
	for(i=0;i<16;i++)
	{
		waits[i] = -1.;
	}
	for(i=0;i<255;i++)
	{
		notes[i] = -1;
		times[i] = -1;
	}
}
void note(int freq,int len)
{
	notes[notenum] = freq;
	times[notenum] = len;//(int)(len*64.);
	notenum++;
}
void song()
{
	int totnotes = 0,sets,finalset,set = 0,note;
	while(notes[totnotes] != -1)
	{
		totnotes++;
	}
	sets = totnotes/16;
	finalset = totnotes%16;
	while(set < sets)
	{
		create_write_byte(140);
		create_write_byte(set);
		create_write_byte(16);
		waits[set] = 0.;
		for(note = 0;note<16;note++)
		{
			waits[set] += (float)times[note+(set*16)]/64.;
			create_write_byte(notes[note+(set*16)]);
			create_write_byte(times[note+(set*16)]);
		}
		set++;
	}
	create_write_byte(140);
	create_write_byte(set);
	create_write_byte(finalset);
	waits[set] = 0.;
	for(note = 0;note<finalset;note++)
	{
		waits[set] += (float)times[note+(set*16)]/64.;
		create_write_byte(notes[note+(set*16)]);
		create_write_byte(times[note+(set*16)]);
	}
}

int songCheck() {//returns -1 on error, 0 if no song, 1 if song
    int x;
    CREATE_BUSY;
    s_write_byte(149);
    s_write_byte(1);  // send 1 packet
    s_write_byte(37);  // is song playing
	
	char buffer[1];
	char *bptr = buffer;
	create_read_block(bptr,1);
    return *bptr;
}
void play()
{
    int i = 0;
    while(waits[i] != -1)
      {
        serial_write_byte(141);
        serial_write_byte(i);
        while(songCheck()==1){msleep(1);}
        i++;
    }
}

void sing()
{
	int i = 0;
	while(waits[i] != -1.)
	{
		create_write_byte(141);
		create_write_byte(i);
		create_wait_time((int)((waits[i]*10.)));
		printf("%d,%d\n",i,(int)((waits[i]*10.)));
		//sleep(waits[i]);
		i++;
	}
}
int tetris()
{
	initsong();
	
	//E = 76
	note(76,24); 
	//B = 71
	note(71,12);
	//C = 72
	note(72,12);
	//D = 74
	note(74,24);
	note(72,12);
	note(71,12);
	//A = 69
	note(69,24);
	note(69,12);
	note(72,12);
	note(76,24);
	note(74,12);
	note(72,12);
	note(71,24);
	note(0,12);
	note(72,12);
	note(74,24);
	note(76,24);
	note(72,24);
	note(69,24);
	note(69,24);
	note(0,24);
	//
	note(0,12);
	note(74,24);
	//F = 77
	note(77,12);
	//A = 81
	note(81,24);
	//G = 79
	note(79,12);
	note(77,12);
	//E = 76
	note(76,24);
	note(0,12);
	note(72,12);
	note(76,24);
	note(74,12);
	note(72,12);
	note(71,24);
	note(71,12);
	note(72,12);
	note(74,24);
	note(76,24);
	note(72,24);
	note(69,24);
	note(69,24);
	note(0,24);
	//E = 64
	note(64,48);
	note(60,48);
	note(62,48);
	note(59,48);
	note(60,48);
	note(57,48);
	note(56,48);
	note(59,24);
	note(0,24);
	//
	note(64,48);
	note(60,48);
	note(62,48);
	note(59,48);
	note(60,24);
	note(64,24);
	note(69,48);
	note(68,48);
	note(0,48);
	
	// Repeat beginning
	//E = 76
	note(76,24); 
	//B = 71
	note(71,12);
	//C = 72
	note(72,12);
	//D = 74
	note(74,24);
	note(72,12);
	note(71,12);
	//A = 69
	note(69,24);
	note(69,12);
	note(72,12);
	note(76,24);
	note(74,12);
	note(72,12);
	note(71,24);
	note(0,12);
	note(72,12);
	note(74,24);
	note(76,24);
	note(72,24);
	note(69,24);
	note(69,24);
	note(0,24);
	//
	note(0,12);
	note(74,24);
	//F = 77
	note(77,12);
	//A = 81
	note(81,24);
	//G = 79
	note(79,12);
	note(77,12);
	//E = 76
	note(76,24);
	note(0,12);
	note(72,12);
	note(76,24);
	note(74,12);
	note(72,12);
	note(71,24);
	note(71,12);
	note(72,12);
	note(74,24);
	note(76,24);
	note(72,24);
	note(69,24);
	note(69,24);
	note(0,24);
	song();
}
#define A 69
#define Bb 70
#define B 71
#define C 60
#define D 62
#define Eb 63
#define E 64
#define F 65
#define G 67
#define OC 12
void undersea(){
	initsong();
	note(D,16);
	note(F,16);
	note(Bb,16);
	note(D+OC,31+1);
	//note(0,1);
	note(D+OC,32);
	note(F,16);
	note(C+OC,32);
	note(Eb+OC,32);
	note(D+OC,32);
	note(Bb,32);
	note(Bb-OC,16);
	note(D,16);
	note(F,16);
	note(Bb,31+1);
	//note(0,1);
	note(Bb,32);
	note(C,16);
	note(A,32);
	note(C+OC,32);
	note(Bb,32);
	note(0,64);
	note(Bb,15+1);
	//note(0,1);
	note(Bb,31+1);
	//note(0,1);
	note(Bb,31+1);
	//note(0,1);
	note(Bb,16);
	note(A,32);
	note(C+OC,32);
	note(Bb,32);
	note(F,32);
	note(0,32);
	note(D,16);
	note(F,31+1);
	//note(0,1);
	note(F,32);
	note(D,16);
	note(C,32);
	note(F,32);
	note(D,32);
	song();
}
