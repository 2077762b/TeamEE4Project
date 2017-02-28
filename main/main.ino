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

#define MAX_CAN_FRAME_DATA_LEN 8

int diagnostics_mode = 0;

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

void gotFrame2000(CAN_FRAME *frame) {
  int CAN_ID = 2000;

  // System works in Display Mode
  if (diagnostics_mode == 0) {
    int16_t RPM = (frame->data.byte[1]<<8) | frame->data.byte[0];
    update_rpm(RPM);
    return;
  }

  // System in Diagnostics Mode
  // update_diagnostics_frame(CAN_ID, frame);
}

void gotFrame2001(CAN_FRAME *frame) {
  int CAN_ID = 2001;

  // System works in Display Mode
  if (diagnostics_mode == 0) {
    int16_t kph = (frame->data.byte[1]<<8) | frame->data.byte[0];
    update_mph(kph * 0.62137 / 10);
    return;
  }
  
  // System in Diagnostics Mode
  // update_diagnostics_frame(CAN_ID, frame);
}

void gotFrame2002(CAN_FRAME *frame) {
  int CAN_ID = 2002;

  // System works in Display Mode
  if (diagnostics_mode == 0) {
      return;
  }
  
  // System in Diagnostics Mode
  // update_diagnostics_frame(CAN_ID, frame);
}

void gotFrame2003(CAN_FRAME *frame) {
  int CAN_ID = 2000;

  // System works in Display Mode
  if (diagnostics_mode == 0) {
    int16_t gear = (frame->data.byte[1]<<8) | frame->data.byte[0];
    update_gear(gear);
    return;
  }

  // System in Diagnostics Mode
  // update_diagnostics_frame(CAN_ID, frame);

}

void gotFrame2004(CAN_FRAME *frame) {
  int CAN_ID = 2004;

  // System works in Display Mode
  if (diagnostics_mode == 0) {
    return;
  }
  
  // System in Diagnostics Mode
  // update_diagnostics_frame(CAN_ID, frame);
}

void gotFrame2005(CAN_FRAME *frame) {
  int CAN_ID = 2005;

  // System works in Display Mode
  if (diagnostics_mode == 0) {
    return;
  }
  
  // System in Diagnostics Mode
  // update_diagnostics_frame(CAN_ID, frame);
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

  Can0.setCallback(1, gotFrame2000);
  Can0.setCallback(2, gotFrame2001);
  Can0.setCallback(3, gotFrame2002);
  Can0.setCallback(4, gotFrame2003);
  Can0.setCallback(5, gotFrame2004);
  Can0.setCallback(6, gotFrame2005);

  /*
  delay(1000);
  if (BOTH_BUTTONS_ARE_PUSHED) {
    diagnostics_mode = 1;
    while(1) {
      if (RIGHT_BUTTON_PUSHED) {
        next_page;
      }
      else if (RIGHT_BUTTON_PUSHED) {
        next_page;
      }
      else (BOTH_BUTTONS_ARE_PUSHED) {
        diagnostics_mode = 0;
      }
    }
  }

  */
  
}

void loop() {

    uint8_t b1 = 1;
    dueFlashStorage.write(0,b1);
    
    CAN_FRAME output;
    output.id = ID_1;
    output.length = MAX_CAN_FRAME_DATA_LEN;
    output.extended = 1;
 
    for (int i=0;i<4000;i++){
      output.data.bytes[0] = 8;
      output.data.bytes[1] = 7;
      output.data.bytes[2] = 0x22;
      output.data.bytes[3] = 0x33;
      output.data.bytes[4] = 0x44;
      output.data.bytes[5] = 0x55;
      output.data.bytes[6] = 0x66;
      output.data.bytes[7] = 0x77;
      Can1.sendFrame(output);
      delay(5000);
    }
    
}


