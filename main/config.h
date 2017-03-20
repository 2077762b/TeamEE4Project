#ifndef CONFIG_H_  
#define CONFIG_H_

#include <DueFlashStorage.h>
DueFlashStorage dueFlashStorage;

#define COOL_THRESHOLD 80
#define MAX_RPM 13500
#define MPH 1
#define KPH 0
#define CONFIG_ADDR 4
#define CAN_IDS {ID_1,ID_2,ID_3,ID_4,ID_5,ID_6,TEST_ID}
#define MAX_NUM_PAGES 5
#define NUM_CAN_IDS 7
#define CAN_IDS_PER_PAGE 6

typedef struct configuration {
  int cool_threshold;
  int speed_units;
  int max_rpm;
  int can_pages[MAX_NUM_PAGES][CAN_IDS_PER_PAGE];
  int max_num_pages;
  int num_can_ids;
  int can_ids_per_page;
} Configuration;

int current_page;

Configuration configuration;

void setup_config();
void update_config();

#endif
