#include "Can.h"

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

void setup_can(){  
  Can0.begin(CAN_BPS_250K);
  
  Can0.setRXFilter(1, ID_1, 0x1FFFFFFF, true);
  Can0.setRXFilter(2, ID_2, 0x1FFFFFFF, true);
  Can0.setRXFilter(3, ID_4, 0x1FFFFFFF, true);
  Can0.setRXFilter(4, 0, 0, true); //catch all mailbox

  Can0.setCallback(1, gotFrame2000);
  Can0.setCallback(2, gotFrame2001);
  Can0.setCallback(3, gotFrame2003);
  Can0.setGeneralCallback(gotFrame);
}

void gotFrame(CAN_FRAME *frame){
  // Only prints frame if system is in Diagnostics mode
  if (diagnostics_mode == 1) {
    update_diagnostics(frame->id, frame->data.bytes, frame->length);
  }
}

void gotFrame2000(CAN_FRAME *frame) {
    
  // Only updates values if system is in Display mode
  if (diagnostics_mode == 0) {
    // RPM
    int16_t RPM = (frame->data.byte[1]<<8) | frame->data.byte[0];
    update_rpm(RPM);
    
    // Coolant
    int16_t coolant = (frame->data.byte[5]<<8) | frame->data.byte[4];
    update_cool(coolant);
    return;
  }

}

void gotFrame2001(CAN_FRAME *frame) {
    
  // Only updates values if system is in Display mode
  if (diagnostics_mode == 0) {
    // Speed
    int16_t speed = (frame->data.byte[5]<<8) | frame->data.byte[4];
    int corrected_speed = (int) speed/10.0;
    update_speed(corrected_speed);
    return;
  }

}

void gotFrame2003(CAN_FRAME *frame) {

  // Only updates values if system is in Display mode
  if (diagnostics_mode == 0) {
    // Gear
    int16_t gear = (frame->data.byte[1]<<8) | frame->data.byte[0];
    update_gear(gear);
    return;
  }

}