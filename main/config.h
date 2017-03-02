#ifndef CONFIG_H_  
#define CONFIG_H_

#include <DueFlashStorage.h>
DueFlashStorage dueFlashStorage;

#define COOL_THRESHOLD 80
#define MPH 1
#define KPH 0
#define CONFIG_ADDR 4
#define CAN_IDS {ID_1,ID_2,ID_3,ID_4,ID_5,ID_6}
#define NUM_CAN_IDS 6
#define CAN_IDS_PER_PAGE 6
#define MAX_CAN_PAGES 5

typedef struct configuration {
  int cool_threshold;
  int speed_units; 
  int can_pages[6][MAX_CAN_PAGES];
  int num_pages;
  int num_can_ids;
} Configuration;

int current_page;

Configuration configuration;

void setup_config();
void update_config();

#endif
