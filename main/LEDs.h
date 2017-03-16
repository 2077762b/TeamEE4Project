#include <Adafruit_DotStar.h>
#include <SPI.h>

#define NUM_LEDS 11 // Number of LEDs in strip
#define DATAPIN    10
#define CLOCKPIN   9

void setup_leds();
int set_leds (int num_leds);
