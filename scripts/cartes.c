#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "intPlus.h"

//cette structure contient le chemin d’accès d’une image et le nombre de fois où elle se trouve dans le paquet de carte. Attention à la capacité du chemin d’accès
typedef struct cartePaquet {
  int carte;
  int occurence;
}cartePaquet;
//cette structure contient le chemin d’accès d’une image, son état actuel (si elle est recto ou verso) et son emplacement sur le terrain (x,y). Attention à la capacité du chemin d’accès
typedef struct carteTable {
char chemin[50];
  int id;
  int etat;
  //0 lorsqu'elle est cliquable,  1 lorsqu'elle est joue, 2 lorqu'elle est trouve, 
  int x;
  int y;
}carteTable;

typedef struct dimensions {
  int tCarteX;
  int tCarteY;
  int tFenetreX;
  int tFenetreY;
  int margeX;
  int margeY;
}dimensions;

/*génère une liste de cartes. Chaque élément de cette liste comprend le le chiffre 2 (qui correspond au nombre de fois où la carte est présente dans le paquet) et le chemin d’accès vers l’image qui correspond à la carte (ex: carte015.png ). Les cartes sont générées de 0 à certain nombre (spécifié en argument). Il faut également préciser le début du chemin d’accès (ex: “carte”)et l’extension de l’image (ex: “.png”). Attention, la liste ainsi générée vient de la fonction malloc. il faut donc un free après chaque appelle de cette fonction*/
cartePaquet* fabriqueCarte(cartePaquet* biblis, int nbBiblis, int* p_nbCartes){
  int nbCartes=0;
  int numCarte;
  int numBibli;
  int indiceCarte=0;
  cartePaquet* paquetTotal = NULL;
  for (numBibli=0; numBibli<nbBiblis; numBibli++){
    nbCartes += (biblis[numBibli].carte * biblis[numBibli].occurence)/2;
  }
  paquetTotal = (cartePaquet*) malloc(nbCartes*sizeof(cartePaquet));
  for (numBibli=0; numBibli<nbBiblis; numBibli++){
    if (biblis[numBibli].occurence != 0){
      for (numCarte=0; numCarte<biblis[numBibli].carte; numCarte++){
	paquetTotal[indiceCarte].carte = numBibli*1000+numCarte;
	paquetTotal[indiceCarte].occurence = 2;
	indiceCarte++;
      }
    }
  }
  *p_nbCartes=indiceCarte;
    return paquetTotal;
}

/*génère une liste de cartes. Chaque élément de cette liste comprend le le chiffre 2 (qui correspond au nombre de fois où la carte est présente dans le paquet) et le chemin d’accès vers l’image qui correspond à la carte (ex: carte015.png ). Un certain nombre de cartes (spécifié en argument) sont tirées aléatoirement à partir d’une autre liste de cartes (donné en argument). Attention, la liste ainsi générée vient de la fonction malloc. il faut donc un free après chaque appelle de cette fonction*/
cartePaquet* choixCarte(int nbCartesDiff, cartePaquet* pioche, int nbCartesPioche){
    int i;
    int carteChoisis;
    cartePaquet* paquetJeuTrie = (cartePaquet*) malloc(nbCartesDiff*sizeof(cartePaquet));
    srand(time(NULL));
    for (i=0; i<nbCartesDiff; i++){
        for (carteChoisis = rand()%nbCartesPioche; pioche[carteChoisis].occurence==0; carteChoisis=(carteChoisis+1)%nbCartesPioche){
        }
	paquetJeuTrie[i].carte = pioche[carteChoisis].carte;
        paquetJeuTrie[i].occurence = 2;
        pioche[carteChoisis].occurence = 0;
    }
    return paquetJeuTrie;
}

/*génère une liste de cartes. qui sont les mêmes que la liste spécifié en arguments mais mélanger. Chaque carte contient l’emplacement du fichier de l’image qui correspond à cette carte (ex: "carte 015.png"), l’état dans lequelle se trouve cette carte (recto ou verso), et ses coordonnées sur le plateau (x,y). Pour calculer ces coordonnées, il faut spécifier le centre du plateau de jeu (x,y), la marge en pixel qu’il doit y avoir entre chaque carte (x,y), la composition de la grille de carte (nombre de carte en ligne et en colonne) et la taille des carte en pixel (x,y). Attention, la liste ainsi générée vient de la fonction malloc. il faut donc un free après chaque appelle de cette fonction
centre (X,Y) --> coordonée du pixel au centre du plateau de carte
marge (X,Y) --> tailles respective de l'espace harizontal et verticale entre chaques cartes en pixel
nbCarte (X,Y) --> nombres de carte par ligne et par colonnes
tCarte (X,Y) --> tailles respective de la largeur et la hauteur de chaques cartes en pixel
coin(X,Y) --> coordonée du coin supérieur droit du plateau de jeu (aussi celle de la première carte)*/
carteTable* melangeCarte(cartePaquet* pioche, int centreX, int centreY, int margeX, int margeY, int nbCarteX, int nbCarteY, int tCarteX, int tCarteY){
  int i, carteChoisis, nbCartesDiff = nbCarteX*nbCarteY/2;
    int coinX = centreX-(nbCarteX*(margeX+tCarteX)-margeX)/2;
    int coinY = centreY-(nbCarteY*(margeY+tCarteY)-margeY)/2;
    carteTable* carteJeu = (carteTable*) malloc(nbCartesDiff*2*sizeof(carteTable));
    char chemin[50]="../pack_de_texture/cartes/objets/";
    srand(time(NULL));
    for (i=0; i<nbCartesDiff*2; i++){
        for (carteChoisis = rand()%nbCartesDiff; pioche[carteChoisis].occurence==0; carteChoisis=(carteChoisis+1)%nbCartesDiff){
        }
        pioche[carteChoisis].occurence--;
        carteJeu[i].etat = 0;
        carteJeu[i].id = pioche[carteChoisis].carte;
        carteJeu[i].x = coinX + (i%nbCarteX)*(margeX+tCarteX);
        carteJeu[i].y = coinY + (i/nbCarteX)*(margeY+tCarteY);
	strcpy(carteJeu[i].chemin, chemin);
	intToString(carteJeu[i].id,5,carteJeu[i].chemin);
	strcat(carteJeu[i].chemin,"00.png");	
    }
    return carteJeu;
}

