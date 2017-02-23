#ifndef DASH_FUNCTIONS_H_  
#define DASH_FUNCTIONS_H_

#include "Display_driver.h"

//#include "formula1.h"
#include "fuel.h"
#include "coolant.h"
#include "oil.h"

#define OIL_THRESHOLD 100
#define FUEL_THRESHOLD 20
#define COOL_THRESHOLD 80

void setup_screen();
   
void update_fuel(int level);
void update_oil(int level);
void update_cool(int level);
void update_mph(int level);
void update_rpm(int level);
void update_gear(int level);
void set_fuel(int state);
void set_coolant(int state);
void set_oil(int state);

#endif
