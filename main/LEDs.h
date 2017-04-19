#include <Adafruit_DotStar.h>
#include <SPI.h>

#define NUM_LEDS   11 //12 // Number of LEDs in strip
#define NUM_GREEN  4 //6
#define NUM_RED    4 //3

#define GREEN      0xFF0000
#define RED        0x00FF00
#define BLUE       0x0000FF

#define DATAPIN    75   // PC29
#define CLOCKPIN   76   // PA17

void setup_leds();
int set_leds (int num_leds);
