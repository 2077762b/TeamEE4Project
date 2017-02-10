#ifndef FONT24_H_  
#define FONT24_H_

#include "Numbers24.h"
#include "Letters24.h"

typedef struct font {
  const unsigned char * data;
  int width; 
} Font;

Font font_24[122];

#endif
