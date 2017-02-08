#include "Display.h"
#include "Letters24.h"
#include "Numbers24.h"

#define SOURCE 320
#define GATE 240
#define OIL_THRESHOLD 80
#define FUEL_THRESHOLD 20
#define COOL_THRESHOLD 50
 
void Write_Command(char cmd){
    PIOC->PIO_CODR = 0x000001fe | DC; // DC = 0 (command)
    PIOC->PIO_SODR = cmd << 1;
    PIOC->PIO_CODR = WR;     // WR = 0 (write)
    PIOC->PIO_SODR = WR;     // WR = 1 
}

void Write_Parameter(char data){
    PIOC->PIO_SODR = DC;     // DC = 1 (data)
    PIOC->PIO_CODR = 0x000001fe;
    PIOC->PIO_SODR = data << 1;
    PIOC->PIO_CODR = WR;     // WR = 0 (write)
    PIOC->PIO_SODR = WR;     // WR = 1 
}

void setup() {
  PMC->PMC_PCER0=(1<<13); //Enable Peripheral Clock
  PIOC->PIO_PER=0xFFFFFFFF; //Enable PIO
  PIOC->PIO_OER=0xFFFFFFFF; //Declare 
  PIOC->PIO_SODR = WR | RD | RESET;
  init_LCD();
}

// the loop function runs over and over again forever
void loop() {
  write_fuel(67,200,30);
  write_oil(87,200,60);
  for (int i=0;i<120;i++){
    write_cool(i,200,90);
    delay(100);
  }
}

void write_char(int start_x, int start_y, int width, int height, const unsigned char * bit_array, int red, int green, int blue ) {
    // Set Window parameters
    Write_Command(0x2A);
    Write_Parameter(start_x>>8);
    Write_Parameter(start_x);
    Write_Parameter((start_x + width-1)>>8);
    Write_Parameter((start_x + width-1));
    Write_Command(0x2B);
    Write_Parameter(start_y>>8);
    Write_Parameter(start_y);
    Write_Parameter((start_y + height-1)>>8);
    Write_Parameter((start_y + height-1));
    
    // Write character from Hexidecimal
    char y,z;
    Write_Command(0x2C);
    int red_value = 0, green_value = 0, blue_value = 0;
    if (red) red_value = 0xFF;
    if (green) green_value = 0xFF;
    if (blue) blue_value = 0xFF;
    
    for (int i=0; i<((width*height)/8); i++) {
        y = bit_array[i];
        for (int j=0; j<8; j++){
            if (y & 0x80){
                Write_Parameter(red_value);
                Write_Parameter(green_value);
                Write_Parameter(blue_value);
            }
            else {
                Write_Parameter(0x00);
                Write_Parameter(0x00);
                Write_Parameter(0x00);
            }
            y = y << 1; 
        }
    }
}

// Fuel level
void write_fuel(int level, int x, int y){
  
    // Make sure fuel is a proper percentage
    if (level > 100) level = 100;

    // Write word 'Fuel:'
    write_char(x, y, F_24_blocks*8, 24, F_24,1,1,1);
    x = x + F_24_width + 2;
    write_char(x, y, u_24_blocks*8, 24, u_24,1,1,1);
    x = x + u_24_width + 2;
    write_char(x, y, e_24_blocks*8, 24, e_24,1,1,1);
    x = x + e_24_width + 2;
    write_char(x, y, l_24_blocks*8, 24, l_24,1,1,1);
    x = x + l_24_width + 2;
    write_char(x, y, colon_24_blocks*8, 24, colon_24,1,1,1);
    x = x + colon_24_width + 10;

    int r = 0,g = 1;
    if (level < FUEL_THRESHOLD) {
      r = 1;
      g = 0;
    }
    clear_area(x,y,SOURCE-x,24);
    
    if (level >= 100) {
         write_char(x, y, 16, 24, numbers_24[(level/100)%10],r,g,0);
         if ((level/100)%10 == 1) x = x + 10;
         else x = x + 14;
    }
    if (level >= 10) {
         write_char(x, y, 16, 24, numbers_24[(level/10)%10],r,g,0);
         if ((level/10)%10 == 1) x = x + 10;
         else x = x + 14;
    }
    write_char(x, y, 16, 24, numbers_24[level%10],r,g,0);
    if (level%10 == 1) x = x + 10;
    else x = x + 14;
       
    write_char(x, y, percent_24_blocks*8, 24, percent_24,r,g,0);    
}

