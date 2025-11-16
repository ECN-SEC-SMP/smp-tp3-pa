#include "chargesauve.h"
#include "image.h"
#include "structurant.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
using namespace std;

void seuillage(int seuil, t_Image * Image){
  if (Image == nullptr || Image->h <= 0 || Image->w <= 0) {
    cout << "Erreur: Image non valide." << endl;
    return;
  }

  for(int i = 0; i < Image->h; i++){
    for(int j = 0; j < Image->w; j++){
      if(Image->im[i][j] > seuil){
        Image->im[i][j] = 255;
      } else {
        Image->im[i][j] = 0;
      }
    }
  }
  cout << "Seuillage terminé." << endl;
}

void diff(t_Image * Image1, t_Image * Image2, t_Image * Image3) {
  if (Image1 == nullptr || Image2 == nullptr || Image3 == nullptr) {
    cout << "Erreur: Une des images est invalide." << endl;
    return;
  }
  Image3->h = Image1->h;
  Image3->w = Image1->w;

  for (int i = 0; i < Image1->h; i++) {
    for (int j = 0; j < Image1->w; j++) {
      int diff = abs((int)Image1->im[i][j] - (int)Image2->im[i][j]);
      Image3->im[i][j] = (unsigned char)diff;
    }
  }
  cout << "Différence calculée avec succès." << endl;
}


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
                            int ni = i + si - (struc->h/2);
                            int nj = j + sj - (struc->w/2);
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
                        int ni = i + si - (struc->h/2);
                        int nj = j + sj - (struc->w/2);

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
