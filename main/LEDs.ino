#include "LEDs.h"

Adafruit_DotStar strip = Adafruit_DotStar(
  NUM_LEDS, DATAPIN, CLOCKPIN, DOTSTAR_BRG);

void setup_leds() {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000L)
  clock_prescale_set(clock_div_1); // Enable 16 MHz on Trinket
#endif

  strip.begin(); // Initialize pins for output
  strip.show();  // Turn all LEDs off ASAP
}

int set_leds(int num_leds) {
  if (num_leds > NUM_LEDS) return 1;

  // Clear all pixels
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, 0);
  }
  
  for (int i = 0; i < num_leds; i++) {
    if (i < NUM_GREEN) {
      strip.setPixelColor(i, GREEN);
    }
    else if (i < NUM_GREEN + NUM_RED) {
      strip.setPixelColor(i, RED);
    }
    else{
      strip.setPixelColor(i, BLUE);
    }
  }
  
  strip.show(); // Refresh strip

  return 0;
}