// Oil level
void write_oil(int level, int x, int y){

    // Make sure fuel is a proper percentage
    if (level > 999) level = 999;

    // Write word 'Oil:'
    write_char(x, y, O_24_blocks*8, 24, O_24,1,1,1);
    x = x + O_24_width + 2;
    write_char(x, y, i_24_blocks*8, 24, i_24,1,1,1);
    x = x + i_24_width + 2;
    write_char(x, y, l_24_blocks*8, 24, l_24,1,1,1);
    x = x + l_24_width + 2;
    write_char(x, y, colon_24_blocks*8, 24, colon_24,1,1,1);
    x = x + colon_24_width + 10;

    int r = 0,g = 1;
    if (level > OIL_THRESHOLD) {
      r = 1;
      g = 0;
    }
    clear_area(x,y,SOURCE-x,24);
    
    if (level >= 100) {
         write_char(x, y, 16, 24, numbers_24[(level/100)%10],r,g,0);
         if ((level/100)%10 == 1) x = x + 10;
         else x = x + 14;
    }
    if (level >= 10) {
         write_char(x, y, 16, 24, numbers_24[(level/10)%10],r,g,0);
         if ((level/10)%10 == 1) x = x + 10;
         else x = x + 14;
    }
    write_char(x, y, 16, 24, numbers_24[level%10],r,g,0);
    if (level%10 == 1) x = x + 10;
    else x = x + 14;

    write_char(x, y, degree_24_blocks*8, 24, degree_24,r,g,0);
    x = x + 8;
    write_char(x, y, C_24_blocks*8, 24, C_24,r,g,0);
}

// Oil level
void write_cool(int level, int x, int y){

    // Make sure fuel is a proper percentage
    if (level > 999) level = 999;

    // Write word 'Cool:'
    write_char(x, y, C_24_blocks*8, 24, C_24,1,1,1);
    x = x + C_24_width + 2;
    write_char(x, y, o_24_blocks*8, 24, o_24,1,1,1);
    x = x + o_24_width + 2;
    write_char(x, y, o_24_blocks*8, 24, o_24,1,1,1);
    x = x + o_24_width + 2;
    write_char(x, y, l_24_blocks*8, 24, l_24,1,1,1);
    x = x + l_24_width + 2;
    write_char(x, y, colon_24_blocks*8, 24, colon_24,1,1,1);
    x = x + colon_24_width + 10;

    int r = 0,g = 1;
    if (level > COOL_THRESHOLD) {
      r = 1;
      g = 0;
    }
    clear_area(x,y,SOURCE-x,24);
    
    if (level >= 100) {
         write_char(x, y, 16, 24, numbers_24[(level/100)%10],r,g,0);
         if ((level/100)%10 == 1) x = x + 10;
         else x = x + 14;
    }
    if (level >= 10) {
         write_char(x, y, 16, 24, numbers_24[(level/10)%10],r,g,0);
         if ((level/10)%10 == 1) x = x + 10;
         else x = x + 14;
    }
    write_char(x, y, 16, 24, numbers_24[level%10],r,g,0);
    if (level%10 == 1) x = x + 10;
    else x = x + 14;

    write_char(x, y, degree_24_blocks*8, 24, degree_24,r,g,0);
    x = x + 8;
    write_char(x, y, C_24_blocks*8, 24, C_24,r,g,0);
}

void clear_screen(){
    Write_Command(0x2C);
    for(int i=0; i<76800; i++){
        Write_Parameter(0x00);
        Write_Parameter(0x00);
        Write_Parameter(0x00);
    }
}

