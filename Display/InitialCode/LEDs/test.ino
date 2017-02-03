#include "LEDs.h"

void setup() {
  setup_leds();
}

void loop() {
  
  set_leds(11);
  delay(100);
  set_leds(2);
  delay(100);

}
