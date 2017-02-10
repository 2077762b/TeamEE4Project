#include "Display_driver.h"

int fuel_start, oil_start, cool_start;

void setup() {
  init_LCD();
  
  // Show start-up image
  display_ppm_image(0,0,SOURCE,GATE,formula_1_image);

  // Load fonts
  setup_font_24();
  setup_font_48();
  setup_font_96();

  delay(4000);

  // Setup labels on screen
  clear_area(0,0,SOURCE,GATE);
  setup_screen();
}

// the loop function runs over and over again forever
void loop() {
    update_oil(87);
    update_cool(65);
    update_fuel(15);
    update_mph(125);
    update_rpm(104);
    
    for (int i = 0; i < 9; i++){
      update_gear(i);
      delay(1000);
    }
}

// Show gauges
void setup_screen(){
  fuel_start = write_word("Fuel:\n",200,30,1,1,1,24);
  oil_start = write_word("Oil:\n",200,80,1,1,1,24);
  cool_start = write_word("Cool:\n",200,130,1,1,1,24);
  write_word("mph\n",30,80,1,1,1,24);
  write_word("rpm\n",30,200,1,1,1,24);
  write_word("Gear\n",125,130,1,1,1,24);
}
   
void update_fuel(int level){

  clear_area(fuel_start,30, SOURCE - fuel_start, 24);
  // Make sure fuel is a proper percentage
  if (level > 100) level = 100;

  // Warning colour
  int r = 0, g = 0, b = 0;
  if (level < FUEL_THRESHOLD) r = 1;
  else g = 1;
    
  char str[6]; 
  sprintf(str, "%d%%\n", level);
  write_word(str,fuel_start,30,r,g,b,24);
}

void update_oil(int level){

  clear_area(oil_start,80, SOURCE - oil_start, 24);
  // Make sure only 3 digits
  if (level > 999) level = 999;

  // Warning colour
  int r = 0, g = 0;
  if (level > OIL_THRESHOLD) r = 1;
  else g = 1;
    
  char str[6]; 
  sprintf(str, "%d'C\n", level);
  write_word(str,oil_start,80,r,g,0,24);
}

void update_cool(int level){
  
  clear_area(cool_start,130, SOURCE - cool_start, 24);
  
  // Make sure only 3 digits
  if (level > 999) level = 999;

  // Warning colour
  int r = 0, g = 0;
  if (level > COOL_THRESHOLD) r = 1;
  else g = 1;
    
  char str[5]; 
  sprintf(str, "%d'C\n", level);
  write_word(str,cool_start,130,r,g,0,24);
}

void update_mph(int level){
  
  clear_area(15,20,95,48);

  // Make sure only 3 digits
  if (level > 999) level = 999;

  char str[5]; 
  sprintf(str, "%d\n", level);
  write_word(str,15,20,1,1,1,48);
  
}

void update_rpm(int level){
  
  clear_area(15,140,95,48);

  // Make sure only 3 digits
  if (level > 999) level = 999;

  char str[5]; 
  sprintf(str, "%d\n", level);
  write_word(str,15,140,1,1,1,48);
  
}

void update_gear(int level){

   clear_area(115,20,67,96);

  // Make sure only 3 digits
  if (level > 999) level = 999;

  char str[5]; 
  sprintf(str, "%d\n", level);
  write_word(str,115,20,1,1,1,96);
}
