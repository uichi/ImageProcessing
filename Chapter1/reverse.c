#include<stdio.h>
#include"pgmlib.h"

void reverse(int n);

int main(void)
{
  load_image(0, "../mono/LENNA.pgm");
  reverse(0);
  save_image(0, "../trans_mono/lenna_reverse.pgm");
  return 0;
}

void reverse(int n)
{
  int x, y, harmony;
  for(y=0; y<height[n]; y++) {
    for(x=0; x<width[n]; x++) {
      harmony = image[n][x][y];
      image[n][x][y] = 255-harmony;
    }
  }
}