#include "config.h"

void setup_config() {
  SerialUSB.begin(9600);
  while(!SerialUSB){
  }
  delay(500);

  // Check to see if this is the first time the program has run
  uint8_t first_run = dueFlashStorage.read(0); 
  if (first_run) {
    configuration.cool_threshold = COOL_THRESHOLD;
    configuration.speed_units = MPH;
    configuration.max_num_pages = MAX_NUM_PAGES;
    configuration.num_can_ids = NUM_CAN_IDS;
    configuration.can_ids_per_page = CAN_IDS_PER_PAGE;
    configuration.max_rpm = MAX_RPM;
    
    int temp[CAN_IDS_PER_PAGE][MAX_NUM_PAGES] = CAN_IDS; // Default CAN IDs
    memcpy(configuration.can_pages, temp, sizeof(temp));

    uint8_t b2[sizeof(Configuration)]; 
    memcpy(b2, &configuration, sizeof(Configuration)); 
    dueFlashStorage.write(CONFIG_ADDR, b2, sizeof(Configuration));
    dueFlashStorage.write(0, 0); 
  }
  // Otherwise retrieve the configuration from flash
  else {
    uint8_t* b = dueFlashStorage.readAddress(CONFIG_ADDR); 
    memcpy(&configuration, b, sizeof(Configuration));
  }
}

void update_config(){

  // Display current configuration values
  SerialUSB.println("Current Configuration");
  SerialUSB.println("*********************");
  SerialUSB.print("Coolant Threshold:   ");
  SerialUSB.println(configuration.cool_threshold);
  SerialUSB.print("Speed Units:         ");
  if (configuration.speed_units == MPH) Serial.println("MPH");
  else SerialUSB.println("KPH");
  SerialUSB.print("Max RPM (for LEDs):  ");
  SerialUSB.println(configuration.cool_threshold);
  SerialUSB.println("CAN IDs:");
  int page_index = 0;
  int page_location_index = 0;
  int number_checked = 0;
  while (number_checked < configuration.num_can_ids){
    SerialUSB.print("0x");
    SerialUSB.print(configuration.can_pages[page_index][page_location_index],HEX);
    SerialUSB.print("\n");
    number_checked++;
    page_location_index++;
    if (page_location_index==6 && number_checked < configuration.num_can_ids) {
      page_index++;
      page_location_index = 0;
    }
  }

  /*
  Serial.println("Please enter coolant threshold value");
  while (Serial.available() == 0);
  configuration.cool_threshold = Serial.parseInt();
  while (Serial.available() > 0) Serial.read();
  
  Serial.println("Please select 1(MPH) or 0(KPH)");
  while (Serial.available() == 0);
  configuration.speed_units = Serial.parseInt();
  while (Serial.available() > 0) Serial.read();
   
  Serial.println("Enter CAN IDs");
  int count = 0, temp;
  int temp_array[32];
  while (Serial.available() == 0);
  while (Serial.available() > 0){
    temp = Serial.parseInt();
    if (temp == 0) break;
    temp_array[count] = temp;
    count++;
    if (count == MAX_CAN_ARRAY_SIZE) break;
  }
  memcpy(configuration.can_ids, temp_array, sizeof(temp_array));
  configuration.num_can_ids = count;

  uint8_t b[sizeof(Configuration)]; 
  memcpy(b, &configuration, sizeof(Configuration)); 
  dueFlashStorage.write(CONFIG_ADDR, b, sizeof(Configuration));
  */
}

