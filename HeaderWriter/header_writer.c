#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define outfile "coolant.h"

int main(int argc, char *argv[]){

	// Check that an image file name has been supplied
	if (argc < 2){
		printf("ERROR: no file supplied\n");
		exit(1);
	}
	
	// Attempt to open the image file
	char * filename = argv[1];
	FILE * ppmFile;
	ppmFile = fopen(filename,"rb");
	if (!ppmFile){
		printf("ERROR: %s does not exist\n", filename);
		exit(1);
	}
	
	// Check that the image file has a PPM header
	char a = fgetc(ppmFile);
	char b = fgetc(ppmFile);
	if (a != 'P' && b != '6'){
		printf("ERROR: %s is not a valid PPM file\n", filename);
		exit(1);
	}
	
	// Check for a comment and ignore it
	unsigned char cmt;
	cmt = fgetc(ppmFile);
	cmt = fgetc(ppmFile);
	if (cmt == '#') {
		while (cmt != 10){
			cmt = fgetc(ppmFile);
		}
	}
	ungetc(cmt, ppmFile);

	// Read in the image width, height and colour value and ensure all are valid 
	int width, height, colorValue;
	fscanf(ppmFile, " %d %d %d ", &width, &height, &colorValue);
	if (colorValue != 255){
		printf("Only 24-bit colour images are supported\n");
		exit(1);
	}

	// Attempt to open a file for writing the COE data
	FILE * headerFile;
	headerFile = fopen(outfile,"w+");
	if (!headerFile){
		printf("ERROR: Output file could not be opened\n");
		exit(1);
	}
	
	// Output the COE file preliminaries
	fprintf(headerFile,"const unsigned int width = %d;\n", width);
	fprintf(headerFile,"const unsigned int height = %d;\n\n",height);
	fprintf(headerFile,"const unsigned char image [] = {\n");
	
	// Read in image pixel data and write to COE file in the correct format
	int c, i;
	char * num[3];
	int limit = (width*height) * 3 - 1;	
	// Loops over each pixel in the image
	for (i=0; i< limit;i++){
		// get the 8 bit char value	
		c = fgetc(ppmFile);
		// write the 8 bit char value
		fprintf(headerFile, "0x%02X, ", c);
		if (i%8 == 7) fprintf(headerFile, "\n");		
	}
	c = fgetc(ppmFile);
	fprintf(headerFile, "0x%02X\n};", c);
	
	// Close open files
	fclose(ppmFile);
	fclose(headerFile);
}

	

