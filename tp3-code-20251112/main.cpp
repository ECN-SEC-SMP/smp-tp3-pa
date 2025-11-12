#include "chargesauve.h"
#include "image.h"


int main(){
  int s = 125;
  t_Image * Image1 = new t_Image;
  t_Image * Image2 = new t_Image;
  t_Image * Image3 = new t_Image;
  bool ok;
  loadPgm("kodie512x512.pgm", Image1, ok);
  loadPgm("lena512x512.pgm", Image2, ok);
  diff(Image1, Image2, Image3);
  savePgm("resudiff.pgm", Image3);
  delete Image1, Image2, Image3;
  return 0;
}