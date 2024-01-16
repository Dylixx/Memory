#include<graph.h>
#include<stdio.h>

int main(void)
{
  int hauteur=1080;
  int largeur=1920;
  int jeu = 1;
  InitialiserGraphique();
  CreerFenetre(0,0,largeur,hauteur);
  while (jeu==1)
    if (SourisCliquee()==1){
      ChargerImage("test.jpg",100,50,0,0,200,100);
      EcrireTexte(1000,100,"BIENVENUE !!!",2);
      jeu =2;
    }
  Touche();
  FermerGraphique();
}
