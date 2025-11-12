#include "chargesauve.h"
#include "image.h"


int main(){
    int s = 125;
    t_Image * Image;
    bool ok;
    loadPgm("paysage.pgm", Image, ok);
    seuillage(s, Image);
    savePgm("paysage.pgm", Image);
    return 0;
  }