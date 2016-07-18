/* LineFollow.h
 * The LineFollow library has code to help robots utilize lines for line
 * following. 
 * !TODO! Support for line following with robots using single tophats.
 * PID
 */

#ifndef LINEFOLLOW_H
#define LINEFOLLOW_H

// Dependent on drive.h!
#include "drive.h"

// Left and right tophats
#define LEFT_LINE 1
#define RIGHT_LINE 0

// Black values
#define LEFT_BLACK 2500
#define RIGHT_BLACK 2500

/*
 * \brief drives forward and squares up on line.
 * \param speed the speed to travel towards the line at. Max 1500, min -1500.
 */
void go_to_line(int speed);

/*
 * \brief drives forward while line following for a set distance at a set speed.
 * \param dist the distance to travel.
 * \param speed the speed to travel at.
 */
void line_follow(int dist, int speed);

#endif
