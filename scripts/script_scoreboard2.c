#include <stdio.h>
#include <stdlib.h>
int verif(long int temps_chrono,long int* score_fichier){
  int i,flag;
  for(i=0;i<10 && flag!=1;i++){
  printf("le %d > %d ?\n",  temps_chro, score_fichier[i]);
  printf("%d\n", test);
     if(temps_chrono > score_fichier[i]){
       flag++;
       position = i;
       printf("%d\n", position);
              }
 }
  return flag;
}
int classement (char* nom_joueur,long int temps_chrono,char* tab_pseudo,long int* tab_score,int taille_grille){
  int score_fichier[10];
  char pseudo[10][11];
  int position, i, o, flag, test;
  int temps_chro = *temps_chrono;
  char* fichier_grille;
  printf("%d\n", temps_chro);
  top10_path[10]={'t','o','p','1','0','_','\0'};
  strcat(top10_path,fichier_grille = intToString(taille_grille,3);

  FILE* fichier = fopen(top10_path,"r");
if(fichier != NULL){
    printf("C'est bon\n");
    for(i=0;i<10;i++){
        size_t reussite1 = fread(&score_fichier[i],sizeof(int),1,fichier);
	printf("%09d", score_fichier[i]);
        size_t reussite3 = fread(&pseudo[i],sizeof(char),10,fichier);
	pseudo[i][10]='\0';
	printf(" %010s\n", pseudo[i]);
    }

 }
 else{
   return 0;
 }
	 flag=verif(temps_chrono,score_fichier);
	 
	 if(flag==1){
     for(i=9;i>position;i--){
       score_fichier[i]=score_fichier[i-1];
       for(o=0;o<10;o++){
	 pseudo[i][o]=pseudo[i-1][o];
       }
     }
score_fichier[position]=temps_chro;
for(o=0;o<10;o++){
  pseudo[position][o]=nom_joueur[o];
}
fclose(fichier);
 }
 printf("\n\n");
  for(i=0;i<10;i++){
       printf("%09d", score_fichier[i]);
       tab_score[i]=score_fichier[i];
       printf(" %010s\n", pseudo[i]);
       for(o=0;o<11;o++){
	 tab_pseudo[i][o]=pseudo[i][o];
       }
       printf(" %010s\n", tab_pseudo[i]);
    }

return position+1;
 }

/* ajouter un if(ilatriché == 1) alors on appelle pas FinDePartie*/
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

