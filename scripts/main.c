#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include "boutons.h"
#include "cartes.h"
#include "menus.h"

/*ce qui donne les ordres et structure le programme*/
int main(void){
  int hauteur=1080, largeur=1920, margeX=20, margeY=20, tCarteX=132, tCarteY=132, nbLignes, nbColones, cacheTrouve=1;
  int configuration, nbCartesTotal=0;
  cartePaquet bibliothequesCartes[3] = {{100,2},{100,0},{100,0}};
  cartePaquet* paquetTotal = fabriqueCarte(bibliothequesCartes, 3, &nbCartesTotal);
  cartePaquet* paquetJeuTrie = NULL;
  carteTable* cartesJeu = NULL;
  bouton* boutonsMenu[9];
  bouton* boutonsParametre[10];
  InitialiserGraphique();
  CreerFenetre(0,0,largeur,hauteur);
  ChargerImage("../pack_de_texture/fonds/acceuil.jpg",0,0,0,0,1920,800);
  boutonsMenu[0] = sauverBouton("../pack_de_texture/boutons/grille1_1.png",240,360,600,180);
  boutonsMenu[1] = sauverBouton("../pack_de_texture/boutons/grille2_1.png",1080,360,600,180);
  boutonsMenu[2] = sauverBouton("../pack_de_texture/boutons/grille3_1.png",240,720,600,180);
  boutonsMenu[3] = sauverBouton("../pack_de_texture/boutons/grille4_1.png",1080,720,600,180);
  boutonsMenu[4] = sauverBouton("../pack_de_texture/boutons/reccord_1.png",300,540,480,60);
  boutonsMenu[5] = sauverBouton("../pack_de_texture/boutons/reccord_1.png",1140,540,480,60);
  boutonsMenu[6] = sauverBouton("../pack_de_texture/boutons/reccord_1.png",300,900,480,60);
  boutonsMenu[7] = sauverBouton("../pack_de_texture/boutons/reccord_1.png",1140,900,480,60);
  boutonsMenu[8] = sauverBouton("../pack_de_texture/boutons/parametre_1.png",1720,60,120,120);

  boutonsParametre[0] = sauverBouton("../pack_de_texture/boutons/boutonrouge_1.png",100,300,100,100);
  boutonsParametre[1] = sauverBouton("../pack_de_texture/boutons/boutonrouge_1.png",100,500,100,100);
  boutonsParametre[2] = sauverBouton("../pack_de_texture/boutons/boutonrouge_1.png",100,700,100,100);
  boutonsParametre[3] = sauverBouton("../pack_de_texture/boutons/boutonrouge_1.png",100,900,100,100);
  boutonsParametre[4] = sauverBouton("../pack_de_texture/boutons/boutonjaune_1.png",1720,60,100,100);
  boutonsParametre[5] = sauverBouton("../pack_de_texture/boutons/plus_1.png",1500,400,75,75);
  boutonsParametre[6] = sauverBouton("../pack_de_texture/boutons/moins_1.png",1500,500,75,75);
  boutonsParametre[7] = sauverBouton("../pack_de_texture/boutons/true_1.png",400,300,100,52);
  boutonsParametre[8] = sauverBouton("../pack_de_texture/boutons/false_1.png",400,300,100,52);
  boutonsParametre[9] = sauverBouton("../pack_de_texture/boutons/boutonbleu_1.png",1400,437,100,100);
  configuration = menu(boutonsMenu,boutonsParametre);
  if (configuration==1){
    nbLignes = 3;
    nbColones = 4;
  }
  if (configuration==2){
    nbLignes = 4;
    nbColones = 7;
  }
  if (configuration==3){
    nbLignes = 6;
    nbColones = 11;
  }
  paquetJeuTrie = choixCarte( nbColones*nbLignes/2, paquetTotal, nbCartesTotal);
  cartesJeu = melangeCarte(paquetJeuTrie, largeur/2, hauteur/2, margeX, margeY, nbColones, nbLignes, tCarteX, tCarteY);
  jeu(cartesJeu, nbColones, nbLignes, tCarteX, tCarteY, margeX, margeY, largeur, hauteur,"../pack_de_texture/cartes/fonds/01.png", "../pack_de_texture/fonds/01.jpg", cacheTrouve);
  printf("Jeu\n");

  free(paquetJeuTrie);
  free(cartesJeu);
  free(paquetTotal);
  return EXIT_SUCCESS;
}
