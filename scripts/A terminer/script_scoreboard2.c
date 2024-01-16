#include <stdio.h>
#include <stdlib.h>

void empty2full(char* chemin_complet){
  int i,o;
  char charvide[10][11];
  long int longvide[10];
  for(i=0;i<10;i++){
    longvide[i]=9999999999999999;
    for(o=0;o<11;o++){
      charvide[i][o]='\0';
    }
  }
  FILE* fichier = fopen(chemin_complet,"w");
  for(i=0;i<10;i++){
    size_t ecriture1 = fwrite(&longvide[i],sizeof(long int),1,fichier);
    size_t recriture2 = fwrite(&charvide[i],sizeof(char),10,fichier);
  }
  fclose(fichier);
}
/*Permet de verifier si le joueur se trouve dans le classement, et si oui où. La positon est ensuite renvoyée*/
int verif(long int temps_chrono,long int* score_fichier,int flag,char* pseudo){
  int i,position,vide=0;
  for(i=0;i<10 && flag!=1 && vide!=1;i++){
    if(temps_chrono < score_fichier[i] || pseudo[i][0]=='\0'){
      flag++;
      position = i;
      printf("%d\n", position);
      }
 }
  return position;
}

void longcpy(long int* arrive,long int* depart){
  int i;
  for(i=0;i<10;i++){
    arrive[i]=depart[i];
  }
}

void charcpy(char* arrive,char* depart){
int i,o;

for(i=0;i<10;i++){
  for(o=0;o<11;o++){
    arrive[i][o]=depart[i][o];
  }
}
}

/*Modifie le tableau de sorte a insérer le nouveau score.*/
void modif_tab(long int* score_fichier,char* pseudo,char* nom_joueur,long int temps_chrono,int position){
  int i,o;
  for(i=9;i>position;i--){
    score_fichier[i]=score_fichier[i-1];
    for(o=0;o<10;o++){
      pseudo[i][o]=pseudo[i-1][o];
      }
  }
  score_fichier[position]=temps_chrono;
for(o=0;o<10;o++){
  pseudo[position][o]=nom_joueur[o];
}
}

void openfile(char* debut_chemin,int taille_grille,long int* score_fichier,char* pseudo){
  debut_chemin = intToString(taille_grille,3,debut_chemin);
FILE* fichier = fopen(debut_chemin,"r");
if(fichier==NULL){
  empty2full(debut_chemin);
  fichier = fopen(debut_chemin,"r");
}
if(fichier != NULL){
  printf("C'est bon\n");
  for(i=0;i<10;i++){
    size_t reussite1 = fread(&score_fichier[i],sizeof(long int),1,fichier);
    size_t reussite3 = fread(&pseudo[i],sizeof(char),10,fichier);
    pseudo[i][10]='\0';
    }
}
fclose(fichier);
}
int classement (char* nom_joueur,long int temps_chrono,char* tab_pseudo,long int* tab_score,int taille_grille){
  int score_fichier[10];
  char pseudo[10][11];
  int position, i, o, flag=0;
  char top10_path[12]={'.','.','/','t','o','p','1','0','_','\0'};

top10_path = intToString(taille_grille,3,top10_path);
openfile(top10_path,taille_grille,score_fichier,pseudo);
position=verif(temps_chrono,score_fichier,flag);
if(flag==1){
  modif_tab(score_fichier,pseudo,nom_joueur,temps_chrono,position);
  }
longcpy(tab_score,score_fichier);
charcpy(tab_pseudo,pseudo);
return position+1;
}

/* ajouter un if(ilatriché == 1) alors on n'appelle pas FinDePartie*/
void FinDePartie(long int dureePartie,char* tab_pseudo,long int* tab_score){
  int i=0;
  char nom_joueur[11];
  do{
    if(ToucheEnAttente()==1){
      nom_joueur[i]=Touche();
      i++;
	}
  }while(tab_pseudo[i]!='\n' &&i<11);
  classement (nom_joueur,dureePartie,tab_pseudo,tab_score;
  
  
    



  
int main (void){
  char name[11]={'z', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a'};
  int chrono=12000;
  int position, i;
  position = classement(name,&chrono);
  printf("\n%d\n", position);
  return 0;
}

