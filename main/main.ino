#include "dash_functions.h"

void setup() {
  setup_screen();
}

void loop() {
    update_oil(87);
    update_cool(65);
    update_fuel(15);
    update_mph(125);
    update_rpm(104);
    toggle_fuel(1);
    toggle_coolant(1);
    toggle_oil(1);
    
    for (int i = 0; i < 9; i++){
      update_gear(i);
      delay(1000);
    }
}


