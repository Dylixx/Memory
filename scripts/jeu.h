#ifndef jeu_H
#define jeu_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graph.h>
#include "intPlus.h"
#include "cartes.h"
void afficheChrono(long int, int, int);
int retourneToutesCartes(struct carteTable*, int, int, int, int, char*);
int retourne2Cartes(struct carteTable*, int, int, int, int, char*);
int supprPaire(struct carteTable*, int, int, int);
void calculTemps(long int*, long int*, int);
int calculTriche(int*, struct carteTable*, int, int, int, int*, char*);
int carteCliquee(int, int, int, int, int, int, int, int, int, int);
void mainJeu(struct carteTable*, int, int, int, int, int, int, int, int, char*, int);
#endif
