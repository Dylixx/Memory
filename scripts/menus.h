#ifndef menus_H
#define menus_H
#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <string.h>
#include "intPlus.h"
#include "boutons.h"
#include "jeu.h"
#include "cartes.h"
void parametre(bouton**, bouton**, int*, int*, int*);
int menu(bouton**, bouton**);
void pause(int);
void jeu(struct carteTable*, int, int, int, int, int, int, int, int, char*, char*, int);
#endif
