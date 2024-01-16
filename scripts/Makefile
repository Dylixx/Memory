# TP 19 Exercice 1 : fichier Makefile

# CHAPITRE 1 : BUT FINAL

but : exe

# CHAPITRE 2 : VARIABLES

OFILES = intPlus.o \
	 boutons.o \
	 cartes.o \
	 jeu.o \
	 menus.o \
         main.o

CC = gcc

CFLAGS = -Wall -g -lgraph -lm

# CHAPITRE 3 : DEPENDANCES (REGLES IMPLICITES)

cartes.o : cartes.c intPlus.h
jeu.o : jeu.c intPlus.h cartes.h
menus.o : menus.c boutons.h intPlus.h jeu.h
main.o : main.c boutons.h menus.h cartes.h

#CHAPITRE 4 : DEPENDANCES AVEC COMMANDES

exe : $(OFILES)
	$(CC) $(CFLAGS) -o exe $(OFILES)

#CHAPITRE 5 : NETTOYAGE DES FICHIERS GENERES

clean :
	-rm -f $(OFILES) exe

#CHAPITRE 6 : BUTS FACTICES

.PHONY : but clean
