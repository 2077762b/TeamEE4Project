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

int set_leds (int num_leds) {
  if (num_leds > NUM_LEDS) return 1;

  // Clear all pixels
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, 0);
  }
  
  uint32_t color = 0xFF0000;      // 'On' color (starts green)
  int number_green = int(NUM_LEDS * 0.7) - 1;
  
  for (int i = 0; i < num_leds; i++) {
    if (i > number_green) {
      color = 0x00FF00;
    }
    strip.setPixelColor(i, color);
  }
  
  strip.show();                     // Refresh strip

  return 0;
}


