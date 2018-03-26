#include<stdio.h>
#include"pgmlib.h"

int main()
{
  load_image(0, "../mono/LENNA.pgm");
  save_image(0, "../trans_mono/lenna_copyimage.pgm");
  return 0;
}