#include "dash_functions.h"

int cool_start, volt_start;

int screen_delay = 0;

// Performs required initialisation for fonts and the display 
void setup_screen(){
  
  // Low level screen configuration
  init_LCD();
  
  // Create font libraries 
  setup_font_24();
  setup_font_48();
  setup_font_96();
  
  // Show start-up image
  display_ppm_image(0,0,SOURCE,GATE,formula_1_image);
  delay(4000);
}

// Set out the screen layout
void setup_display_mode(){

  clear_area(0,0,SOURCE,GATE);
  cool_start = write_word("Cool:\n",200,20,1,1,1,24);
  volt_start = write_word("Volts:\n",200,60,1,1,1,24);
  write_word("rpm\n",15,210,1,1,1,24);
  write_word("Gear\n",120,130,1,1,1,24);

  display_ppm_image(190,180,110,37,ugr_image);
  
  if (configuration.speed_units == MPH) {
    write_word("mph\n",15,80,1,1,1,24);
  }
  else {
    write_word("kph\n",30,80,1,1,1,24);
  }
}

void setup_diagnostics_mode(){
  setup_page(0);
}

int is_last_page(int page_number){
  return page_number == configuration.num_can_ids/configuration.can_ids_per_page;
}

void setup_page(int page_number){
  if (page_number <= configuration.max_num_pages){
    // Clears whole screen
    clear_area(0,0,SOURCE,GATE);
    
    int maximum_ids = configuration.can_ids_per_page;
    
    // Don't print everything if on last page
    if (is_last_page(page_number)) maximum_ids = configuration.num_can_ids%configuration.can_ids_per_page;
    
    for (int location_on_page = 0; location_on_page < maximum_ids; location_on_page++){
      char id[8*4];
      sprintf(id, "%04x\n", configuration.can_pages[page_number][location_on_page]);
      write_word(id,CAN_ID_START,(34*location_on_page+20),1,1,1,24);
    }
    current_page = page_number;
  }
}

void update_diagnostics(CAN_FRAME *frame){
  int location_on_page = -1;
  int maximum_ids = configuration.can_ids_per_page;

  // Don't print everything if on last page
  if (is_last_page(current_page)) maximum_ids = configuration.num_can_ids%configuration.can_ids_per_page;

  for (int i = 0; i < maximum_ids; i++) {
    if (configuration.can_pages[current_page][i] == frame->id) {
      location_on_page = i;
      break;
    }
  }

  if (location_on_page == -1) return;

  char value[MAX_FRAME_SIZE+1];
  sprintf(value,"%08x%08x\n", frame->data.high,frame->data.low);

  clear_area(CAN_VALUE_START,(34*location_on_page+20),SOURCE-CAN_VALUE_START,24);
  write_word(value,CAN_VALUE_START,(34*location_on_page+20),1,1,1,24);
}


// Update the current value of the coolant on the display
void update_cool(int level){
  clear_area(cool_start,20,SOURCE-cool_start,24);

  int coolant = level;

  // Make sure only 3 digits
  if (coolant > 999 || coolant < 0) coolant = 999;

  // Change colour to red if value is above allowed threshold
  int r = 1, g = 1, b = 1;
  if (coolant > configuration.cool_threshold){
    g = 0;
    b = 0;
  }
  // display or remove warning symbol if above/below allowed threshold
  set_coolant(g == 0);

  // Write value on the screen
  char str[5]; 
  sprintf(str, "%d'C\n", coolant);
  write_word(str,cool_start,20,r,g,b,24);
}

// Update the current value of the voltage on the display
void update_volts(int level){
  clear_area(volt_start,60,SOURCE-volt_start,24);

  // Ensure the value is with allowed range
  if (level < 0 | level > 999) level = 0;

  // Extract fraction from the data
  int volts = level/10;
  int point = level%10;

  // Write value on the screen
  char str[6];
  sprintf(str, "%d.%dV\n", volts, point);
  write_word(str,volt_start,60,1,1,1,24);
}

// Update the current value of the speed on the display
void update_speed(int level){

  // Convert the value to mph if required
  if (configuration.speed_units == MPH) {
    float conversion_factor = 0.62137;
    int level = (int) level*conversion_factor;
  }
  
  clear_area(15,20,95,48);

  char str[4];

  // Make sure only 3 digits
  // Dynamically resizes
  if (level > 999 || level < 0) {
    level = 999;
    sprintf(str, "%03d\n", level);
  }
  else if (level > 99) {
    sprintf(str, "%03d\n", level);
  }
  else if (level > 9) {
    sprintf(str, "%02d\n", level);
  }
  else {
    sprintf(str, "%01d\n", level);
  }

  // Write value on the screen
  write_word(str,15,20,1,1,1,48);
}

// Update the current value of the rpm on the display
void update_rpm(int level){
  clear_area(15,160,165,48);
  
  // Make sure rpm value is less than the configured maximum
  if (level > configuration.max_rpm || level < 0) {
    level = configuration.max_rpm;
  }

  // Set RPM LEDs
  float percent = (1.0*level) / configuration.max_rpm;
  int num_leds = percent * NUM_LEDS;
  set_leds(num_leds);

  // Write value on the screen
  char str[6];
  sprintf(str, "%5d\n", level);
  write_word(str,15,160,1,1,1,48);
}

// Update the current value of the gear on the display
void update_gear(int level){
  clear_area(112,20,67,96);

  // Make sure only 1 digit
  if (level > 9 || level < 0) level = 0;

  // Write value on the screen
  char str[2];
  sprintf(str, "%1d\n", level);
  write_word(str,112,20,1,1,1,96);
}

// Set or unset the coolant warning image
void set_coolant(int state){
  if (state) display_ppm_image(230,100,48,48,coolant_image);
  else clear_area(230,100,48,48);
}

