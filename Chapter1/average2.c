#include<stdio.h>
#include"pgmlib.h"

void average(int n1, int n2);

int main(void)
{
  int i;
  char *list[] = {"../mono/LENNA.pgm", "../mono/BARBARA.pgm", "../mono/girl.pgm"};
  int length = sizeof list /sizeof list[0];
  for(i=0; i<length; i++) {
    printf("%s\n", list[i]);
    load_image(0, list[i]);
    average(0, 1);
  }
  save_image(1, "../trans_mono/average2.pgm");
  return 0;
}

void average(int n1, int n2)
{
  int x, y;
  width[n2] = width[n1];
  height[n2] = height[n1];
  for(y=0; y<height[n1]; y++) {
    for(x=0; x<width[n1]; x++) {
      image[n2][x][y] += image[n1][x][y]/3;
    }
  }
}