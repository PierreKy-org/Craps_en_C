#include <stdio.h>
#include<stdlib.h>
#include <time.h>
#include<math.h>
#include"craps.h"

void etape1(Joueur* ListeJoueur) {
	int mise;
	int choix = 3;
	int valide_mise = 0;
	printf("###################\n#Faites un choix :#\n#1.Pass           #\n#2.Don'tPass      #\n###################\n\n");
	if (scanf("%d", &choix) == 1) {
		printf("Vous avez choisi de Pass\n");
	}
	else {
		printf("Vous avez choisi de Don't pass\n");
	}
	ListeJoueur[0].choix = choix;
	while (valide_mise == 0) {
		printf("Vous possédez %d.\nCombien voulez vous miser ? : \n", ListeJoueur[0].argent);
		scanf("%d", &mise);
		if ( mise > ListeJoueur[0].argent) {
			printf("Vous ne pouvez pas miser plus que votre argent !\n");
		}
		else {
			printf("Vous avez misé %d \n", mise);
			ListeJoueur[0].mise = mise;
			ListeJoueur[0].argent = ListeJoueur[0].argent - mise;
			valide_mise = 1;
		}
	}
	printf("Les dés sont lancés... \n");
	srand(time(NULL));
	int premierD = rand() % 7;
	printf("Le premier donne %d\n", premierD);
	int deuxiemeD = rand() % 7;
	printf("Le deuxième donne %d\n", deuxiemeD);
	int sommeD = premierD + deuxiemeD;
	printf("Vous avez donc fait un %d !\n", sommeD);
	if (sommeD == 7) {
		if (ListeJoueur[0].choix == 1) {
			ListeJoueur[0].argent += mise * 2;
		}
	}
	if (sommeD == 2) {
		if (ListeJoueur[0].choix == 0) {
			ListeJoueur[0].argent += mise * 2;
		}
	}
	printf("T'as %d d'argent\n", ListeJoueur[0].argent);
}




