#ifndef CAN_H_  
#define CAN_H_

#include "variant.h"
#include <due_can.h>

#define ID_1 0x2000 // RPM - TPS (%) - Water Temperature (C) - Air Temperature (C)
#define ID_2 0x2001 // Manifold Absolute Pressure (Kpa) - Lambda x1000 - KPH x10 - Oil Pressure (Kpa
#define ID_3 0x2002 // Fuel Pressure (Kpa) - Oil Temperature (C) - Volts x 10 - Fuel Consumption L/100Km x 10 
#define ID_4 0x2003 // Gear - Advance Deg x10 - Injection ms x 100 - Fuel Consumption L/Hr x 10 
#define ID_5 0x2004 // Ana1 mV - Ana2 mV - Ana3 mV - Cam Advance x 10 
#define ID_6 0x2005 // Cam Targ x 10 - Cam PWM x 10 - Crank Errors - Cam Error

#define MAX_CAN_FRAME_DATA_LEN 8
void setup_can();

#endif
