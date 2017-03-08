#include "dash_functions.h"
#include "config.h"
#include "Can.h"

int diagnostics_mode = 0;

int count = 0;

void setup()
{
  setup_screen();
  setup_config();


  diagnostics_mode = 1;

  if (!diagnostics_mode) {
    setup_display_mode();
  }
  else {
    setup_diagnostics_mode();
  }
  
  setup_can();
  
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
  else{
    setup_can();
    setup_display_mode();
  }
  */

  CAN_FRAME output1;
  output1.id = ID_1;
  output1.length = 8;
  output1.extended = 1;
  output1.data.bytes[0] = 0x65; // RPM
  output1.data.bytes[1] = 0x65; // RPM
  output1.data.bytes[2] = 0x65;
  output1.data.bytes[3] = 0x65;
  output1.data.bytes[4] = 0x65; // COOLANT
  output1.data.bytes[5] = 0x65; // COOLANT
  output1.data.bytes[6] = 0x65;
  output1.data.bytes[7] = 0x65;

  CAN_FRAME output2;
  output2.id = ID_2;
  output2.length = 8;
  output2.extended = 1;
  output2.data.bytes[0] = 0x65;
  output2.data.bytes[1] = 0x00;
  output2.data.bytes[2] = 0x00;
  output2.data.bytes[3] = 0x00;
  output2.data.bytes[4] = 0x00; // SPEED
  output2.data.bytes[5] = 0x00; // SPEED
  output2.data.bytes[6] = 0x00;
  output2.data.bytes[7] = 0x00;

  CAN_FRAME output3;
  output3.id = TEST_ID;
  output3.length = 8;
  output3.extended = 1;
  output3.data.bytes[0] = 0x00; // GEAR
  output3.data.bytes[1] = 0x00; // GEAR
  output3.data.bytes[2] = 0x00;
  output3.data.bytes[3] = 0x00;
  output3.data.bytes[4] = 0x00;
  output3.data.bytes[5] = 0x00;
  output3.data.bytes[6] = 0x00;
  output3.data.bytes[7] = 0x00;

  update_diagnostics(&output1);
  update_diagnostics(&output2);
  update_diagnostics(&output3);

  delay(10000);

  set_page(1);

  delay(4000);

  update_diagnostics(&output3);
}

void loop() {
  //update_config();

  /*
  Can1.begin(CAN_BPS_250K);
  CAN_FRAME output1;
  output1.id = ID_1;
  output1.length = 8;
  output1.extended = 1;

  output1.data.bytes[0] = count; // RPM
  output1.data.bytes[1] = count; // RPM
  output1.data.bytes[2] = count;
  output1.data.bytes[3] = count;
  output1.data.bytes[4] = count; // COOLANT
  output1.data.bytes[5] = count; // COOLANT
  output1.data.bytes[6] = count;
  output1.data.bytes[7] = count;
  Can1.sendFrame(output1);
  delay(100);

  count++;

  CAN_FRAME output2;
  output2.id = ID_2;
  output2.length = 8;
  output2.extended = 1;

  output2.data.bytes[0] = 0x00;
  output2.data.bytes[1] = 0x00;
  output2.data.bytes[2] = 0x00;
  output2.data.bytes[3] = 0x00;
  output2.data.bytes[4] = 0x00; // SPEED
  output2.data.bytes[5] = 0x00; // SPEED
  output2.data.bytes[6] = 0x00;
  output2.data.bytes[7] = 0x00;
  Can1.sendFrame(output2);
  delay(100);

  CAN_FRAME output3;
  output3.id = ID_4;
  output3.length = 8;
  output3.extended = 1;

  output3.data.bytes[0] = 0x00; // GEAR
  output3.data.bytes[1] = 0x00; // GEAR
  output3.data.bytes[2] = 0x00;
  output3.data.bytes[3] = 0x00;
  output3.data.bytes[4] = 0x00;
  output3.data.bytes[5] = 0x00;
  output3.data.bytes[6] = 0x00;
  output3.data.bytes[7] = 0x00;
  Can1.sendFrame(output3);
  delay(10000);
  */
}


