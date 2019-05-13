#include <stdio.h>
#include<stdlib.h>
#include <time.h>
#include<math.h>
#include"craps.h"

int lanceD() {
	printf("Les des sont lances... \n");
	srand(time(NULL));
	int premierD = rand() % 7;
	printf("Le premier donne %d\n", premierD);
	int deuxiemeD = rand() % 7;
	printf("Le deuxieme donne %d\n", deuxiemeD);
	int sommeD = premierD + deuxiemeD;
	printf("Vous avez donc fait un %d !\n", sommeD);
	return sommeD;
}
void verifD(Joueur* ListeJoueur, int lance, int mise) {
	if (lance == 7) {
		if (ListeJoueur[0].choix == 1) {
			ListeJoueur[0].argent += mise * 2;
		}
	}
	if (lance == 2) {
		if (ListeJoueur[0].choix == 0) {
			ListeJoueur[0].argent += mise * 2;
		}
	}
}
int choisir(Joueur* ListeJoueur) {
	int choix = 3;
	printf("###################\n#Faites un choix :#\n#1.Pass           #\n#2.Don'tPass      #\n###################\n\n");
	if (scanf("%d", &choix) == 1) {
		printf("Vous avez choisi de Pass\n");
	}
	else {
		printf("Vous avez choisi de Don't pass\n");
	}
	for (int i = 1; i < 6; i++) {
		int ale = rand()%2 +1;
		ListeJoueur[i].choix = ale;
	}
	return choix;
}
void miser(Joueur* ListeJoueur) {
	int mise;
	int valide_mise = 0;
	ListeJoueur[0].choix = choisir(ListeJoueur);
	printf("Le choix des autres joueurs : %d, %d, %d, %d et %d\n", ListeJoueur[1].choix, ListeJoueur[2].choix, ListeJoueur[3].choix, ListeJoueur[4].choix, ListeJoueur[5].choix);
	while (valide_mise == 0) {
		printf("Vous possedez %d.\nCombien voulez vous miser ? : \n", ListeJoueur[0].argent);
		scanf("%d", &mise);
		if (mise > ListeJoueur[0].argent) {
			printf("Vous ne pouvez pas miser plus que votre argent !\n");
		}
		else {
			printf("Vous avez mise %d \n", mise);
			ListeJoueur[0].mise = mise;
			ListeJoueur[0].argent = ListeJoueur[0].argent - mise;
			valide_mise = 1;
		}
	}
}




