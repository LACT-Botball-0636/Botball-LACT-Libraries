#include "newmenu.h"

void get_mode () {
  currstate = menu[options()].snum;
}

int selectionlist (int length) {
  int current = DEFAULT_OPTION;
  int counter = 1;
  int oldcurrent = DEFAULT_OPTION;
  
  while (1) {
    if (a_button()) {
      while (a_button()) msleep(1);
      
      return current;
    }
    
    if (c_button()) {
      while (c_button()) msleep(1);
      
      oldcurrent = current--;
      counter = 1;
      
      if(current < 0) current = length - 1;
    }
    
    if (b_button()) {
      while (b_button()) msleep(1);
      
      oldcurrent = current++;
      counter = 1;
      
      if (current >= length) current = 0;
    }
    
    if (counter == 1) {
      display_printf(0, oldcurrent + 1, " ");
      display_printf(0, current + 1, "*");
      
      counter = 0;
    }
  }
}

int options () {
  display_clear();
  
  msleep(10);
  
  display_printf(0, 0, "A Accept|B down|C up\n");
  while (a_button()) msleep(10);
  
  int result = selectionlist(draw_screen());
  display_clear();
  
  return result;
}

int draw_screen () {
  int i = 0;
  
  do {
    display_printf(0,i+1,"  %s",menu[i].name);
    //printf("\n %d%s",i,menu[i].name);
  } while (strcmp(menu[++i].name, "END") != 0);
  
  return i;
}


void mnext(int state) {
  int i = -1;
  currstate = state;
  
  while (strcmp(menu[++i].name, "FIN") != 0) {
    if (menu[i].snum == state){
      nowstr(menu[i].name);
      return;
    }
  }
  
  nowstr("nope");
}
