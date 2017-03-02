#include "dash_functions.h"
#include "config.h"
#include "Can.h"

int diagnostics_mode = 0;

void setup()
{
  setup_screen();
  setup_config();
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
    setup_display_mode();
  }

  */
  
}

void loop() {
    Can1.begin(CAN_BPS_250K);

    CAN_FRAME output1;
    output1.id = ID_1;
    output1.length = 8;
    output1.extended = 1;
    diagnostics_mode = 1;
    //update_config();
 
    for (int i=0;i<4000;i++){
      output1.data.bytes[0] = 0x05;
      output1.data.bytes[1] = 0x00;
      output1.data.bytes[2] = 0x22;
      output1.data.bytes[3] = 0x33;
      output1.data.bytes[4] = 0x44;
      output1.data.bytes[5] = 0x55;
      output1.data.bytes[6] = 0x66;
      output1.data.bytes[7] = 0x77;
      Can1.sendFrame(output1);
      delay(1000);
    }

    CAN_FRAME output2;
    output2.id = ID_2;
    output2.length = 8;
    output2.extended = 1;
 
    for (int i=0;i<4000;i++){
      output2.data.bytes[0] = 0x05;
      output2.data.bytes[1] = 0x00;
      output2.data.bytes[2] = 0x22;
      output2.data.bytes[3] = 0x33;
      output2.data.bytes[4] = 0x44;
      output2.data.bytes[5] = 0x55;
      output2.data.bytes[6] = 0x66;
      output2.data.bytes[7] = 0x77;
      Can1.sendFrame(output2);
      delay(1000);
    }    
}


