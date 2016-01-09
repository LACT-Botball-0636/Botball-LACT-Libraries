#ifndef _NEWMENU
#define _NEWMENU
#include "generic.h"

#define DEFAULT_OPTION 0
extern int currstate;//defined in generic.h

struct menuitem {
  int snum;
  char* name;
};

extern struct menuitem menu[];

void get_mode();
//other functions are hidden- just use get_mode();

#endif
