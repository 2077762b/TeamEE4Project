#include "dash_functions.h"
#include "config.h"
#include "Can.h"

int diagnostics_mode = 0;
int count = 0;

void setup()
{
  setup_screen();
  setup_config();
  setup_can();

  diagnostics_mode = 1;

  if (!diagnostics_mode) setup_display_mode();
  else setup_diagnostics_mode();
  
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
  output1.data.bytes[1] = 0x1F; // RPM
  output1.data.bytes[2] = 0x3C;
  output1.data.bytes[3] = 0x97;
  output1.data.bytes[4] = 0x8; // COOLANT
  output1.data.bytes[5] = 0x0; // COOLANT
  output1.data.bytes[6] = 0xAB;
  output1.data.bytes[7] = 0xED;

  CAN_FRAME output2;
  output2.id = ID_2;
  output2.length = 8;
  output2.extended = 1;
  output2.data.bytes[0] = 0x44;
  output2.data.bytes[1] = 0x44;
  output2.data.bytes[2] = 0x44;
  output2.data.bytes[3] = 0x44;
  output2.data.bytes[4] = 0x44; // SPEED
  output2.data.bytes[5] = 0x44; // SPEED
  output2.data.bytes[6] = 0x44;
  output2.data.bytes[7] = 0x44;

  CAN_FRAME output3;
  output3.id = TEST_ID;
  output3.length = 8;
  output3.extended = 1;
  output3.data.value = 0;

  update_diagnostics(&output1);
  update_diagnostics(&output2);
  output3.id = ID_4;
  update_diagnostics(&output3);
  output3.id = ID_5;
  update_diagnostics(&output3);
  output3.id = ID_6;
  update_diagnostics(&output3);
  
  CAN_FRAME output4;
  output4.id = ID_3;
  output4.length = 8;
  output4.extended = 1;
  for (uint64_t i = 0; i < 2^64; i++){
    output4.data.value = i;
    update_diagnostics(&output4);   
    delay(100);
  }
  


}

void loop() {
  // update_config();

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


