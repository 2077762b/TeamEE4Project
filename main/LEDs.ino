#include "LEDs.h"

Adafruit_DotStar strip = Adafruit_DotStar(
  NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BRG);

void setup_leds() {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000L)
  clock_prescale_set(clock_div_1); // Enable 16 MHz on Trinket
#endif

  strip.begin(); // Initialize pins for output
  strip.show();  // Turn all LEDs off ASAP
}

int set_leds (int num_leds) {
  if (num_leds > NUMPIXELS) return 1;

  // Clear all pixels
  for (int i = 0; i < NUMPIXELS; i++) {
    strip.setPixelColor(i, 0);
  }
  
  uint32_t color = 0xFF0000;      // 'On' color (starts green)
  int number_green = int(NUMPIXELS * 0.7) - 1;
  
  for (int i = 0; i < num_leds; i++) {
    if (i > number_green) {
      color = 0x00FF00;
    }
    strip.setPixelColor(i, color);
  }
  
  strip.show();                     // Refresh strip

  return 0;
}


