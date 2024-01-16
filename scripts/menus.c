#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <string.h>
#include <math.h>
#include "intPlus.h"
#include "jeu.h"
#include "cartes.h"
#include "boutons.h"

void calculeGrillePerso(int* nbLignes, int* nbColones, int plusOuMoins,bouton* bouton){
  int maxLignes=8, maxColones=12, minLignes=2, minColones=2, colones, lignes, grilleTrouve=0;
  int nbCartes=(*nbLignes)*(*nbColones);
  double rapportIdeal=16/9, bestRapport=99999, rapport=99999;
  char texteCartes[3]="\0";
  while ((nbCartes>minLignes*minColones || plusOuMoins==1) && (nbCartes<maxLignes*maxColones || plusOuMoins==-1) && grilleTrouve==0){
    nbCartes+=(plusOuMoins*2);
    for (lignes=minLignes; lignes<=maxLignes; lignes++){
      colones = nbCartes/lignes;
      if (((double) nbCartes/lignes == colones) && (colones<=maxColones) && (colones>=minColones)){
	rapport = (double) (colones)/(lignes);
	if (fabs(rapport-rapportIdeal)<fabs(bestRapport-rapportIdeal)){
	  bestRapport=rapport;
	  *nbLignes=lignes;
	  *nbColones=colones;
	  grilleTrouve=1;
	}
      }
    }
  }
  intToString((*nbLignes)*(*nbColones)/2,2,texteCartes);
  afficheBoutons(&bouton,1);
  EcrireTexte(bouton->minX+30,bouton->minY+50,texteCartes,2);
}

void parametre(bouton** boutonsMenu, bouton** boutonsParametre, int* nbLignes, int* nbColones, int* cacheTrouve){
  int ecran=1, page=0;
  ChargerImage("../pack_de_texture/fonds/parametre.jpg",0,0,0,0,1920,1080);
  afficheBoutons(boutonsParametre,10);
  ChargerImage("../pack_de_texture/boutons/boutonvert_1.png",boutonsParametre[0]->minX,boutonsParametre[0]->minY,0,0,boutonsParametre[0]->maxX-boutonsParametre[0]->minX,boutonsParametre[0]->maxY-boutonsParametre[0]->minY);
  boutonsParametre[0]->etat='v';
  while(ecran==1){
    SourisCliquee();//Remet SourisCliquee à 0 si le joueur clic en dehors des boutons
    if (boutonDynamique(boutonsParametre[4])){
      menu(boutonsMenu, boutonsParametre);
    }
    if (page==0){
      if (*cacheTrouve==1){
	if(boutonDynamique(boutonsParametre[7])){
	  *cacheTrouve=0;
	  afficheBoutons(&boutonsParametre[8],1);
	}
      }
      else{
	if(boutonDynamique(boutonsParametre[8])){
	  *cacheTrouve=1;
	  afficheBoutons(&boutonsParametre[7],1);
	}
      }
      if(boutonDynamique(boutonsParametre[5])){
	calculeGrillePerso(nbLignes, nbColones, 1, boutonsParametre[9]);
      }
      if(boutonDynamique(boutonsParametre[6])){
	calculeGrillePerso(nbLignes, nbColones, -1, boutonsParametre[9]);
      }
    }
    else{
      if (boutonDynamique(boutonsParametre[0])){
	ChargerImage("../pack_de_texture/boutons/boutonvert_1.png",boutonsParametre[0]->minX,boutonsParametre[0]->minY,0,0,boutonsParametre[0]->maxX-boutonsParametre[0]->minX,boutonsParametre[0]->maxY-boutonsParametre[0]->minY);
	page=0;
      }
    }
    if (page==1){
    }
    else{
      if (boutonDynamique(boutonsParametre[1])){
	page=1;
	ChargerImage("../pack_de_texture/boutons/boutonvert_1.png",boutonsParametre[1]->minX,boutonsParametre[1]->minY,0,0,boutonsParametre[1]->maxX-boutonsParametre[1]->minX,boutonsParametre[1]->maxY-boutonsParametre[1]->minY);
      }
    }
    if (page==2){
    }
    else{
      if (boutonDynamique(boutonsParametre[2])){
	page=2;
	ChargerImage("../pack_de_texture/boutons/boutonvert_1.png",boutonsParametre[2]->minX,boutonsParametre[2]->minY,0,0,boutonsParametre[2]->maxX-boutonsParametre[2]->minX,boutonsParametre[2]->maxY-boutonsParametre[0]->minY);
      }
    }
    if (page==3){
    }
    else{
      if (boutonDynamique(boutonsParametre[3])){
	page=3;
	ChargerImage("../pack_de_texture/boutons/boutonvert_1.png",boutonsParametre[3]->minX,boutonsParametre[3]->minY,0,0,boutonsParametre[3]->maxX-boutonsParametre[3]->minX,boutonsParametre[3]->maxY-boutonsParametre[0]->minY);
      }
    }
  }
}

