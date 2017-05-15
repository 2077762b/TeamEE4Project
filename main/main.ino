#include "dash_functions.h"
#include "config.h"
#include "Can.h"
#include "LEDs.h"

int diagnostics_mode;
int count = 0;
int gearCount = 0;


int gear = 0;
int gearUpPin = 53; 
int gearDownPin = 51; 
unsigned long lastInterruptTimeUp = 0;  // the last time the output pin was toggled
unsigned long lastInterruptTimeDown = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
int buttonStateUp;             // the current reading from the input pin
int buttonStateDown;             // the current reading from the input pin

#define sender 

void gearUp(){

  int reading = digitalRead(gearUpPin);
  unsigned long interruptTime = millis();

  if ((interruptTime - lastInterruptTimeUp) > debounceDelay) {
    if (reading != buttonStateUp) {
      buttonStateUp = reading;    
      if (buttonStateUp == HIGH && gear != 6) gear++;   
    }
  }
  lastInterruptTimeUp = interruptTime;
}

void gearDown(){

  int reading = digitalRead(gearDownPin);
  unsigned long interruptTime = millis();

  if ((interruptTime - lastInterruptTimeDown) > debounceDelay) {
    if (reading != buttonStateDown) {
      buttonStateDown = reading;    
      if (buttonStateDown == HIGH && gear != 0) gear--;   
    }
  }
  lastInterruptTimeDown = interruptTime;
}

void setup()
{

  #ifndef sender
    setup_screen();
    setup_config();
    setup_can();
    setup_leds();
    
    diagnostics_mode = 0;
    if (diagnostics_mode) {
      setup_diagnostics_mode();
      setup_can_diagnostics();
    }
    else {
      setup_display_mode();
      setup_can_display();
    }
  #else
    pinMode(gearUpPin, INPUT);
    attachInterrupt(digitalPinToInterrupt(gearUpPin), gearUp, CHANGE);
    pinMode(gearDownPin, INPUT);
    attachInterrupt(digitalPinToInterrupt(gearDownPin), gearDown, CHANGE);
  #endif
  

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

  #ifdef sender

    int sensorValue = analogRead(A0);
    pinMode(53, INPUT);
    int buttonState = digitalRead(53);

  
    
    Can0.begin(CAN_BPS_250K);
    
    CAN_FRAME output1, output2, output3, output4;
  
    output1.id = ID_1;
    output1.length = 8;
    output1.extended = 1;
    //output1.data.s0 = (count*600)%14000; // RPM
    output1.data.s0 =  sensorValue * (14000 / 1023.0); // RPM
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
    output4.data.s0 = gear; // Gear
    
    Can0.sendFrame(output1);
    delay(40);
    Can0.sendFrame(output2);
    delay(40);
    Can0.sendFrame(output3);
    delay(40);
    Can0.sendFrame(output4);
    delay(40);
    count++;
  #endif
}



