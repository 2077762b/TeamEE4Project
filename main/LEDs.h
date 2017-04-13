#include <Adafruit_DotStar.h>
#include <SPI.h>

#define NUM_LEDS   4 //11 // Number of LEDs in strip
#define NUM_GREEN  1 //6
#define NUM_RED    1 //3

#define GREEN      0xFF0000
#define BLUE       0x0000FF
#define RED        0x00FF00

#define DATAPIN    10   // PC29
#define CLOCKPIN   70   // PA17

void setup_leds();
int set_leds (int num_leds);
