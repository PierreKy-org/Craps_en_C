#include <stdio.h>
#include<stdlib.h>
#include <time.h>
#include<math.h>
#include<string.h>
#include"craps.h"

int lanceD() {
	printf("Les des sont lances... \n");
	srand(time(NULL));
	int premierD = rand() % 6 + 1;
	printf("#############################\n#Le premier donne %d         #\n", premierD);
	int deuxiemeD = rand() % 6 + 1;
	printf("#Le deuxieme donne %d        #\n", deuxiemeD);
	int sommeD = premierD + deuxiemeD;
	printf("#Vous avez donc fait un %d ! #\n#############################\n", sommeD);
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
		printf("##################################\n");
		printf("#Vous avez choisi de Pass\n");
	}
	else {
		printf("##################################\n");
		printf("#Vous avez choisi de Don't pass\n");
	}
	char* texte = NULL;
	for (int i = 1; i < 6; i++) {
		int ale = rand()%2 +1;
		
		ListeJoueur[i].choix = ale;
		if (ListeJoueur[i].choix == 1) {
			texte = malloc(5 * sizeof(char));
			strcpy(texte, "Pass");
		}
		else {
			texte = malloc(11 * sizeof(char));
			strcpy(texte, "Don't Pass");
		}
		printf("#%s a choisi %s\n", ListeJoueur[i].nom, texte);
		free(texte);
	}
	printf("##################################\n");
	return choix;
}
void miser(Joueur* ListeJoueur) {
	int mise;
	int valide_mise = 0;
	ListeJoueur[0].choix = choisir(ListeJoueur);
	while (valide_mise == 0) {
		printf("\nVous possedez %d.\nCombien voulez vous miser ? : \n", ListeJoueur[0].argent);
		scanf("%d", &mise);
		if (mise > ListeJoueur[0].argent) {
			printf("Vous ne pouvez pas miser plus que votre argent !\n\n");
		}
		else {
			printf("#####################\n#Vous avez mise %d \n", mise);
			for (int i = 1; i < 6; i++) {
				int mise_ordi = rand() % ListeJoueur[i].argent;
				ListeJoueur[i].mise = mise_ordi;
				ListeJoueur[i].argent -= mise_ordi;
				printf("#%s a mise %d\n", ListeJoueur[i].nom, ListeJoueur[i].mise);
			}
			printf("#####################\n\n");
			ListeJoueur[0].mise = mise;
			ListeJoueur[0].argent = ListeJoueur[0].argent - mise;
			valide_mise = 1;
		}
	}
}




