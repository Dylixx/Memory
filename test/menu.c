#include<stdio.h>
#include<stdlib.h>
#include<graph.h>

void menu(int largeur, int hauteur){
  int ecran=0;
  int sourisX, sourisY;
  InitialiserGraphique();
  CreerFenetre(0,0,largeur,hauteur);
  ChargerImage("test.jpg",100,50,0,0,200,100);
  EcrireTexte(800,373,"Choisissez votre grille",2);
  ChargerImage("test.jpg",300,473,0,0,307,307);
  ChargerImage("test.jpg",807,473,0,0,307,307);
  ChargerImage("test.jpg",1314,473,0,0,307,307);
  while (ecran==0){
    if (SourisCliquee()==1){
      sourisX=_X;
      sourisY=_Y;
      if ((sourisX>=300)&&(sourisX<=607)&&(sourisY>=473)&&(sourisY<=780)){
	printf("Config1\n");
      }
      if ((sourisX>=807)&&(sourisX<=1114)&&(sourisY>=473)&&(sourisY<=780)){
	printf("Config2\n");
      }
      if ((sourisX>=1314)&&(sourisX<=1621)&&(sourisY>=473)&&(sourisY<=780)){
	printf("Config3\n");
      }
    }
  }
  Touche();
  FermerGraphique();
}
void choixCarte(){}
void melangeCarte(){}
void ecranDeJeu(){}

int main(void){
  int hauteur=1080;
  int largeur=1920;
  menu(largeur,hauteur);
  return EXIT_SUCCESS;
}
