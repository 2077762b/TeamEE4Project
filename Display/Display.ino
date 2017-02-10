#include "font24.h"
#include "Display_driver.h"

int fuel_start, oil_start, cool_start;

void setup() {
  init_LCD();
  setup_font_24();
  setup_screen();
}

// the loop function runs over and over again forever
void loop() {
    for (int i = 100; i >= 0; i--){
      update_fuel(i);
      delay(100);
    }
}

// Show gauges
void setup_screen(){
  fuel_start = write_word("Fuel:\n",200,30,1,1,1);
  oil_start = write_word("Oil:\n",200,60,1,1,1);
  cool_start = write_word("Cool:\n",200,90,1,1,1);
}

void update_fuel(int level){

  // Make sure fuel is a proper percentage
  if (level > 100) level = 100;

  // Warning colour
  int r = 0, g = 0, b = 0;
  if (level < FUEL_THRESHOLD) r = 1;
  else g = 1;
    
  char str[5]; 
  sprintf(str, "%d%\n", level);
  write_word(str,fuel_start,30,r,g,b);
}

