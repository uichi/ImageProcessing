#include<stdio.h>
#include"pgmlib.h"
long int hist[256];
void make_histogram(int n);
void make_histogram_image(int h, int n);
void revise_image(int n1);
//void revise_histogram_image(int n1, int n2);

int main(void)
{
  load_image(0, "../mono/LENNA.pgm");
  make_histogram(0);
  make_histogram_image(256, 1);
  save_image(1, "../trans_mono/linear1.pgm");
  
  load_image(0, "../trans_mono/linear1.pgm");
  revise_image(0);
  // revise_histogram_image(0);
  save_image(0, "../trans_mono/linear2.pgm");
  return 0;
}

void make_histogram(int n)
{
  int i, x, y;
  for(i=0; i<256; i++) hist[i] = 0;
  for(y=0; y<height[n]; y++)
    for(x=0; x<width[n]; x++)
      hist[image[n][x][y]]++;
}

void make_histogram_image(int h, int n)
{
  int i, x, y;
  long int max;
  int takasa;
  width[n] = 256;
  height[n] = h;
  
  max = 0;
  for(i=0; i<256; i++)
    if(hist[i] > max) max = hist[i]; 
  for(x=0; x<width[n]; x++) {
    takasa = (int)(h / (double)max*hist[x]);
    if(takasa > h) takasa = h;
    for(y=0; y<h; y++)
      if(y < takasa) image[n][x][h-1-y] = 0;
      else image[n][x][h-1-y] = 255;
  }
}

void revise_image(int n1)
{
  int x, y, trans_position;
  int i = 0;
  int histogram[256];
  int min = 255;
  int max = 0;
  //ヒストグラムの最大諧調値と最小諧調値を求める
  for(x=0; x<width[n1]; x++) {
    for(y=0; y<height[n1]; y++) {
      if(image[n1][x][255] == 255)
        break;
      else if(image[n1][x][255-y] == 0)
        i++;
    }
    histogram[x] = i;
    if(min>i)
      min = i;
    else if(max<i)
      max = i;
    printf("%d, ", i);
    i = 0;
  }
  printf("最大諧調値は%dです。", max);
  printf("最小諧調値は%dです。", min);

  for(x=0; x<width[n1]; x++) {
    trans_position = (int)(255 * (histogram[x]-min) / (max-min));
    for(y=0; y<histogram[x]; y++)
      image[n1][x][255-y] = 255;
  }
}

// void revise_histogram_image(int n1, int n2)
// {
// 
// }