#include "Can.h"

int diagnostics_mode = 0;
int counter = 0;

void setup_can(){ Can0.begin(CAN_BPS_250K); } // Initialise CAN

void disable_can(){ Can0.disable(); } // Disable CAN

// Set up mailboxes and interrupts for each required ID for regular display mode
void setup_can_display(){
  Can0.setRXFilter(0, ID_1, 0x1FFFFFFF, true);
  Can0.setRXFilter(1, ID_2, 0x1FFFFFFF, true);
  Can0.setRXFilter(2, ID_3, 0x1FFFFFFF, true);
  Can0.setRXFilter(3, ID_4, 0x1FFFFFFF, true);
  Can0.setRXFilter(4, TEST_ID, 0x1FFFFFFF, true);
  Can0.attachCANInterrupt(0, gotFrame2000);
  Can0.attachCANInterrupt(1, gotFrame2001);
  Can0.attachCANInterrupt(2, gotFrame2002);
  Can0.attachCANInterrupt(3, gotFrame2003);
  Can0.attachCANInterrupt(4, switchMode);
}

// If in diagnostics extract all data from CAN bus
void setup_can_diagnostics(){
  Can0.setRXFilter(0, TEST_ID, 0x1FFFFFFF, true);
  Can0.attachCANInterrupt(0, switchMode);
  Can0.setRXFilter(1,0, 0, true); //catch all IDs
  Can0.setGeneralCallback(gotFrame);
}

void switchMode(CAN_FRAME *frame){
  
    disable_can();
    setup_can();
    diagnostics_mode = !diagnostics_mode;
    if (diagnostics_mode) {
      // Setup screen for diagnostics mode
      setup_diagnostics_mode();
      setup_can_diagnostics();
    }
    else {
      // Setup screen for normal operation
      setup_display_mode();
      setup_can_display();
    }
}

// Callback for diagnostics mode
void gotFrame(CAN_FRAME *frame){
  update_diagnostics(frame);
}

// Extract data from frame with ID 2000 and update display
void gotFrame2000(CAN_FRAME *frame) { 
  int16_t RPM = (frame->data.byte[1]<<8) | frame->data.byte[0]; // extract rpm from CAN data
  update_rpm(RPM); 
  int16_t coolant = (frame->data.byte[5]<<8) | frame->data.byte[4]; // extract coolant temp from CAN data
  update_cool(coolant);
}

// Extract data from frame with ID 2001 and update display
void gotFrame2001(CAN_FRAME *frame) {
  int16_t speed = (frame->data.byte[5]<<8) | frame->data.byte[4]; // extract speed from CAN data
  int corrected_speed = (int) speed/10.0; // Adjust speed (speed multiplied by 10 for transmission on CAN)
  update_speed(corrected_speed); 
}

// Extract data from frame with ID 2002 and update display
void gotFrame2002(CAN_FRAME *frame) {
  int16_t volts = (frame->data.byte[5]<<8) | frame->data.byte[4]; // extract volts from CAN data
  update_volts(volts);
}

// Extract data from frame with ID 2003 and update display
void gotFrame2003(CAN_FRAME *frame) {
  int16_t gear = (frame->data.byte[1]<<8) | frame->data.byte[0]; // extract gear from CAN data
  update_gear(gear);
  pinMode(1, OUTPUT);
  counter++;
  if (counter%2 == 1) digitalWrite(1, HIGH);
  else digitalWrite(1, LOW);
  #ifdef sender
    CAN_FRAME output;
    output.id = ID_4;
    output.length = 8;
    output.extended = 1;
    output.data.s0 = gear;
    Can0.sendFrame(output);
  #endif
}

