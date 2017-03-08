#include "dash_functions.h"

int cool_start;

// Show gauges
void setup_screen(){
  init_LCD();
  setup_font_24();
  setup_font_48();
  setup_font_96();
  
  // Show start-up image
  //display_ppm_image(0,0,SOURCE,GATE,formula_1_image);
  //delay(4000);
}

void setup_display_mode(){
  // Setup labels on screen
  clear_area(0,0,SOURCE,GATE);
  cool_start = write_word("Cool:\n",200,130,1,1,1,24);
  write_word("rpm\n",15,210,1,1,1,24);
  write_word("Gear\n",120,130,1,1,1,24);
  
  if (configuration.speed_units == MPH) {
    write_word("mph\n",15,80,1,1,1,24);
  }
  else {
    write_word("kph\n",30,80,1,1,1,24);
  }
}

void setup_diagnostics_mode(){
  set_page(0);
}

void set_page(int page_number){
  // Clears whole screen
  clear_area(0,0,SOURCE,GATE);
  
  if (page_number <= MAX_CAN_PAGES){
    for (int i = 0; i < CAN_IDS_PER_PAGE; i++){
      char id[8*4];
      sprintf(id, "%04x\n", configuration.can_pages[page_number][i]);
      write_word(id,CAN_ID_START,20,1,1,1,24);
    }
  }

  current_page = page_number;
}

void update_diagnostics(CAN_FRAME *frame){
  int location_on_page = -1;
  if (current_page != configuration.num_pages-1) {
    for (int i = 0; i < CAN_IDS_PER_PAGE; i++) {
      if (configuration.can_pages[current_page][i] == frame->id) {
        location_on_page = i;
        break;
      }
    }
    return;
  }

  Serial.print(location_on_page);

  char value[frame->length+1];
  for (int i = 0; i<frame->length; i++){
    sprintf(&value[2*i], "%02x", frame->data.bytes[i]);
  }
  value[frame->length+1] = '\n';

  clear_area(CAN_VALUE_START,(location_on_page+1)*30,CAN_VALUE_START+24,GATE);
  write_word(value,CAN_VALUE_START,(location_on_page+1)*30,1,1,1,24);
}

void update_cool(int level){
  clear_area(cool_start,130,SOURCE-cool_start,24);

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

void update_speed(int level){
  int speed = level;

  if (configuration.speed_units == MPH) {
    float conversion_factor = 0.62137;
    int speed = (int) level*conversion_factor;
  }
  
  clear_area(15,20,95,48);

  char str[5];

  // Make sure only 3 digits
  if (speed > 99) {
    sprintf(str, "%03d\n", speed);
  }
  else if (speed > 9) {
    sprintf(str, "%02d\n", speed);
  }
  else {
    sprintf(str, "%01d\n", speed);
  }

  write_word(str,15,20,1,1,1,48);
}

void update_rpm(int level){
  clear_area(15,160,95,48);

  // Make sure only 3 digits
  if (level > 999) level = 999;

  char str[5]; 
  sprintf(str, "%05d\n", level);
  write_word(str,15,160,1,1,1,48);
}

void update_gear(int level){
  clear_area(115,20,67,96);

  // Make sure only 1 digit
  if (level > 9) level = 9;

  char str[5];
  sprintf(str, "%01d\n", level);
  write_word(str,115,20,1,1,1,96);
}

void set_coolant(int state){
  if (state) display_ppm_image(190,175,48,48,coolant_image);
  else clear_area(190,175,48,48);
}

