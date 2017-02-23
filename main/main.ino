#include "dash_functions.h"
#include "variant.h"
#include <due_can.h>
#include <DueFlashStorage.h>

#define GEAR_ID 0x1A0
#define SPEED_ID 0x1E0
#define OIL_ID 0x260
#define COOLANT_ID 0x2E0
#define FUEL_ID 0x360
#define RPM_ID 0x0E0

#define MAX_CAN_FRAME_DATA_LEN   8

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
       Serial.print(" ");
   }
   Serial.print("\r\n");
}

void gotFrameMB0(CAN_FRAME *frame) {   printFrame(frame,0);   update_gear(frame->data.bytes[0]); }
void gotFrameMB1(CAN_FRAME *frame) {   printFrame(frame,1);   update_mph(frame->data.bytes[0]);  }
void gotFrameMB2(CAN_FRAME *frame) {   printFrame(frame,2);   update_oil(frame->data.bytes[0]);  }
void gotFrameMB3(CAN_FRAME *frame) {   printFrame(frame,3);   update_cool(frame->data.bytes[0]); }
void gotFrameMB4(CAN_FRAME *frame) {   printFrame(frame,4);   update_fuel(frame->data.bytes[0]); }
void gotFrameMB5(CAN_FRAME *frame) {   printFrame(frame,5);   update_rpm(frame->data.bytes[0]);  }

void setup()
{

  Serial.begin(9600);

  setup_screen();
  
  Can0.begin(CAN_BPS_250K);
  Can1.begin(CAN_BPS_250K);
  
  Can0.setRXFilter(0, GEAR_ID, 0x7FF, false);
  Can0.setRXFilter(1, SPEED_ID, 0x7FF, false); 
  Can0.setRXFilter(2, OIL_ID, 0x7FF, false); 
  Can0.setRXFilter(3, COOLANT_ID, 0x7FF, false); 
  Can0.setRXFilter(4, FUEL_ID, 0x7FF, false); 
  Can0.setRXFilter(5, RPM_ID, 0x7FF, false); 

  Can0.setCallback(0, gotFrameMB0);
  Can0.setCallback(1, gotFrameMB1);
  Can0.setCallback(2, gotFrameMB2);
  Can0.setCallback(3, gotFrameMB3);
  Can0.setCallback(4, gotFrameMB4);
  Can0.setCallback(5, gotFrameMB5);
  
}

void loop() {
    CAN_FRAME output;
    output.id = GEAR_ID;
    output.length = MAX_CAN_FRAME_DATA_LEN;
    output.data.high = 0;

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
 
    for (int i=0;i<6;i++){
      output.data.low = i;
      Can1.sendFrame(output);
      delay(1000);
    }
}


