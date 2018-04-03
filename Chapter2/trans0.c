#include<stdio.h>
#include"pgmlib.h"
int trans_table[256];
void trans(int n);

int main(void)
{
  load_image(0, "../mono/LENNA.pgm");
  trans(0);
  save_image(0, "../trans_mono/trans0.pgm");
  return 0;
}

void trans(int n)
{
  int f;
  int x, y;
  
  for(f=0; f<256; f++) {
    trans_table[f] = f;
  }
  for(y=0; y<height[n]; y++)
    for(x=0; x<width[n]; x++)
      image[n][x][y] = trans_table[image[n][x][y]];
}