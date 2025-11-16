#include "chargesauve.h"
#include "image.h"
#include "structurant.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
using namespace std;


void dilatation(t_structurant *struc, t_Image *Image) {
    if (!Image || Image->h <= 0 || Image->w <= 0) return;

    // Création d'une copie binaire de l'image
    unsigned int **original = new unsigned int*[Image->h];
    for(int i = 0; i < Image->h; i++) {
        original[i] = new unsigned int[Image->w];
        for(int j = 0; j < Image->w; j++) {
            original[i][j] = (Image->im[i][j] >= 128) ? 1 : 0; // binaire
            Image->im[i][j] = original[i][j]; // on met déjà à 0/1
        }
    }

    // Dilatation
    for(int i = 0; i < Image->h; i++) {
        for(int j = 0; j < Image->w; j++) {
            if(original[i][j] == 1) {
                for(int si = 0; si < struc->h; si++) {
                    for(int sj = 0; sj < struc->w; sj++) {
                        if(struc->im[si][sj] != 0) {
                            int ni = i + si - struc->h/2;
                            int nj = j + sj - struc->w/2;
                            if(ni >= 0 && ni < Image->h && nj >= 0 && nj < Image->w) {
                                Image->im[ni][nj] = 1;
                            }
                        }
                    }
                }
            }
        }
    }

    // Conversion finale 0/1 -> 0/255
    for(int i = 0; i < Image->h; i++)
        for(int j = 0; j < Image->w; j++)
            Image->im[i][j] *= 255;

    // Libération mémoire
    for(int i = 0; i < Image->h; i++) delete[] original[i];
    delete[] original;
}

void erosion(t_structurant *struc, t_Image *Image) {
    if (!Image || Image->h <= 0 || Image->w <= 0) return;

    // Créer une copie binaire de l'image
    unsigned int **original = new unsigned int*[Image->h];
    for(int i = 0; i < Image->h; i++) {
        original[i] = new unsigned int[Image->w];
        for(int j = 0; j < Image->w; j++) {
            original[i][j] = (Image->im[i][j] >= 128) ? 1 : 0;
            Image->im[i][j] = 0; // initialisation de l'image de sortie
        }
    }

    // Parcours de tous les pixels
    for(int i = 0; i < Image->h; i++) {
        for(int j = 0; j < Image->w; j++) {

            bool garder = true; // on suppose que le centre restera blanc

            for(int si = 0; si < struc->h; si++) {
                for(int sj = 0; sj < struc->w; sj++) {
                    if(struc->im[si][sj] != 0) {
                        int ni = i + si - struc->h/2;
                        int nj = j + sj - struc->w/2;

                        // Si le structurant dépasse l'image ou chevauche un fond, on supprime
                        if(ni < 0 || ni >= Image->h || nj < 0 || nj >= Image->w || original[ni][nj] == 0) {
                            garder = false;
                            break;
                        }
                    }
                }
                if(!garder) break;
            }

            if(garder) Image->im[i][j] = 1; // conserver le pixel blanc
        }
    }

    // Conversion finale 0/1 -> 0/255
    for(int i = 0; i < Image->h; i++)
        for(int j = 0; j < Image->w; j++)
            Image->im[i][j] *= 255;

    // Libération mémoire
    for(int i = 0; i < Image->h; i++) delete[] original[i];
    delete[] original;
}


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