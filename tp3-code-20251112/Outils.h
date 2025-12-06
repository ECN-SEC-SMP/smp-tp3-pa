#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include "image.h"
#include "structurant.h"
#include "chargesauve.h"


void seuillage(int seuil, t_Image * Image);

void diff(t_Image * Image1, t_Image * Image2, t_Image *Image3);

void dilatation(t_structurant *struc, t_Image *Image);

void erosion(t_structurant *struc, t_Image *Image);
