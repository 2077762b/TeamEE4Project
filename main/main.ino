#include "dash_functions.h"
#include "variant.h"
#include <due_can.h>
#include <DueFlashStorage.h>

#define ID_1 0x2000 // RPM - TPS (%) - Water Temperature (C) - Air Temperature (C)
#define ID_2 0x2001 // Manifold Absolute Pressure (Kpa) - Lambda x1000 - KPH x10 - Oil Pressure (Kpa
#define ID_3 0x2002 // Fuel Pressure (Kpa) - Oil Temperature (C) - Volts x 10 - Fuel Consumption L/100Km x 10 
#define ID_4 0x2003 // Gear - Advance Deg x10 - Injection ms x 100 - Fuel Consumption L/Hr x 10 
#define ID_5 0x2004 // Ana1 mV - Ana2 mV - Ana3 mV - Cam Advance x 10 
#define ID_6 0x2005 // Cam Targ x 10 - Cam PWM x 10 - Crank Errors - Cam Error

#define MAX_CAN_FRAME_DATA_LEN 48

DueFlashStorage dueFlashStorage;

void printFrame(CAN_FRAME *frame, int filter) {
   Serial.print("Fltr: ");
   if (filter > -1) Serial.print(filter);
   else Serial.print("???");
   Serial.print(" ID: 0x");
   Serial.print(frame->id, HEX);
   Serial.print(" Len: ");
   Serial.print(frame->length);
   Serial.print(" Data: 0x");
   for (int count = 0; count < frame->length; count++) {
       Serial.print(frame->data.bytes[count], HEX);
   }
   Serial.print("\r\n");
}

void gotFrameMB1(CAN_FRAME *frame) {
  printFrame(frame,0);
  Serial.print(frame->data.bytes[0], HEX);
  Serial.print(frame->data.bytes[1], HEX);
  Serial.print(frame->data.bytes[2], HEX);
  Serial.print(frame->data.bytes[3], HEX);
  Serial.print("\n");
}

void gotFrameMB2(CAN_FRAME *frame) {
  printFrame(frame,0);
}

void gotFrameMB3(CAN_FRAME *frame) {
  printFrame(frame,0);
}

void gotFrameMB4(CAN_FRAME *frame) {
  printFrame(frame,0);
}

void gotFrameMB5(CAN_FRAME *frame) {
  printFrame(frame,0);
}

void gotFrameMB6(CAN_FRAME *frame) {
  printFrame(frame,0);
}

void setup()
{

  Serial.begin(9600);

  setup_screen();
  
  Can0.begin(CAN_BPS_250K);
  Can1.begin(CAN_BPS_250K);
  
  Can0.setRXFilter(1, ID_1, 0x1FFFFFFF, true);
  Can0.setRXFilter(2, ID_2, 0x1FFFFFFF, true); 
  Can0.setRXFilter(3, ID_3, 0x1FFFFFFF, true); 
  Can0.setRXFilter(4, ID_4, 0x1FFFFFFF, true); 
  Can0.setRXFilter(5, ID_5, 0x1FFFFFFF, true); 
  Can0.setRXFilter(6, ID_6, 0x1FFFFFFF, true); 

  Can0.setCallback(1, gotFrameMB1);
  Can0.setCallback(2, gotFrameMB2);
  Can0.setCallback(3, gotFrameMB3);
  Can0.setCallback(4, gotFrameMB4);
  Can0.setCallback(5, gotFrameMB5);
  Can0.setCallback(6, gotFrameMB6);
  
}

void loop() {
    CAN_FRAME output;
    output.id = ID_1;
    output.length = MAX_CAN_FRAME_DATA_LEN;
    output.extended = 1;

    uint8_t b1 = 1;
    dueFlashStorage.write(0,b1);

    update_gear(1);
    update_oil(87);
    update_cool(65);
    update_fuel(15);
    update_mph(125);
    update_rpm(104);
    set_fuel(1);
    set_coolant(1);
    set_oil(1);
 
    for (int i=0;i<4000;i++){
      output.data.bytes[0] = 0xF;
      output.data.bytes[1] = 0x01;
      output.data.bytes[2] = 0x02;
      output.data.bytes[3] = 0x03;
      output.data.bytes[4] = 0x03;
      output.data.bytes[5] = 0x03;
      output.data.bytes[6] = 0x03;
      output.data.bytes[7] = 0x03;
      Can1.sendFrame(output);
      delay(5000);
    }
}


