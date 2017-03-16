#include <Adafruit_DotStar.h>
#include <SPI.h>

#define NUM_LEDS   11 // Number of LEDs in strip
#define NUM_GREEN  6
#define NUM_RED    3

#define GREEN      0xFF0000
#define BLUE       0x0000FF
#define RED        0x00FF00

#define DATAPIN    10
#define CLOCKPIN   70

void setup_leds();
int set_leds (int num_leds);
