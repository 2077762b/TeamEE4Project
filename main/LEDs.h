#include <Adafruit_DotStar.h>
#include <SPI.h>

#define NUM_LEDS   12 
#define NUM_GREEN  6 
#define NUM_RED    3 

#define GREEN      0x550000
#define RED        0x005500
#define BLUE       0x000055

#define DATAPIN    74   // PC29
#define CLOCKPIN   75   // PA17

void setup_leds();
int set_leds (int num_leds);
