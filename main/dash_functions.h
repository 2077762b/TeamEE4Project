#ifndef DASH_FUNCTIONS_H_  
#define DASH_FUNCTIONS_H_

#include <due_can.h>

#include "Display_driver.h"
//#include "formula1.h"
#include "coolant.h"
#include "config.h"

#define CAN_ID_START 30
#define CAN_VALUE_START 110

void setup_screen();

void set_page(int page_number);
void update_diagnostics(CAN_FRAME frame);

void update_cool(int level);
void update_mph(int level);
void update_rpm(int level);
void update_gear(int level);
void set_coolant(int state);

#endif
