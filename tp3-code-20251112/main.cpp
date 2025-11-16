#include "chargesauve.h"
#include "Outils.h"
#include "image.h"
#include "structurant.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
using namespace std;

int main() {
  bool ok;

  // --- Création du structurant ---
  t_structurant structo;
  structo.h = 9;
  structo.w = 9;
  structo.centre = 4.0; // juste indicatif ici

  // structurant en forme de croix
  for (int i = 0; i < structo.h; i++) {
      for (int j = 0; j < structo.w; j++) {
          if (i == structo.h / 2 || j == structo.w / 2)
              structo.im[i][j] = 1;
          else
              structo.im[i][j] = 0;
      }
  }

  // --- Chargement de l'image ---
  t_Image *Image3 = new t_Image;
  loadPgm("lena512x512.pgm", Image3, ok);
  if (!ok) {
      cout << "Erreur lors du chargement de l'image." << endl;
      return 1;
  }

  // --- Dilatation ---
  erosion(&structo, Image3);

  // --- Sauvegarde ---
  savePgm("resudiff.pgm", Image3);

  delete Image3;
  return 0;
}