#include <Adafruit_DotStar.h>
#include <SPI.h>

#define NUMPIXELS 11 // Number of LEDs in strip
#define DATAPIN    4
#define CLOCKPIN   5

void setup_leds();
int set_leds (int num_leds);
