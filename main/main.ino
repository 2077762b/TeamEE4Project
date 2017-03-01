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

  */
  
}

void loop() {

    //update_config();

    CAN_FRAME output;
    output.id = ID_4;
    output.length = MAX_CAN_FRAME_DATA_LEN;
    output.extended = 1;
 
    for (int i=0;i<4000;i++){
      output.data.bytes[0] = 0x05;
      output.data.bytes[1] = 0x00;
      output.data.bytes[2] = 0x22;
      output.data.bytes[3] = 0x33;
      output.data.bytes[4] = 0x44;
      output.data.bytes[5] = 0x55;
      output.data.bytes[6] = 0x66;
      output.data.bytes[7] = 0x77;
      Can1.sendFrame(output);
      delay(100);
    }    
}


