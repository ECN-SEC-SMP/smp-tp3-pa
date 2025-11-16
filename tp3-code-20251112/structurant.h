/*********************************************
fichier entete structurant.h
----------------------
Auteurs : Equipe pédagogique ALGPR
Date : 18 novembre 2003
Fichier : image.h
But : définir la structure de données t_Image 
pour représenter une image au format PGM
*********************************************/

#ifndef __secsmp_structurant
#define __secsmp_structurant 
#include "image.h"
//on définit un type matrice d'entiers 
//pour rentrer les niveaux de gris des pixels de l'image 

//on définit la structure de données pour représenter un structurant
struct t_structurant
{
	int w; //largeur de l'image
    int h; //hauteur de l'image
    double centre; // coordonées du centre
	t_MatEnt im; //tableau des niveaux de gris de l'image
};

#endif
