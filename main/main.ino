#include "dash_functions.h"
#include "config.h"
#include "Can.h"
#include "LEDs.h"

int count;
int lock;

int gear = 0; // Current gear
int gearUpPin = 53; // Pin used for gear up button
int gearDownPin = 51; // Pin used for gear down button
unsigned long lastInterruptTimeUp = 0;  // the last time the output pin was toggled
unsigned long lastInterruptTimeDown = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
int buttonStateUp;             // the current reading from the input pin
int buttonStateDown;             // the current reading from the input pin

#define sender  // Define if writing to test unit

#ifdef sender

  void sendBack(CAN_FRAME *frame){
    
  }
  // Executes if gear up has generated an interrupt
  void gearUp(){

    int reading = digitalRead(gearUpPin);  // Read button pin
    unsigned long interruptTime = millis(); // Get current time

    // Debouncing switch
    if ((interruptTime - lastInterruptTimeUp) > debounceDelay) {
      if (reading != buttonStateUp) {
        buttonStateUp = reading;    
        
        // Pass over CAN that the switch has been pressed
        if (buttonStateUp == HIGH && buttonStateDown == HIGH && lock == 0){ 
          lock = 1;         
          CAN_FRAME output;
          output.id = TEST_ID;
          output.length = 8;
          output.extended = 1;
          output.data.s0 =  0; 
          Can0.sendFrame(output);
          delay(500);
          lock = 0;
        }
        if (buttonStateUp == HIGH && gear != 6) gear++; // Increment gear
      }
    }
    lastInterruptTimeUp = interruptTime;
  }

  // Executes if gear down has generated an interrupt
  void gearDown(){
  
    int reading = digitalRead(gearDownPin); // Read button pin
    unsigned long interruptTime = millis(); // Get current time

    // Debouncing switch
    if ((interruptTime - lastInterruptTimeDown) > debounceDelay) {
      if (reading != buttonStateDown) {
        buttonStateDown = reading;    
        
        // Pass over CAN that the switch has been pressed
        if (buttonStateUp == HIGH && buttonStateDown == HIGH && lock == 0){     
          lock = 1;     
          CAN_FRAME output;
          output.id = TEST_ID;
          output.length = 8;
          output.extended = 1;
          output.data.s0 =  0; 
          Can0.sendFrame(output);
          delay(500);
          lock = 0;
        }
        if (buttonStateDown == HIGH && gear != 0) gear--;   // Decrement gear
      }
    }
    lastInterruptTimeDown = interruptTime;
  }
#endif

void setup()
{

  #ifndef sender
    // Set up all elements
    setup_screen();
    setup_config();
    setup_can();
    setup_leds();
    setup_display_mode();
    setup_can_display();
  #else
    setup_can();
    setup_can_display();
    // Set up interrupts for gear buttons
    pinMode(gearUpPin, INPUT);
    attachInterrupt(digitalPinToInterrupt(gearUpPin), gearUp, CHANGE);
    pinMode(gearDownPin, INPUT);
    attachInterrupt(digitalPinToInterrupt(gearDownPin), gearDown, CHANGE);
    
  #endif
 


}

void loop() {

  #ifdef sender

    // Read RPM analog input
    int sensorValue = analogRead(A0);
    
    CAN_FRAME output1, output2, output3, output4;

    // Create RPM/Coolant CAN packet
    output1.id = ID_1;
    output1.length = 8;
    output1.extended = 1;
    output1.data.s0 =  sensorValue * (14000 / 1023.0); // RPM uses analog input
    output1.data.s2 = count%120; // COOLANT

    // Create Speed CAN packet
    output2.id = ID_2;
    output2.length = 8;
    output2.extended = 1;
    output2.data.s2 = (count*10)%1500; // Speed

    // Create volts CAN packet
    output3.id = ID_3;
    output3.length = 8;
    output3.extended = 1;
    output3.data.s2 = count%1010; // volts

    // Create gear CAN packet
    output4.id = ID_4;
    output4.length = 8;
    output4.extended = 1;
    output4.data.s0 = gear; // Gear uses value as determined by button interrupt functions

    // Send CAN packets
    Can0.sendFrame(output1);
    delay(40);
    Can0.sendFrame(output2);
    delay(40);
    Can0.sendFrame(output3);
    delay(40);
    Can0.sendFrame(output4);
    delay(40);
    count++;

  #else
    // Config always running in normal operation
    CAN_FRAME output;
    output.id = ID_4;
    output.length = 8;
    output.extended = 1;
    output.data.s0 = gear;
    Can0.sendFrame(output);
    delay(1000);
    //update_config();
  #endif
}



