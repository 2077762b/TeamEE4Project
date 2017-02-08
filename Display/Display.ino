#include "Display.h"
//#include "formula1.h"
#include "Letters24.h"
#include "Numbers24.h"
       
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

/*
void write_hello_mum(){
    write_char(32, 32, 24, 32, h);
    write_char(56, 32, 24, 32, e);
    write_char(80, 32, 16, 32, l);
    write_char(96, 32, 16, 32, l);
    write_char(112, 32, 24, 32, o);
    write_char(32, 64, 24, 32, m);
    write_char(56, 64, 24, 32, u);
    write_char(80, 64, 24, 32, m);
}
*/
/*
const unsigned char * num_to_name(int num, char height){
  height = (unsigned)height + '0';
  if (num == 0) return "zero_" + height;
  if (num == 1) return "one_" + height;
}
*/
void write_fuel(){
    // Fuel level

    int level = 101;
    int total = 210;
    write_char(total, 30, F_24_blocks*8, 24, F_24,1,1,1);
    total = total + F_24_width + 2;
    write_char(total, 30, u_24_blocks*8, 24, u_24,1,1,1);
    total = total + u_24_width + 2;
    write_char(total, 30, e_24_blocks*8, 24, e_24,1,1,1);
    total = total + e_24_width + 2;
    write_char(total, 30, l_24_blocks*8, 24, l_24,1,1,1);
    total = total + l_24_width + 2;
    write_char(total, 30, colon_24_blocks*8, 24, colon_24,1,1,1);
    total = total + colon_24_width + 2;

    if ( level >= 100) {
         write_char(total, 30, 16, 24, numbers_24[(level/100)%10],0,1,0);
         if ((level/100)%10 == 1) total = total + 8;
         else total = total + 12;
    }
    if ( level >= 10) {
         write_char(total, 30, 16, 24, numbers_24[(level/10)%10],0,1,0);
         if ((level/10)%10 == 1) total = total + 8;
         else total = total + 12;
    }
    write_char(total, 30, 16, 24, numbers_24[level%10],0,1,0);
    if (level%10 == 1) total = total + 8;
    else total = total + 12;
}

void write_levels(){
    // Oil level
    int total = 210;
    write_char(total, 60, O_24_blocks*8, 24, O_24,1,1,1);
    total = total + O_24_width + 2;
    write_char(total, 60, i_24_blocks*8, 24, i_24,1,1,1);
    total = total + i_24_width + 2;
    write_char(total, 60, l_24_blocks*8, 24, l_24,1,1,1);
    total = total + l_24_width + 2;
    write_char(total, 60, colon_24_blocks*8, 24, colon_24,1,1,1);
    total = total + colon_24_width + 2;

    // Collant level
    total = 210;
    write_char(total, 90, C_24_blocks*8, 24, C_24,1,1,1);
    total = total + C_24_width + 2;
    write_char(total, 90, o_24_blocks*8, 24, o_24,1,1,1);
    total = total + o_24_width + 2;
    write_char(total, 90, o_24_blocks*8, 24, o_24,1,1,1);
    total = total + o_24_width + 2;
    write_char(total, 90, l_24_blocks*8, 24, l_24,1,1,1);
    total = total + l_24_width + 2;
    write_char(total, 90, colon_24_blocks*8, 24, colon_24,1,1,1);
    total = total + colon_24_width + 2;
}

void clear_screen(){
    Write_Command(0x2C);
    for(int i=0; i<76800; i++){
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
   unsigned int SOURCE,GATE;
   SOURCE=320;
   GATE=240;

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
    write_levels();
    write_fuel();
    
    //display_ppm_image(0,0,width,height,image);
}



