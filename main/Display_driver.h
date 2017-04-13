#ifndef DISPLAY_DRIVER_H_  
#define DISPLAY_DRIVER_H_

#include "Fonts.h"
#include <Arduino.h>

// PC4 (116)
#define DC            0x00000010 
#define DC_PORT       PIOC 

// PA29 (112)
#define WR            0x20000000 
#define WR_PORT       PIOA

// PB21 (92)
#define RD            0x00200000 
#define RD_PORT       PIOB

// PC12-PC19 (94-101)
#define BUS_SHIFT     12
#define BUS_PORT      PIOC

// PB14 (140)
#define RESET         0x00004000 
#define RESET_PORT    PIOB
   
#define LEFT_BUTTON   0x00000800 //                 
#define RIGHT_BUTTON  0x00001000 // 

// 94 to 101 (PC12 - PC19)   
// Port C, pins 11 (left) and 12 (right) for buttons
// Port C, pins 13 (CI), 14 (DI) for LEDs

const unsigned int SOURCE = 320;
const unsigned int GATE = 240;

void Write_Parameter(char data);
void Write_Command(char cmd);
void init_LCD();
void write_char(int start_x, int start_y, int width, int height, const unsigned char * bit_array, int red, int green, int blue);
void display_ppm_image(int start_x, int start_y, int width, int height, const unsigned char * bit_array);
void clear_area(int start_x, int start_y, int width, int height);
int write_word(const char * w, int x, int y, int r, int g, int b, int font);

void toggle();

#endif
