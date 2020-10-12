#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE  1
#define FALSE 0

#define BAD_NUMBER_ARGS 1
#define FSEEK_ERROR 2
#define FREAD_ERROR 3
#define MALLOC_ERROR 4
#define FWRITE_ERROR 5

/**
 * Parses the command line.
 *
 * argc:      the number of items on the command line (and length of the
 *            argv array) including the executable
 * argv:      the array of arguments as strings (char* array)
 * grayscale: the integer value is set to TRUE if grayscale output indicated
 *            outherwise FALSE for threshold output
 *
 * returns the input file pointer (FILE*)
 **/
FILE *parseCommandLine(int argc, char **argv, int *isGrayscale) {
  if (argc > 2) {
    printf("Usage: %s [-g]\n", argv[0]);
    exit(BAD_NUMBER_ARGS);
  }
  
  if (argc == 2 && strcmp(argv[1], "-g") == 0) {
    *isGrayscale = TRUE;
  } else {
    *isGrayscale = FALSE;
  }

  return stdin;
}

unsigned getFileSizeInBytes(FILE* stream) {
  unsigned fileSizeInBytes = 0;
  
  rewind(stream);
  if (fseek(stream, 0L, SEEK_END) != 0) {
    exit(FSEEK_ERROR);
  }
  fileSizeInBytes = ftell(stream);

  return fileSizeInBytes;
}

void getBmpFileAsBytes(unsigned char* ptr, unsigned fileSizeInBytes, FILE* stream) {
  rewind(stream);
  if (fread(ptr, fileSizeInBytes, 1, stream) != 1) {
#ifdef DEBUG
    printf("feof() = %x\n", feof(stream));
    printf("ferror() = %x\n", ferror(stream));
#endif
    exit(FREAD_ERROR);
  }
}

unsigned char getAverageIntensity(unsigned char blue, unsigned char green, unsigned char red) {
  int sum = red + blue + green;
  int average = sum / 3;
  //printf("%d + %d + %d = %d / 3 = %d \n", red, blue, green, sum, average);
  return average;
}

void applyGrayscaleToPixel(unsigned char* pixel) {
  //printf("R: %d, B: %d, G: %d ", pixel[0], pixel[1], pixel[0]);
  unsigned char average = getAverageIntensity(pixel[0], pixel[1], pixel[2]);
  pixel[0] = average;
  pixel[1] = average;
  pixel[2] = average;
  //printf(" A: %d,   R: %d, B: %d, G: %d \n\n", average, pixel[0], pixel[1], pixel[0]);
}

void applyThresholdToPixel(unsigned char* pixel) {
  unsigned char average = getAverageIntensity(pixel[0], pixel[1], pixel[2]);
  //printf("R: %d, B: %d, G: %d ", pixel[0], pixel[1], pixel[0]);
  if(average < 128){
    pixel[0] = 0x00;
    pixel[1] = 0x00;
    pixel[2] = 0x00;
  }
  else{
    pixel[0] = 0xff;
    pixel[1] = 0xff;
    pixel[2] = 0xff;
  }
  //printf(" A: %d,   R: %d, B: %d, G: %d \n\n", average, pixel[0], pixel[1], pixel[0]);

}


void applyFilterToPixel(unsigned char* pixel, int isGrayscale) {
  if(isGrayscale == 1){
    //printf("grayscale\n");
    applyGrayscaleToPixel(pixel);
  }
  else if(isGrayscale == 0){
    applyThresholdToPixel(pixel);
    //printf("Threshold\n");
  }
}


int computePadding(int width){
  int pad = (width*3)%4;
  if(pad==0 || pad==2){
    return pad;
  }
  else if (pad == 1){
    return 3;
  }
  else{
    return 1;
  }
}


void applyFilterToRow(unsigned char* row, int width, int isGrayscale) {
  int i;
  for(i=0; i<width*3; i+=3){
    //printf("i: %d, c: %x ", i, (int)row[i]);
    applyFilterToPixel(row+i, isGrayscale);
  }
}


void applyFilterToPixelArray(unsigned char* pixelArray, int width, int height, int isGrayscale) {
  unsigned char* row;
  int i;
  int length = (width*3) + computePadding(width);
  for(i=0; i<height; ++i){
    row = pixelArray + length*i;
    //printf("%d: %p \n", i, row);
    applyFilterToRow(row, width, isGrayscale);
  }
}

void parseHeaderAndApplyFilter(unsigned char* bmpFileAsBytes, int isGrayscale) {
  int offsetFirstBytePixelArray = (int)bmpFileAsBytes[10];
  int width = *(int*)(bmpFileAsBytes+18);
  int height = *(int*)(bmpFileAsBytes+22);
  unsigned char* pixelArray = bmpFileAsBytes + offsetFirstBytePixelArray;

#ifdef DEBUG
  printf("offsetFirstBytePixelArray = %u\n", offsetFirstBytePixelArray);
  printf("width = %u\n", width);
  printf("height = %u\n", height);
  printf("pixelArray = %p\n", pixelArray);
#endif

  applyFilterToPixelArray(pixelArray, width, height, isGrayscale);
}

int main(int argc, char **argv) {
  int grayscale = FALSE;
  unsigned fileSizeInBytes = 0;
  unsigned char* bmpFileAsBytes = NULL;
  FILE *stream = NULL;
  
  stream = parseCommandLine(argc, argv, &grayscale);
  fileSizeInBytes = getFileSizeInBytes(stream);

#ifdef DEBUG
  printf("fileSizeInBytes = %u\n", fileSizeInBytes);
#endif

  bmpFileAsBytes = (unsigned char *)malloc(fileSizeInBytes);
  if (bmpFileAsBytes == NULL) {
    exit(MALLOC_ERROR);
  }
  getBmpFileAsBytes(bmpFileAsBytes, fileSizeInBytes, stream);

  parseHeaderAndApplyFilter(bmpFileAsBytes, grayscale);

#ifndef DEBUG
  if (fwrite(bmpFileAsBytes, fileSizeInBytes, 1, stdout) != 1) {
    exit(FWRITE_ERROR);
  }
#endif

  free(bmpFileAsBytes);
  return 0;
}