/*Ce qui affiche le menu et gère les clics du menu.
Attention: pas terminé (il faut trouver des images pour avoir un beau menu)*/
int menu(bouton** boutonsMenu, bouton** boutonsParametre){
  int nbLignes=4, nbColones=5, cacheTrouve=0;
  ChargerImage("../pack_de_texture/fonds/acceuil.jpg",0,0,0,0,1920,1080);
  afficheBoutons(boutonsMenu,9);
  while (1){
    SourisCliquee();//Remet SourisCliquee à 0 si le joueur clic en dehors des boutons
    if (boutonDynamique(boutonsMenu[0])){
      printf("1\n");
      return 1;
    }
    if (boutonDynamique(boutonsMenu[1])){
      printf("2\n");
      return 2;
    }
    if (boutonDynamique(boutonsMenu[2])){
      printf("3\n");
      return 3;
    }
    if (boutonDynamique(boutonsMenu[3])){
	printf("grille4\n");
    }
    if (boutonDynamique(boutonsMenu[4])){
	printf("score1\n");
    }
    if (boutonDynamique(boutonsMenu[5])){
	printf("score2\n");
    }
    if (boutonDynamique(boutonsMenu[6])){
	printf("score3\n");
    }
    if (boutonDynamique(boutonsMenu[7])){
	printf("score4\n");
    }
    if (boutonDynamique(boutonsMenu[8])){
      parametre(boutonsMenu, boutonsParametre, &nbLignes, &nbColones, &cacheTrouve);
      }
  }
}

void pause(int reprendre){
}

/*Fonction qui gère tout le temps de jeu : temps, affichage des cartes, clic,...
Idéalement, il serait bien de la décomposer
Attention: fonction pas terminé*/
void jeu(carteTable* cartes, int nbColones, int nbLignes, int tCarteX, int tCarteY, int margeX, int margeY, int largeur, int hauteur, char* designCarte, char* designFond, int cacheTrouve){
  int i;
  char derriereCarte[50];
  ChargerImage(designFond,0,0,0,0,largeur,hauteur);
  if (cacheTrouve==1){
    for (i=0; i<nbColones*nbLignes; i++){
      strcpy(derriereCarte,"../pack_de_texture/provisoire/carte");
      intToString(i,3,derriereCarte);
      strcat(derriereCarte,".png");
      SauverImage(derriereCarte, cartes[i].x, cartes[i].y, cartes[i].x+tCarteX, cartes[i].y+tCarteY);
      ChargerImage(designCarte, cartes[i].x, cartes[i].y, 0, 0, tCarteX, tCarteY);
    }
  }
  else{
    retourneToutesCartes(cartes, nbColones*nbLignes, 1, tCarteX, tCarteY, designCarte);
  }
  mainJeu(cartes,nbColones, nbLignes, tCarteX, tCarteY, margeX, margeY, largeur, hauteur, designCarte, cacheTrouve);
}
