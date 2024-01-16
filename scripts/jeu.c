#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graph.h>
#include "intPlus.h"
#include "cartes.h"

/*affiche le chrono*/
void afficheChrono(long int temps, int x, int y){
  int centieme, sec, min;
  char chrono[13] = "\0";
  min = temps/60000000;
  temps -= min*60000000;
  sec = temps/1000000;
  temps -= sec*1000000;
  centieme = temps/10000;
  if (min<100){
    intToString(min,2,chrono);
    strcat(chrono," : ");
    intToString(sec, 2, chrono);
    strcat(chrono," ' ");
    intToString(centieme, 2, chrono);
  }
  ChargerImage("../pack_de_texture/fond/rouge.png",x-50,y-40,0,0,200,50);
  EcrireTexte(x,y,chrono,2);
}

int retourneToutesCartes(carteTable* cartes,int nbCartes, int verso, int tCarteX, int tCarteY, char* imageAffiche){
  int i;
    for (i=0; i<nbCartes; i++){
      if (verso ==1 && (cartes[i].etat==0)){
	ChargerImage(imageAffiche,cartes[i].x,cartes[i].y,0,0, tCarteX,tCarteY);
      }
      if (verso ==0 && (cartes[i].etat==0 || cartes[i].etat==1)){
	ChargerImage(cartes[i].chemin, cartes[i].x+7, cartes[i].y+7, 0, 0, tCarteX, tCarteY);
      }
    }
  return 0;
}
int retourne2Cartes(carteTable* cartes, int tCarteX, int tCarteY, int numCarte1, int numCarte2,char* imageAffiche){
  ChargerImage(imageAffiche, cartes[numCarte1].x, cartes[numCarte1].y, 0, 0, tCarteX, tCarteY);
    ChargerImage(imageAffiche, cartes[numCarte2].x, cartes[numCarte2].y, 0, 0, tCarteX, tCarteY);
    if (cartes[numCarte1].id != cartes[numCarte2].id){
      cartes[numCarte1].etat=0;
      cartes[numCarte2].etat=0;
    }
    return 0;
}

int supprPaire(carteTable* cartes, int tCarteX, int tCarteY, int numCarte){
  char derriereCarte[50]="../pack_de_texture/provisoire/carte";
  intToString(numCarte,3,derriereCarte);
  strcat(derriereCarte,".png");
  printf("%s\n",derriereCarte);
  ChargerImage(derriereCarte, cartes[numCarte].x, cartes[numCarte].y, 0, 0, tCarteX, tCarteY);
  return 0;
}

/* Cette fonction prends 3 arguments :
DureeParie qui se met à jour lors de l'appel de la fonction
DebutPartie qui correspond à la durée de la partie soustrait à l'instant présent. Et qui est également mis à jour à l'appel de la fonction.
temps qui prend la valeur 1 si on veut que le temps s'écoule et 0 si on veut qu'il soit gelé.
La fonction appel une autre fonction qui affiche le temps*/
void calculTemps(long int* dureePartie, long int* instantDebut, int temps){
  if (temps!=1){
    *instantDebut = Microsecondes() - *dureePartie;
  }
  if (temps==1){
    *dureePartie = Microsecondes() - *instantDebut;
    afficheChrono(*dureePartie,900,50);
  }
}

/*Cette fonction change, si la touche "t" est pressé, l'état de triche du jeu*/
void calculTriche(int* triche,carteTable* cartes, int nbCartes, int tCarteX, int tCarteY, int* temps, char* designCarte){
  if (ToucheEnAttente()==1){
    if (Touche()==116){
      *triche = (*triche+1)%2;
    }
  }
  if (*triche==1){
    retourneToutesCartes(cartes, nbCartes, 0, tCarteX, tCarteY, designCarte);
    if (*temps==1){
      *temps = 0;
    }
  }
  if (*triche==0){
    retourneToutesCartes(cartes, nbCartes, 1, tCarteX, tCarteY, designCarte);
    if (*temps==0){
      *temps = 1;
    }
  }
}

/*Cette fonction renvoie le numéro de la carte situé sous la souris. Si il n'y à pas de carte sous la souris, la fonction renvoie -1
  souris (X, Y) --> coordonée de la souris au clique
  centre (X, Y) --> coordonnée du pixel au centre du plateau de carte
  marge (X, Y) --> tailles respective de l'espace horizontal et verticale entre chaques cartes en pixel
  nbCarte (X, Y) --> nombres de carte par ligne et par colonnes
  tCarte (X, Y) --> tailles respective de la largeur et la hauteur de chaques cartes en pixel
  coin(X,Y) --> coordonnée du coin supérieur droit du plateau de jeu (aussi celle de la première carte)
  diff(X, Y) --> coordonnée de la souris au clic dans le plan du plateau de jeu (le coin est considéré comme 0,0)
  carte(X, Y) --> numéro de ligne et de colonne de la carte la plus proche du clique
  limite(Inf,Sup)(X, Y) --> 4 coordonnées des bords de la carte la plus proche du clique*/
