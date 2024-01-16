#ifndef cartes_H
#define cartes_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "intPlus.h"
typedef struct dimensions {
  int tCarteX;
  int tCarteY;
  int tFenetreX;
  int tFenetreY;
  int margeX;
  int margeY;
}dimensions;
typedef struct cartePaquet {
  int carte;
  int occurence;
}cartePaquet;
typedef struct carteTable{
  char chemin[50];
  int id;
  int etat;
  int x;
  int y;
}carteTable;
cartePaquet* fabriqueCarte(cartePaquet*, int, int*);
cartePaquet* choixCarte(int,cartePaquet*,int);
carteTable* melangeCarte(cartePaquet*, int, int, int, int, int, int, int, int);
#endif
