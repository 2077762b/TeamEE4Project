#ifndef DASH_FUNCTIONS_H_  
#define DASH_FUNCTIONS_H_

#include "Display_driver.h"

//#include "formula1.h"
#include "coolant.h"
#include "config.h"

#define CAN_ID_START 30

void setup_screen();
   
void update_cool(int level);
void update_mph(int level);
void update_rpm(int level);
void update_gear(int level);
void set_coolant(int state);

#endif
