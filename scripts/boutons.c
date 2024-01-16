#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <string.h>

typedef struct bouton{
  char active[50];
  char desactive[50];
  char etat;
  int minX;
  int minY;
  int maxX;
  int maxY;
}bouton;

void afficheBoutons(bouton** listeBoutons, int nbBoutons){
  int i;
  for (i=0;i<nbBoutons;i++){
    if (listeBoutons[i]->etat=='v'){
      ChargerImage(listeBoutons[i]->active,listeBoutons[i]->minX,listeBoutons[i]->minY, 0, 0, listeBoutons[i]->maxX-listeBoutons[i]->minX, listeBoutons[i]->maxY-listeBoutons[i]->minY);
    }
    else{
      ChargerImage(listeBoutons[i]->desactive,listeBoutons[i]->minX,listeBoutons[i]->minY, 0, 0, listeBoutons[i]->maxX-listeBoutons[i]->minX, listeBoutons[i]->maxY-listeBoutons[i]->minY);
    }
  }
}

int  boutonDynamique(bouton* bouton){
  SourisPosition();
  while ((_X>=bouton->minX)&&(_X<=bouton->maxX)&&(_Y>=bouton->minY)&&(_Y<=bouton->maxY)){
    if (bouton->etat=='f'){
      bouton->etat='v';
      afficheBoutons(&bouton,1);
    }
    if (SourisCliquee()){
      return 1;
    }
    SourisPosition();
  }
  if (bouton->etat=='v'){
    bouton->etat='f';
    afficheBoutons(&bouton,1);
  }
  return 0;
}

bouton* sauverBouton(char* active, int x, int y, int l, int h){
  int caractere;
  char desactive[50];
  bouton* dataBouton = (bouton*) malloc(sizeof(bouton));
  for (caractere=0; active[caractere]!='\0'; caractere++){
    if (active[caractere-1]=='_' && active[caractere]=='1' && active[caractere+1]=='.'){
      desactive[caractere]='2';
    }
    else{
      desactive[caractere]=active[caractere];
    }
  }
  desactive[caractere]='\0';
  strcpy(dataBouton->desactive,desactive);
  strcpy(dataBouton->active,active);
  dataBouton->etat = 'f';
  dataBouton->minX = x;
  dataBouton->minY = y;
  dataBouton->maxX = x+l;
  dataBouton->maxY = y+h;
  return(dataBouton);
}
