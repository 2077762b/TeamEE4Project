#include "Can.h"

void printFrame(CAN_FRAME *frame, int filter) {
   SerialUSB.print("Fltr: ");
   if (filter > -1) Serial.print(filter);
   else SerialUSB.print("???");
   SerialUSB.print(" ID: 0x");
   SerialUSB.print(frame->id, HEX);
   SerialUSB.print(" Len: ");
   SerialUSB.print(frame->length);
   SerialUSB.print(" Data: 0x");
   for (int count = 0; count < frame->length; count++) {
       SerialUSB.print(frame->data.bytes[count], HEX);
   }
   SerialUSB.print("\r\n");
}

void setup_can(){
  Can0.begin(CAN_BPS_250K);
}

void setup_can_display(){
  Can0.setRXFilter(0, ID_1, 0x1FFFFFFF, true);
  Can0.setRXFilter(1, ID_2, 0x1FFFFFFF, true);
  Can0.setRXFilter(2, ID_3, 0x1FFFFFFF, true);
  Can0.setRXFilter(3, ID_4, 0x1FFFFFFF, true);
  Can0.attachCANInterrupt(0, gotFrame2000);
  Can0.attachCANInterrupt(1, gotFrame2001);
  Can0.attachCANInterrupt(2, gotFrame2002);
  Can0.attachCANInterrupt(3, gotFrame2003);
}

void setup_can_diagnostics(){
  Can0.setRXFilter(0, 0, true); //catch all IDs
  Can0.setGeneralCallback(gotFrame);
}

void disable_can(){
  Can0.disable();
}

void gotFrame(CAN_FRAME *frame){
  printFrame(frame, -1);

  update_diagnostics(frame);
}

// Only updates values if system is in Display mode
void gotFrame2000(CAN_FRAME *frame) {
  //printFrame(frame, 2000);
  
  // RPM
  int16_t RPM = (frame->data.byte[1]<<8) | frame->data.byte[0];
  update_rpm(RPM);
  
  // Coolant
  int16_t coolant = (frame->data.byte[5]<<8) | frame->data.byte[4];
  update_cool(coolant);
}

// Only updates values if system is in Display mode
void gotFrame2001(CAN_FRAME *frame) {
  //printFrame(frame, 2001);
  
  // Speed
  int16_t speed = (frame->data.byte[5]<<8) | frame->data.byte[4];
  int corrected_speed = (int) speed/10.0;
  update_speed(corrected_speed);
}

void gotFrame2002(CAN_FRAME *frame) {
  //printFrame(frame, 2002);

  // Voltage
  int16_t volts = (frame->data.byte[5]<<8) | frame->data.byte[4];
  update_volts(volts);
}

// Only updates values if system is in Display mode
void gotFrame2003(CAN_FRAME *frame) {
  //printFrame(frame, 2003);

  // Gear
  int16_t gear = (frame->data.byte[1]<<8) | frame->data.byte[0];
  update_gear(gear);
}

