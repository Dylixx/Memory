#ifndef boutons_H
#define boutons_H
#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <string.h>
typedef struct bouton{
  char active[50];
  char derriere[50];
  char etat;
  int minX;
  int minY;
  int maxX;
  int maxY;
}bouton;
void afficheBoutons(bouton**, int);
int boutonDynamique(bouton* bouton);
bouton* sauverBouton(char*, int, int, int, int);
#endif
