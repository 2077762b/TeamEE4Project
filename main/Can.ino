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
  Can1.begin(CAN_BPS_250K);
  
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
  return;
}

void gotFrame2000(CAN_FRAME *frame) {
 
  // System works in Display Mode
  if (diagnostics_mode == 0) {
    int16_t RPM = (frame->data.byte[1]<<8) | frame->data.byte[0];
    update_rpm(RPM);
    return;
  }

  // System in Diagnostics Mode
  // update_diagnostics_frame(frame);
}

void gotFrame2001(CAN_FRAME *frame) {

  // System works in Display Mode
  if (diagnostics_mode == 0) {
    int16_t kph = (frame->data.byte[1]<<8) | frame->data.byte[0];
    update_mph(kph * 0.62137 / 10);
    return;
  }
  
  // System in Diagnostics Mode
  // update_diagnostics_frame(frame);
}

void gotFrame2003(CAN_FRAME *frame) {

  // System works in Display Mode
  if (diagnostics_mode == 0) {
    int16_t gear = (frame->data.byte[1]<<8) | frame->data.byte[0];
    update_gear(gear);
    printFrame(frame,3);
    Serial.println(gear);
    return;
  }

  // System in Diagnostics Mode
  // update_diagnostics_frame(frame);

}

/*
void update_diagnostics_frame(can_id, frame) {
  int16_t value_1 = (frame->data.byte[1]<<8) | frame->data.byte[0];
  int16_t value_2 = (frame->data.byte[3]<<8) | frame->data.byte[2];
  int16_t value_3 = (frame->data.byte[5]<<8) | frame->data.byte[4];
  int16_t value_4 = (frame->data.byte[7]<<8) | frame->data.byte[6];

  update_diagnostics(CAN_ID, value_1);
  update_diagnostics(CAN_ID, value_2);
  update_diagnostics(CAN_ID, value_3);
  update_diagnostics(CAN_ID, value_4);
}
*/

