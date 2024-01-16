#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <graph.h>

//cette structure contient le chemin d’accès d’une image et le nombre de fois où elle se trouve dans le paquet de carte. Attention à la capacité du chemin d’accès
struct cartePaquet {
  char chemin[50];
  int occurence;
};
//cette structure contient le chemin d’accès d’une image, son état actuel (si elle est recto ou verso) et son emplacement sur le terrain (x,y). Attention à la capacité du chemin d’accès
struct carteTable {
char chemin[50];
    int id;
    int etat;
    int x;
    int y;
};

/*Permet de convertir un nombre (int) en chaine de caractère d’une certaine taille (la fonction met des zéros avant le nombre si la taille est plus grande que le nombre). Attention elle ne marche que si la taille de la chaîne est égal ou supérieur à la taille du nombre*/
char* intToString(int nb, int taille){
    char* chaine = (char*) malloc((taille+1)*sizeof(char));
    int i, digit, puissanceDe10=1;
    for(i=1;i<taille;i++,puissanceDe10*=10){
    }
    for (i=0;i<taille;i++, puissanceDe10/=10){
        digit=nb/puissanceDe10;
        nb-=digit*puissanceDe10;
        chaine[i] = (char) digit+48;
    }
    chaine[i]='\0';
    return chaine;
}

//Trouve la taille (en caractère) d’un entier.Attention elle ne marche que pour des nombres positifs
int intLen(int nb){
    int puissanceDe10 = 10;
    int taille;
    for (taille=1; puissanceDe10<=nb;puissanceDe10*=10,taille++){
    }
    return taille;
}

/*génère une liste de cartes. Chaque élément de cette liste comprend le le chiffre 2 (qui correspond au nombre de fois où la carte est présente dans le paquet) et le chemin d’accès vers l’image qui correspond à la carte (ex: carte015.png ). Les cartes sont générées de 0 à certain nombre (spécifié en argument). Il faut également préciser le début du chemin d’accès (ex: “carte”)et l’extension de l’image (ex: “.png”). Attention, la liste ainsi générée vient de la fonction malloc. il faut donc un free après chaque appelle de cette fonction*/
struct cartePaquet* fabriqueCarte(int nbCartes, char* debutChemin, char* extension){
    int numCarte;
    int tailleNbCarte=intLen(nbCartes);
    char* strNumCarte = NULL;
    struct cartePaquet* paquetTotal = (struct cartePaquet*) malloc(nbCartes*sizeof(struct cartePaquet));
    
    for (numCarte=0;numCarte<nbCartes;numCarte++){
        strcpy(paquetTotal[numCarte].chemin,debutChemin);
        strNumCarte = intToString(numCarte,tailleNbCarte);
        strcat(paquetTotal[numCarte].chemin,strNumCarte);
        free(strNumCarte);
        strcat(paquetTotal[numCarte].chemin,extension);
        paquetTotal[numCarte].occurence=2;
    }
    return paquetTotal;
}

