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

/*
// Oil level
void write_oil(int level, int x, int y){

    // Make sure fuel is a proper percentage
    if (level > 999) level = 999;

    int r = 0,g = 1;
    if (level > OIL_THRESHOLD) {
      r = 1;
      g = 0;
    }
    clear_area(x,y,SOURCE-x,24);
    
    if (level >= 100) {
         write_char(x, y, 16, 24, numbers_24[(level/100)%10],r,g,0);
         if ((level/100)%10 == 1) x = x + 10;
         else x = x + 14;
    }
    if (level >= 10) {
         write_char(x, y, 16, 24, numbers_24[(level/10)%10],r,g,0);
         if ((level/10)%10 == 1) x = x + 10;
         else x = x + 14;
    }
    write_char(x, y, 16, 24, numbers_24[level%10],r,g,0);
    if (level%10 == 1) x = x + 10;
    else x = x + 14;

    write_char(x, y, degree_24_blocks*8, 24, degree_24,r,g,0);
    x = x + 8;
    write_char(x, y, C_24_blocks*8, 24, C_24,r,g,0);
}
*/
