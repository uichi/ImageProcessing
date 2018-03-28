#include<stdio.h>
#include"pgmlib.h"

void scale_up(int n1, int n2);

int main(void)
{
  load_image(0, "../mono/LENNA.pgm");
  scale_up(0, 1);
  save_image(1, "../trans_mono/lenna_double.pgm");
  return 0;
}

void scale_up(int n1, int n2)
{
  int x, y, i, j;
  width[n2]=2*width[n1]; height[n2]=2*height[n1];
  for(y=0; y<height[n1]; y++) {
    for(x=0; x<width[n1]; x++) {
      for(i=0; i<2; i++) {
        for(j=0; j<2; j++) {
          image[n2][2*x+j][2*y+i] = image[n1][x][y];
        }
      }
    }
  }
}