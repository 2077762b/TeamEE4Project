#include "Display_driver.h"

static int countup = 0;

void Write_Command(char cmd){
    DC_PORT->PIO_CODR = DC;      // DC = 0 (command)
    BUS_PORT->PIO_CODR = 0xff << BUS_SHIFT;
    BUS_PORT->PIO_SODR = cmd << BUS_SHIFT;
    WR_PORT->PIO_CODR = WR;      // WR = 0 (write)
    WR_PORT->PIO_SODR = WR;      // WR = 1 
}

void Write_Parameter(char data){
    DC_PORT->PIO_SODR = DC;     // DC = 1 (data)
    BUS_PORT->PIO_CODR = 0xff << BUS_SHIFT;
    BUS_PORT->PIO_SODR = data << BUS_SHIFT;
    WR_PORT->PIO_CODR = WR;     // WR = 0 (write)
    WR_PORT->PIO_SODR = WR;     // WR = 1 
}

void toggle(){
    if (countup%2) {
      WR_PORT->PIO_SODR = WR;
      RD_PORT->PIO_SODR = RD; 
      DC_PORT->PIO_SODR = DC;
      RESET_PORT->PIO_SODR = RESET;
      BUS_PORT->PIO_SODR = 0xff << BUS_SHIFT;
    }
    else {
      WR_PORT->PIO_CODR = WR;
      RD_PORT->PIO_CODR = RD; 
      DC_PORT->PIO_CODR = DC; 
      RESET_PORT->PIO_CODR = RESET;
      BUS_PORT->PIO_CODR = 0xff << BUS_SHIFT;
    }
    countup++;
}

void init_LCD() 
{
    PMC->PMC_PCER0=7<11; //Enable Peripheral Clock

    //Enable PIO
    PIOA->PIO_PER=0x20020000;
    PIOB->PIO_PER=0x00204000;
    PIOC->PIO_PER=0x200FF010;

    //Declare
    PIOA->PIO_OER=0x20020000;
    PIOB->PIO_OER=0x00204000;
    PIOC->PIO_OER=0x200FF010;

    WR_PORT->PIO_SODR = WR;           // WR = 1 
    RD_PORT->PIO_SODR = RD;           // RD = 1 
    
    RESET_PORT->PIO_SODR = RESET;     // RESET = 1 
    delay(10);
    RESET_PORT->PIO_CODR = RESET;     // RESET = 0 
    delay(50);
    RESET_PORT->PIO_SODR = RESET;     // RESET = 1 
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
        Write_Parameter((char)SOURCE-1);
        Write_Parameter((GATE-1)>>8);
        Write_Parameter((char)GATE-1);
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
        Write_Parameter((char)SOURCE-1);
    Write_Command(0x2b);
        Write_Parameter(0x00);
        Write_Parameter(0x00);
        Write_Parameter((GATE-1)>>8);
        Write_Parameter((char)GATE-1);
    Write_Command(0x29);
    delay(10);

    // Clear Screen
    Write_Command(0x2C);
    for(int i=0; i<76800; i++){
        Write_Parameter(0x00);
        Write_Parameter(0x00);
        Write_Parameter(0x00);
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
    char y;
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

int write_word(const char * w, int x, int y, int r, int g, int b, int font){

  Font * current_font;
  if (font == 48) current_font = font_48;
  else if (font == 96) current_font = font_96;
  else {
    current_font = font_24;
    font = 24;
  }
  
  double width;
  int chars = strlen(w);
  for (int i=0; i < chars; i++){
    width = ceil((double)current_font[*w].width/8)*8;
    write_char(x,y,width,font,current_font[*w].data,r,g,b);
    x = x + current_font[*w].width + 2;
    w++;
  }
  return x+5;
}
