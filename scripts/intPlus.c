#include <stdio.h>
#include <stdlib.h>

/*Permet de convertir un nombre (int) en chaine de caractère d’une certaine taille (la fonction met des zéros avant le nombre si la taille est plus grande que le nombre). Attention elle ne marche que si la taille de la chaîne est égal ou supérieur à la taille du nombre.
 La chaine de caractere (qui est un nombre) ainsi créer est ajouté à la fin d'une chaine donnée en 3eme argument. Attention à la capacite*/
void intToString(int nb, int taille, char* chaine){
    int i, digit, puissanceDe10;
    for(puissanceDe10=1,i=1;i<taille;i++,puissanceDe10*=10){
    }
    for(i=0;chaine[i]!='\0';i++){
    }
    for (;puissanceDe10>=1;i++, puissanceDe10/=10){
        digit=nb/puissanceDe10;
        nb-=digit*puissanceDe10;
        chaine[i] = (char) digit+48;
	//le +48 permet d'ajuster l'entier à l'entier correspondant en ASCII
    }
    chaine[i]='\0';
}

//Trouve la taille (en caractère) d’un entier.Attention elle ne marche que pour des nombres positifs
int intLen(int nb){
    int puissanceDe10 = 10;
    int taille;
    for (taille=1; puissanceDe10<=nb;puissanceDe10*=10,taille++){
    }
    return taille;
}