int carteCliquee(int sourisX, int sourisY, int centreX, int centreY, int margeX, int margeY, int nbCarteX, int nbCarteY, int tCarteX, int tCarteY){
  int coinX = centreX-(nbCarteX*(margeX+tCarteX)-margeX)/2;
  int coinY = centreY-(nbCarteY*(margeY+tCarteY)-margeY)/2;
  int diffX = sourisX - coinX;
  int diffY = sourisY - coinY;
  int limiteInfX, limiteInfY, limiteSupX, limiteSupY, carteX, carteY;
  for (carteX=0; (carteX*(tCarteX+margeX)+tCarteX<diffX); carteX++){
    if (carteX>=nbCarteX){
      return -1;
    }
  }
  for (carteY=0; (carteY*(tCarteY+margeY)+tCarteY<diffY); carteY++){
    if (carteY>=nbCarteY){
      return -1;
    }
  }
  limiteInfX = carteX*(tCarteX+margeX);
  limiteInfY = carteY*(tCarteX+margeX);
  limiteSupX = limiteInfX + tCarteX;
  limiteSupY = limiteInfY + tCarteY;
  if ((limiteInfX<diffX)&&(limiteSupX>diffX)&&(limiteInfY<diffY)&&(limiteSupY>diffY)){
    return carteY*nbCarteX+carteX;
  }
  return -1;
}

void mainJeu(carteTable* cartes, int nbColones, int nbLignes, int tCarteX, int tCarteY, int margeX, int margeY, int largeur, int hauteur, char* designCarte, int cacheTrouve){
  int ecran =0, tour=1, cartesTrouve = 0, retournement=0, temps=-1, triche=0;
  int numCarte1=-1, numCarte2=-1, numClic=-1, nbCartes=nbColones*nbLignes, ilatriche=0;
  long int tempsRetourne = 1000000L;
  long int dateRetournement = 0;
  long int instantDebut=0;
  long int dureePartie=0;
  while (ecran==0){
    //on regarde en permanence si il faut retourner des cartes, si le joueur active le mode triche, et le chrono
    calculTemps(&dureePartie, &instantDebut, temps);
    calculTriche(&triche, cartes, nbColones*nbLignes, tCarteX, tCarteY, &temps, designCarte);
    if ((retournement==1)&&(dateRetournement<dureePartie)){
      retournement = retourne2Cartes(cartes, tCarteX, tCarteY, numCarte1, numCarte2,designCarte);
    }
    if ((retournement==2)&&(dateRetournement<dureePartie)){
      supprPaire(cartes, tCarteX, tCarteY, numCarte1);
      retournement=supprPaire(cartes, tCarteX, tCarteY, numCarte2);
    }
    if (SourisCliquee()==1){
      numClic = carteCliquee(_X, _Y, largeur/2, hauteur/2, margeX, margeY, nbColones, nbLignes, tCarteX, tCarteY);
      //on vérifie si le joueur clic sur une carte cliquable
      if (numClic>-1 && cartes[numClic].etat==0){
	//et qu'il ne triche pas
	if (triche==0){
	  temps = 1;
	  //on regarde si il choisis sa 1er
	  if (tour==1){
	    if (retournement==1){
	      retournement = retourne2Cartes(cartes, tCarteX, tCarteY, numCarte1, numCarte2, designCarte);
	    }
	    if (retournement==2){
	      supprPaire(cartes, tCarteX, tCarteY, numCarte1);
              retournement=supprPaire(cartes, tCarteX, tCarteY, numCarte2);
	    }
	    numCarte1 = numClic;
	    cartes[numCarte1].etat=1;
	    ChargerImage(cartes[numCarte1].chemin, cartes[numCarte1].x+7, cartes[numCarte1].y+7, 0, 0, tCarteX, tCarteY);
	    tour=2;
	  }
	  //on regarde si il choisis sa deuxième carte
	  if ((tour==2) && (numClic!=numCarte1)){
	    tour=1;
	    numCarte2 = numClic;
	    cartes[numCarte2].etat=1;
	    ChargerImage(cartes[numCarte2].chemin, cartes[numCarte2].x+7, cartes[numCarte2].y+7, 0, 0, tCarteX, tCarteY);
	    //si il vient de trouver une paire
	    if (cartes[numCarte1].id==cartes[numCarte2].id){
	      cartes[numCarte1].etat = 2;
	      cartes[numCarte2].etat = 2;
	      cartesTrouve +=2;
	      if (cartesTrouve==nbCartes){
		ecran=1;
	      }
	      else{
		retournement = 2;
	        dateRetournement = dureePartie + tempsRetourne;
	      }
	    }
	    //sinon les deux cartes selectionner se retournerons après un certain délais
	    else{
	      retournement = 1;
	      dateRetournement = dureePartie + tempsRetourne;
	    }
	  }
	}
	//le mode de triche est actif
	else{
	  ilatriche=1;
	}
      }
      //le joueur n'as pas cliquer sur une carte
    }
  }
  //fin du jeu : score = dureePartie, cheat? = ilatriche
}