/*génère une liste de cartes. Chaque élément de cette liste comprend le le chiffre 2 (qui correspond au nombre de fois où la carte est présente dans le paquet) et le chemin d’accès vers l’image qui correspond à la carte (ex: carte015.png ). Un certain nombre de cartes (spécifié en argument) sont tirées aléatoirement à partir d’une autre liste de cartes (donné en argument). Attention, la liste ainsi générée vient de la fonction malloc. il faut donc un free après chaque appelle de cette fonction*/
struct cartePaquet* choixCarte(int nbCartesDiff, struct cartePaquet* pioche, int nbCartesPioche){
    int i;
    int carteChoisis;
    struct cartePaquet* paquetJeuTrie = (struct cartePaquet*) malloc(nbCartesDiff*sizeof(struct cartePaquet));
    srand(time(NULL));
    for (i=0; i<nbCartesDiff; i++){
        for (carteChoisis = rand()%nbCartesPioche; pioche[carteChoisis].occurence==0; carteChoisis=(carteChoisis+1)%nbCartesPioche){
        }
        strcpy(paquetJeuTrie[i].chemin, pioche[carteChoisis].chemin);
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
struct carteTable* melangeCarte(struct cartePaquet* pioche, int centreX, int centreY, int margeX, int margeY, int nbCarteX, int nbCarteY, int tCarteX, int tCarteY){
  int i, carteChoisis, nbCartesDiff = nbCarteX*nbCarteY/2;
    int coinX = centreX-(nbCarteX*(margeX+tCarteX)-margeX)/2;
    int coinY = centreY-(nbCarteY*(margeY+tCarteY)-margeY)/2;
    struct carteTable* carteJeu = (struct carteTable*) malloc(nbCartesDiff*2*sizeof(struct carteTable));
    srand(time(NULL));
    for (i=0; i<nbCartesDiff*2; i++){
        for (carteChoisis = rand()%nbCartesDiff; pioche[carteChoisis].occurence==0; carteChoisis=(carteChoisis+1)%nbCartesDiff){
        }
        pioche[carteChoisis].occurence--;
        strcpy(carteJeu[i].chemin, pioche[carteChoisis].chemin);
        carteJeu[i].etat = 0;
    carteJeu[i].id = carteChoisis;
        carteJeu[i].x = coinX + (i%nbCarteX)*(margeX+tCarteX);
        carteJeu[i].y = coinY + (i/nbCarteX)*(margeY+tCarteY);
    }
    return carteJeu;
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
/*Ce qui affiche le menu et gère les clics du menu.
Attention: pas terminé (il faut trouver des images pour avoir un beau menu)*/
int menu(int largeur, int hauteur){
  int sourisX, sourisY;
  InitialiserGraphique();
  CreerFenetre(0,0,largeur,hauteur);
  ChargerImage("../pack_de_texture/fond/plateau.png",100,50,0,0,200,100);
  EcrireTexte(800,373,"Choisissez votre grille",2);
  ChargerImage("../pack_de_texture/fond/plateau.png",300,473,0,0,307,307);
  ChargerImage("../pack_de_texture/fond/plateau.png",807,473,0,0,307,307);
  ChargerImage("../pack_de_texture/fond/plateau.png",1314,473,0,0,307,307);
  while (1){
    if (SourisCliquee()==1){
      sourisX=_X;
      sourisY=_Y;
      if ((sourisX>=300)&&(sourisX<=607)&&(sourisY>=473)&&(sourisY<=780)){
    return 1;
      }
      if ((sourisX>=807)&&(sourisX<=1114)&&(sourisY>=473)&&(sourisY<=780)){
    return 2;
      }
      if ((sourisX>=1314)&&(sourisX<=1621)&&(sourisY>=473)&&(sourisY<=780)){
    return 3;
      }
    }
  }
}

/*affiche le chrono*/
void afficheChrono(long int temps, int x, int y){
  int centieme, sec, min;
  char* charCentieme=NULL;
  char* charSec=NULL;
  char* charMin=NULL;
  char chrono[13] = {'T','E','M','P','S',' ','E','C','O','U','L','E','\0'};
  min = temps/60000000;
  temps -= min*60000000;
  sec = temps/1000000;
  temps -= sec*1000000;
  centieme = temps/10000;
  if (min<100){
    charCentieme = intToString(centieme, 2);
    charSec = intToString(sec, 2);
    charMin = intToString(min, 2);
    strcpy(chrono,charMin);
    free(charMin);
    chrono[2]=' ';
    chrono[3]=':';
    chrono[4]=' ';
    chrono[5]='\0';
    strcat(chrono,charSec);
    free(charSec);
    chrono[7]=' ';
    chrono[8]='\'';
    chrono[9]=' ';
    chrono[10]='\0';
    strcat(chrono,charCentieme);
    free(charCentieme);
    chrono[12]='\0';
  }
  ChargerImage("../pack_de_texture/fond/rouge.png",x-50,y-40,0,0,200,50);
  EcrireTexte(x,y,chrono,2);
}

int retourneCartes(struct carteTable* cartes,int nbCartes, int verso, int tCarteX, int tCarteY, int numCarte1, int numCarte2){
  int i;
  if (verso == 2){
    ChargerImage("../pack_de_texture/cartes/carte_retourne.png", cartes[numCarte1].x, cartes[numCarte1].y, 0, 0, tCarteX, tCarteY);
    ChargerImage("../pack_de_texture/cartes/carte_retourne.png", cartes[numCarte2].x, cartes[numCarte2].y, 0, 0, tCarteX, tCarteY);
    cartes[numCarte1].etat=0;
    cartes[numCarte2].etat=0;
    return 0;
  }
  else{
    for (i=0; i<nbCartes; i++){
      if (verso ==1 && (cartes[i].etat==0)){
	ChargerImage("../pack_de_texture/cartes/carte_retourne.png",cartes[i].x,cartes[i].y,0,0, tCarteX,tCarteY);
      }
      if (verso ==0 && (cartes[i].etat==0|| cartes[i].etat==1)){
	ChargerImage(cartes[i].chemin, cartes[i].x+7, cartes[i].y+7, 0, 0, tCarteX, tCarteY);
      }
    }
  }
}

/*Fonction qui gère tout le jeu temps, affichage des carte, clic,...
Idealement, il serait bien de la décomposer
Attention: fonction pas terminé*/
void jeu(struct carteTable* cartes, int nbColones, int nbLignes, int tCarteX, int tCarteY, int margeX, int margeY, int largeur, int hauteur){
  int i, ecran =0, tour=1, cartesTrouve = 0, retournement=0, temps=0, triche=0, numCarte1=-1, numCarte2=-1, numClic=-1, sourisX, sourisY, nbCartes=nbColones*nbLignes;
  long int tempsRetourne = 1000000L;
  long int dateRetournement = 0;
  long int instantDebut=0;
  long int dureePartie=0;
  ChargerImage("../pack_de_texture/fond/plateau.png",0,0,0,0,largeur,hauteur);
  retourneCartes(cartes, nbColones*nbLignes, 1, tCarteX, tCarteY, numCarte1, numCarte2);
  while (ecran==0){
    if (temps==0){
      instantDebut = Microsecondes() - dureePartie;
    }
    if (temps==1){
      dureePartie = Microsecondes() - instantDebut;
      afficheChrono(dureePartie,900,50);
    }
    if (ToucheEnAttente()==1){
      if (Touche()==116){
	triche ++;
      }
    }
    if (triche==1){
      triche = 2;
      temps=0;
      retourneCartes(cartes, nbColones*nbLignes, 0, tCarteX, tCarteY, numCarte1, numCarte2);
      }
    if (triche==3){
      retourneCartes(cartes, nbColones*nbLignes, 1, tCarteX, tCarteY, numCarte1, numCarte2);
      triche=0;
      temps = 1;
    }
    if (triche==0){
      if ((retournement==1)&&(dateRetournement<dureePartie)){
	retournement = retourneCartes(cartes, nbColones*nbLignes, 2, tCarteX, tCarteY, numCarte1, numCarte2);
      }
      if (SourisCliquee()==1){
	sourisX = _X;
	sourisY = _Y;
	numClic = carteCliquee(sourisX, sourisY, largeur/2, hauteur/2, margeX, margeY, nbColones, nbLignes, tCarteX, tCarteY);
	if (numClic>-1){
	  temps = 1;
	  if (tour==1){
	    if (retournement==1){
	      retournement = retourneCartes(cartes, nbColones*nbLignes, 2, tCarteX, tCarteY, numCarte1, numCarte2);
	    }
	    numCarte1 = numClic;
	    cartes[numCarte1].etat=1;
	    ChargerImage(cartes[numCarte1].chemin, cartes[numCarte1].x+7, cartes[numCarte1].y+7, 0, 0, tCarteX, tCarteY);
	    tour=2;
	  }
	  if ((tour==2) && (numClic!=numCarte1)){
	    tour=1;
	    numCarte2 = numClic;
	    cartes[numCarte2].etat=1;
	    ChargerImage(cartes[numCarte2].chemin, cartes[numCarte2].x+7, cartes[numCarte2].y+7, 0, 0, tCarteX, tCarteY);
	    if (cartes[numCarte1].id==cartes[numCarte2].id){
	      cartes[numCarte1].etat = 2;
	      cartes[numCarte2].etat = 2;
	      cartesTrouve +=2;
	      if (cartesTrouve==nbCartes){
		ecran=1;
	      }
	    }
	    else{
	      retournement = 1;
	      dateRetournement = dureePartie + tempsRetourne;
	    }
	  }
	}
	//si -2 : afficher des boutons (recommencer, rejouer, menu)
      }
    }
  }
  //afficher des boutons (recommencer, rejouer, menu)
  Touche();
  FermerGraphique();
}

/*ce qui donne les ordres et structure le programme*/
int main(void){
  int hauteur=1080, largeur=1920, margeX=20, margeY=20, tCarteX=132, tCarteY=132, nbCartes = 35, nbLignes, nbColones;
  int configuration = menu(largeur,hauteur);
  printf("\n");
  char chemin[] = {'.','.','/','p','a','c','k','_','d','e','_','t','e','x','t','u','r','e','/','c','a','r','t','e','s','/','c','a','r','t','e','0','\0'};
  char extension[] = {'.','p','n','g','\0'};
  struct cartePaquet* paquetTotal = fabriqueCarte(nbCartes, chemin, extension);
  struct cartePaquet* paquetJeuTrie = NULL;
  struct carteTable* cartesJeu = NULL;
  if (configuration==1){
    nbLignes = 3;
    nbColones = 4;
  }
  if (configuration==2){
    nbLignes = 6;
    nbColones = 8;
  }
  if (configuration==3){
    nbLignes = 6;
    nbColones = 11;
  }
  paquetJeuTrie = choixCarte( nbColones*nbLignes/2, paquetTotal, nbCartes);
  cartesJeu = melangeCarte(paquetJeuTrie, largeur/2, hauteur/2, margeX, margeY, nbColones, nbLignes, tCarteX, tCarteY);
  free(paquetJeuTrie);
  jeu(cartesJeu, nbColones, nbLignes, tCarteX, tCarteY, margeX, margeY, largeur, hauteur);

  free(cartesJeu);
  free(paquetTotal);
  return EXIT_SUCCESS;
}
