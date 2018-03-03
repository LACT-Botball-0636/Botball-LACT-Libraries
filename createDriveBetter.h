//
//  Create.h
//

#include <kipr/botball.h>

#define lfCliff get_create_lfcliff_amt
#define rfCliff get_create_rfcliff_amt
#define LEFT_LINE 0
#define RIGHT_LINE 1

void create_line_follow(int dist, int speed);
void create_forward(int dist, int speed);
void create_backward(int dist, int speed);
void create_left(int degrees, int speed);
void create_right(int degrees, int speed);
