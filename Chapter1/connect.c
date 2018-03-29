#include<stdio.h>
#include"pgmlib.h"

void connect(int n1, int n2, int n3);

int main(void)
{
  load_image(0, "../mono/LENNA.pgm");
  load_image(1, "../mono/BARBARA.pgm");
  connect(0, 1, 2);
  save_image(2, "../trans_mono/lenna_barbara_connect.pgm");
  return 0;
}

void connect(int n1, int n2, int n3)
{
  int x, y;
  height[n3] = height[n1];
  width[n3] = width[n1] + width[n2];
  if(height[n1] != height[n2])
    exit(1);
  else {
    for(y=0; y<height[n3]; y++){
      for(x=0; x<width[n3]; x++) {
        if(x<width[n1])
        image[n3][x][y] = image[n1][x][y];
        else
        image[n3][x][y] = image[n2][x-width[n1]][y];
      }
    }
  }
}