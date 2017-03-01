#include "dash_functions.h"

int fuel_start, oil_start, cool_start;

// Show gauges
void setup_screen(){
  
  init_LCD();
  setup_font_24();
  setup_font_48();
  setup_font_96();
  
  // Show start-up image
  //display_ppm_image(0,0,SOURCE,GATE,formula_1_image);
  //delay(4000);

  // Setup labels on screen
  clear_area(0,0,SOURCE,GATE);
  cool_start = write_word("Cool:\n",200,130,1,1,1,24);
  write_word("mph\n",30,80,1,1,1,24);
  write_word("rpm\n",30,200,1,1,1,24);
  write_word("Gear\n",125,130,1,1,1,24);
}
   
void update_cool(int level){
  
  clear_area(cool_start,130, SOURCE - cool_start, 24);
  
  // Make sure only 3 digits
  if (level > 999) level = 999;

  // Warning colour
  int r = 0, g = 0;
  if (level > COOL_THRESHOLD) r = 1;
  else g = 1;
  set_coolant(r);
    
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

void set_coolant(int state){
  if (state) display_ppm_image(190,175,48,48,coolant_image);
  else clear_area(190,175,48,48);
}

