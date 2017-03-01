#include "config.h"

void setup_config() {
  
  Serial.begin(9600);
  delay(500);

  // Check to see if this is the first time the program has run
  uint8_t first_run = dueFlashStorage.read(0); 
  if (first_run) {
    configuration.cool_threshold = COOL_THRESHOLD;
    configuration.speed_units = MPH;
    int temp[NUM_CAN_IDS] = CAN_IDS;
    memcpy(configuration.can_ids, temp, sizeof(temp));
    configuration.num_can_ids = NUM_CAN_IDS;

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

  Serial.println("Current Configuration");
  Serial.println("*********************");
  Serial.print("Coolant Threshold: ");
  Serial.println(configuration.cool_threshold);
  Serial.print("Speed Units: ");
  if (configuration.speed_units == MPH) Serial.println("MPH");
  else Serial.println("KPH");
  Serial.print("CAN IDs: ");
  for (int i = 0; i<configuration.num_can_ids; i++){
    Serial.print(configuration.can_ids[i],HEX);
    Serial.print(" ");
  }
  Serial.println("");
  Serial.print("Number of CAN IDS: ");
  Serial.println(configuration.num_can_ids);
  Serial.println(" ");
  
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
}