void clear_area(int start_x, int start_y, int width, int height) {
    // Set Window parameters
    Write_Command(0x2A);
    Write_Parameter(start_x>>8);
    Write_Parameter(start_x);
    Write_Parameter((start_x + width-1)>>8);
    Write_Parameter((start_x + width-1));
    Write_Command(0x2B);
    Write_Parameter(start_y>>8);
    Write_Parameter(start_y);
    Write_Parameter((start_y + height-1)>>8);
    Write_Parameter((start_y + height-1));
    
    // Write character from Hexidecimal
    char y,z;
    Write_Command(0x2C);
    
    for (int i=0; i<(width*height); i++) {
      Write_Parameter(0x00);
      Write_Parameter(0x00);
      Write_Parameter(0x00);
    }
}

void display_ppm_image(int start_x, int start_y, int width, int height, const unsigned char * bit_array ){
     // Set Window parameters
    Write_Command(0x2A);
    Write_Parameter(start_x>>8);
    Write_Parameter(start_x);
    Write_Parameter((start_x + width-1)>>8);
    Write_Parameter((start_x + width-1));
    Write_Command(0x2B);
    Write_Parameter(start_y>>8);
    Write_Parameter(start_y);
    Write_Parameter((start_y + height-1)>>8);
    Write_Parameter((start_y + height-1));
    
    char c;
    Write_Command(0x2C);
    for (int i=0; i<(width*height*3);) {
        Write_Parameter(bit_array[i++]);
    }
}

//======================================================
void init_LCD() 
{
    PIOC->PIO_SODR = RESET;
    delay(10);
    PIOC->PIO_CODR = RESET;
    delay(50);
    PIOC->PIO_SODR = RESET;
    delay(100);
    Write_Command(0x01);
    delay(10);
    Write_Command(0xe0);
    //START PLL
        Write_Parameter(0x01);
    delay(50);
    Write_Command(0xe0);
    //LOCK PLL
        Write_Parameter(0x03);
    delay(5);
    Write_Command(0xb0);
        Write_Parameter(0x2C);
        Write_Parameter(0x80);
        Write_Parameter((SOURCE-1)>>8);
        Write_Parameter(SOURCE-1);
        Write_Parameter((GATE-1)>>8);
        Write_Parameter(GATE-1);
        Write_Parameter(0x00);
    Write_Command(0xf0);
        Write_Parameter(0x00); //0x03 is 16bit(565 format);0x00 is for 8-bit,pixel data format
    //Set the MN of PLL
    Write_Command(0xe2);
        Write_Parameter(0x1d);
        Write_Parameter(0x02);
        Write_Parameter(0x54);
    Write_Command(0xe6);
        Write_Parameter(0x01);
        Write_Parameter(0xdd);
        Write_Parameter(0xde);
    //Set front porch and back porch
    Write_Command(0xb4);
        Write_Parameter(0x01);
        Write_Parameter(0x98);
        Write_Parameter(0x00);
        Write_Parameter(0x44);
        Write_Parameter(0x14);
        Write_Parameter(0x00);
        Write_Parameter(0x00);
        Write_Parameter(0x00);
    Write_Command(0xb6);
        Write_Parameter(0x01);
        Write_Parameter(0x06);
        Write_Parameter(0x00);
        Write_Parameter(0x12);
        Write_Parameter(0x04);
        Write_Parameter(0x00);
        Write_Parameter(0x00);
    Write_Command(0x2a);
        Write_Parameter(0x00);
        Write_Parameter(0x00);
        Write_Parameter((SOURCE-1)>>8);
        Write_Parameter(SOURCE-1);
    Write_Command(0x2b);
        Write_Parameter(0x00);
        Write_Parameter(0x00);
        Write_Parameter((GATE-1)>>8);
        Write_Parameter(GATE-1);
    Write_Command(0x29);
    delay(10);
    
    clear_screen();    
    //display_ppm_image(0,0,width,height,image);
}



