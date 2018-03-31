#include<stdio.h>
#include"pgmlib.h"

void average(int n1, int n2, int n3, int n4);

int main(void)
{
  load_image(0, "../mono/LENNA.pgm");
  load_image(1, "../mono/BARBARA.pgm");
  load_image(2, "../mono/girl.pgm");
  average(0, 1, 2, 3);
  save_image(3, "../trans_mono/average.pgm");
  return 0;
}

void average(int n1, int n2, int n3, int n4)
{
  int x, y;
  width[n4] = width[n1];
  height[n4] = height[n1];
  for(y=0; y<height[n1]; y++) {
    for(x=0; x<width[n1]; x++) {
      image[n4][x][y] = (image[n1][x][y]+ image[n2][x][y] + image[n3][x][y])/3;
          
    }
  }
}