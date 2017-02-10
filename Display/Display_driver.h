#ifndef DISPLAY_DRIVER_H_  
#define DISPLAY_DRIVER_H_

#define DC    0x02000000 // Port C, pin 25, Arduino Due pin 5
#define WR    0x01000000 // Port C, pin 24, Arduino Due pin 6
#define RD    0x00800000 // Port C, pin 23, Arduino Due pin 7
#define RESET 0x00400000 // Port C, pin 22, Arduino Due pin 8
// Port C, pins 1 to 8, Arduino Due pins 33 to 40 

#define OIL_THRESHOLD 80
#define FUEL_THRESHOLD 20
#define COOL_THRESHOLD 50

const unsigned int SOURCE = 320;
const unsigned int GATE = 240;

void Write_Parameter(char data);
void Write_Command(char cmd);
void init_LCD();
void write_char(int start_x, int start_y, int width, int height, const unsigned char * bit_array, int red, int green, int blue );
void display_ppm_image(int start_x, int start_y, int width, int height, const unsigned char * bit_array );
void clear_area(int start_x, int start_y, int width, int height);
int write_word(const char * w, int x, int y, int r, int g, int b);

#endif
