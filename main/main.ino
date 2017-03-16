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

  if (diagnostics_mode) {
    setup_diagnostics_mode();
    setup_can_diagnostics();
  }
  else {
    setup_display_mode();
    setup_can_display();
  }

  /*
   * CODE FOR ENABLING DIAGNOSTICS MODE ON STARTUP
   * 
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

  /*
   * DIAGNOSTICS MODE TEST:
   * 
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

  update_diagnostics(&output1);
  output1.id = TEST_ID;
  update_diagnostics(&output1);
  output1.id = ID_4;
  update_diagnostics(&output1);
  output1.id = ID_5;
  update_diagnostics(&output1);
  output1.id = ID_6;
  update_diagnostics(&output1);

  delay(2000);

  setup_page(1);
  
  delay(2000);

  output1.id = TEST_ID;
  update_diagnostics(&output1);

  delay(2000);

  diagnostics_mode = 1;
  setup_display_mode();

  */

}

void loop() {
  // update_config();

  Can1.begin(CAN_BPS_250K);
  
  CAN_FRAME output1;
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

  output1.id = ID_1;

  Can1.sendFrame(output1);
  delay(100);

  count++;

  Serial.print(count);
  Serial.print('\n');

}


