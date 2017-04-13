#include "dash_functions.h"
#include "config.h"
#include "Can.h"
#include "LEDs.h"

int diagnostics_mode;
int count = 0;
int gearCount = 0;

void setup()
{
  setup_screen();
  setup_config();
  setup_can();
  setup_leds();
 
  diagnostics_mode = 1;
  if (diagnostics_mode) {
    setup_diagnostics_mode();
    setup_can_diagnostics();
  }
  else {
    setup_display_mode();
    setup_can_display();
  }

  //update_config();
  
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

}

void loop() {
  /*  
  Can0.begin(CAN_BPS_250K);
  
  CAN_FRAME output1, output2, output3, output4;

  output1.id = ID_1;
  output1.length = 8;
  output1.extended = 1;
  output1.data.s0 = (count*600)%14000; // RPM
  output1.data.s2 = count%120; // COOLANT
  
  output2.id = ID_2;
  output2.length = 8;
  output2.extended = 1;
  output2.data.s2 = (count*10)%1500; // Speed

  output3.id = ID_3;
  output3.length = 8;
  output3.extended = 1;
  output3.data.s2 = count%1010; // volts
  
  output4.id = ID_4;
  output4.length = 8;
  output4.extended = 1;
  output4.data.s0 = count%6; // Gear
  
  Can0.sendFrame(output1);
  delay(10);
  Can0.sendFrame(output2);
  delay(10);
  Can0.sendFrame(output3);
  delay(10);
  Can0.sendFrame(output4);
  delay(10);
  count++;
  */
}


