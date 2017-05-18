#include "config.h"

void setup_config() {
  delay(500);

  // Check to see if this is the first time the program has run
  uint8_t first_run = dueFlashStorage.read(0); 
  if (first_run) {
    // Use default configuration values
    configuration.cool_threshold = COOL_THRESHOLD;
    configuration.speed_units = MPH;
    configuration.max_num_pages = MAX_NUM_PAGES;
    configuration.num_can_ids = NUM_CAN_IDS;
    configuration.can_ids_per_page = CAN_IDS_PER_PAGE;
    configuration.max_rpm = MAX_RPM;
    int temp[CAN_IDS_PER_PAGE][MAX_NUM_PAGES] = CAN_IDS; // Default CAN IDs
    memcpy(configuration.can_pages, temp, sizeof(temp));

    // Write default values to flash
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

// Update the configuration settings
void update_config(){
  // Start serial usb connection
  SerialUSB.begin(9600);
  while (!SerialUSB);

  // Display current configuration values
  SerialUSB.println("Current Configuration");
  SerialUSB.println("*********************");
  SerialUSB.print("Coolant Threshold:   ");
  SerialUSB.println(configuration.cool_threshold);
  SerialUSB.print("Speed Units: ");
  if (configuration.speed_units == MPH) SerialUSB.print("MPH");
  else SerialUSB.print("KPH");
  SerialUSB.print("\n");
  SerialUSB.print("Max RPM (for LEDs):  ");
  SerialUSB.println(configuration.max_rpm);
  SerialUSB.println("CAN IDs:");
  int page_index = 0;
  int page_location_index = 0;
  int number_checked = 0;
  while (number_checked < configuration.num_can_ids){
    SerialUSB.print("0x");
    SerialUSB.print(configuration.can_pages[page_index][page_location_index],HEX);
    SerialUSB.print("    ");
    number_checked++;
    page_location_index++;
    if (page_location_index==6 && number_checked < configuration.num_can_ids) {
      page_index++;
      page_location_index = 0;
    }
  }
  SerialUSB.print("\n\n");
  
  // Update coolant Threshold
  SerialUSB.println("Please enter coolant threshold value");
  while (SerialUSB.available() == 0);
  configuration.cool_threshold = SerialUSB.parseInt();
  while (SerialUSB.available() > 0) SerialUSB.read();
  SerialUSB.println(configuration.cool_threshold);

  // Update speed unit
  SerialUSB.println("Please select 1(MPH) or 0(KPH)");
  while (SerialUSB.available() == 0);
  configuration.speed_units = SerialUSB.parseInt();
  while (SerialUSB.available() > 0) SerialUSB.read();
  SerialUSB.println(configuration.speed_units);

  // Update CAN IDs shown in diagnostics mode
  SerialUSB.println("Enter CAN IDs in decimal form (enter -1 to exit)");
  int count = 0, temp;
  int temp_array[MAX_CAN_ARRAY_SIZE];
  while (1){
    while (SerialUSB.available() == 0);   
    temp = SerialUSB.parseInt();
    if (temp == -1) break;
    SerialUSB.println(temp);
    temp_array[count] = temp;
    count++;
    if (count == MAX_CAN_ARRAY_SIZE) break;    
  }
    memcpy(configuration.can_pages, temp_array, sizeof(temp_array));
  configuration.num_can_ids = count;

  // Write update values to flash memory
  uint8_t b[sizeof(Configuration)]; 
  memcpy(b, &configuration, sizeof(Configuration)); 
  dueFlashStorage.write(CONFIG_ADDR, b, sizeof(Configuration));

  SerialUSB.print("\nConfiguration successfully updated.\n\n\n");
}
