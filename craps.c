#include <stdio.h>
#include<stdlib.h>
#include <time.h>
#include<math.h>
#include<string.h>
#include"craps.h"
void montre_argent(Joueur* ListeJoueur) {
	printf("T'as %d d'argent\n", ListeJoueur[0].argent);
	int i = 1;
	for (i; i < 6; i++) {
		printf("#%s a %d d'argent\n", ListeJoueur[i].nom, ListeJoueur[i].argent);
	}
}
int lanceD() {
	srand(time(NULL));
	int premierD = rand() % 6 + 1;
	printf("#############################\n#Les des sont lances...     #\n#Le premier donne %d         #\n", premierD);
	int deuxiemeD = rand() % 6 + 1;
	printf("#Le deuxieme donne %d        #\n", deuxiemeD);
	int sommeD = premierD + deuxiemeD;
	printf("#Vous avez donc fait un %d ! #\n#############################\n\n", sommeD);
	return sommeD;
}
int verifD(Joueur* ListeJoueur, int lance) {
	if (lance == 7) {
		int i = 0;
		for (i; i < 6; i++) {
			if (ListeJoueur[i].choix == 1) {
				ListeJoueur[i].argent += ListeJoueur[i].mise * 2;

			}
			ListeJoueur[i].mise = 0;
		}
		if (continuer() == 1) {
			return 1;
		}
		else {
			return 0;
		}
	}
	if (lance == 2) {
		int j = 0;
		for (j; j < 6; j++) {
			if (ListeJoueur[j].choix == 2) {
				ListeJoueur[j].argent += ListeJoueur[j].mise * 2;

			}
			ListeJoueur[j].mise = 0;
		}
		if (continuer() == 1) {
			return 1;
		}
		else {
			return 0;
		}
	}
	if (lance == 12) {
		int w = 0;
		for (w; w < 6; w++) {
			if (ListeJoueur[w].choix == 1) {
				ListeJoueur[w].mise = 0;
			}
		}
		if (continuer() == 1) {
			return 1;
		}
		else {
			return 0;
		}
	}
	else {
		int* point = NULL;
		point = malloc(sizeof(int));
		*point = lance;
		printf("Le point est %d !\nL'etape 2 demarre!\n", *point);
		if (etape2(ListeJoueur, point) == 0) {
			return 0;
		}
		else {
			return 1;
		}
	}
}
int choisir(Joueur* ListeJoueur, int mode_jeu) {
	int choix;
	printf("###################\n#Faites un choix :#\n#1.Pass           #\n#2.Don'tPass      #\n###################\n\n");
	scanf("%d", &choix);
	if (choix == 1) {
		printf("##################################\n");
		printf("#Vous avez choisi de Pass\n");
	}
	else {
		printf("##################################\n");
		printf("#Vous avez choisi de Don't pass\n");
	}
	if (mode_jeu == 1) {
		char* texte = NULL;
		int i = 1;
		for (i; i < 6; i++) {
			int ale = rand() % 2 + 1;
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
	}
	return choix;
}
int miser(Joueur* ListeJoueur, int mode_jeu, int nb_joueur) {
	int mise;
	int valide_mise = 0;
	if (mode_jeu == 2) {
		int i = 0;
		for (i;i < nb_joueur;i++) {
			int valide_miise = 0;
			ListeJoueur[i].choix = choisir(ListeJoueur,mode_jeu);
			while (valide_miise == 0) {
				printf("\n%s, vous possedez %d.\nCombien voulez vous miser ? : \n", ListeJoueur[i].nom, ListeJoueur[i].argent);
				scanf("%d", &mise);
				if (mise > ListeJoueur[i].argent) {
					printf("Vous ne pouvez pas miser plus que votre argent !\n\n");
				}
				else {
					printf("#####################\n#Vous avez mise %d \n", mise);
					printf("#####################\n\n");
					ListeJoueur[i].mise += mise;
					ListeJoueur[i].argent = ListeJoueur[i].argent - mise;
					valide_miise = 1;
				}
			}
		}
		return 0;
		
	}
	else {
		ListeJoueur[0].choix = choisir(ListeJoueur, mode_jeu);
		while (valide_mise == 0) {
			printf("\nVous possedez %d.\nCombien voulez vous miser ? : \n", ListeJoueur[0].argent);
			scanf("%d", &mise);
			if (mise > ListeJoueur[0].argent) {
				printf("Vous ne pouvez pas miser plus que votre argent !\n\n");
			}
			else {
				printf("#####################\n#Vous avez mise %d \n", mise);
				int j = 1;
				for (j; j < 6; j++) {
					int mise_ordi = rand() % ListeJoueur[j].argent;
					ListeJoueur[j].mise += mise_ordi;
					ListeJoueur[j].argent -= mise_ordi;
					printf("#%s a mise %d\n", ListeJoueur[j].nom, ListeJoueur[j].mise);
				}
				printf("#####################\n\n");
				ListeJoueur[0].mise += mise;
				ListeJoueur[0].argent = ListeJoueur[0].argent - mise;
				valide_mise = 1;
			}
		}
	}
	return 0;
}
void etape1(Joueur* ListeJoueur, int mode_jeu, int nb_joueur){
	int encore = 1;
	while (encore) {
		printf("Une nouvelle partie vient de demarrer ! \n\n");
		printf("Vous jouez avec :\n");
		int i = 0;
		for (i; i < nb_joueur;i++) {
			printf("- %s\n", ListeJoueur[i].nom);
		}
		miser(ListeJoueur, mode_jeu,nb_joueur);
		int lance = lanceD();
		encore = verifD(ListeJoueur, lance);
		montre_argent(ListeJoueur);
	}
}
void misedeux(Joueur* ListeJoueur) {
	int valide = 0;
	while (valide == 0) {
		if (ListeJoueur[0].choix == 1) {
			int up_mise;
			printf("De combien voulez-vous augmenter la mise sur Pass ?\n\n");
			scanf("%d", &up_mise);
			if (up_mise > ListeJoueur[0].argent) {
				printf("Vous ne pouvez pas miser plus que votre argent !\n\n");
			}
			else {
				ListeJoueur[0].argent -= up_mise;
				ListeJoueur[0].mise += up_mise;
				printf("\n#Vous avez mise %d \n", ListeJoueur[0].mise);
				valide = 1;
			}

		}
		else {
			int down_mise;
			printf("De combien voulez-vous diminuer la mise sur Don't Pass ?\n\n");
			scanf("%d", &down_mise);
			if (down_mise > ListeJoueur[0].mise) {
				printf("Vous ne pouvez pas enlever plus que votre mise !\n\n");
			}
			else {
				printf("\n#Vous avez mise %d \n", ListeJoueur[0].mise);
				ListeJoueur[0].argent += down_mise;
				ListeJoueur[0].mise -= down_mise;
				valide = 1;
			}
		}
	}
	int i = 1;
	for (i; i < 6;i++) {
		if (ListeJoueur[i].choix == 1) {
			ListeJoueur[i].mise += rand() % ListeJoueur[i].argent;
		}
		else {
			int down_bot = rand() % ListeJoueur[i].argent;
			ListeJoueur[i].mise -= down_bot;
			ListeJoueur[i].argent += down_bot;

		}
	}
}
int verifDD(Joueur* ListeJoueur, int lance, int* point, int first) {
	if (lance == *point) {
		int i = 0;
		for (i; i < 6; i++) {
			if (ListeJoueur[i].choix == 1) {
				ListeJoueur[i].argent += ListeJoueur[i].mise * 2;

			}
			ListeJoueur[i].mise = 0;
		}
		if (continuer() == 1) {
			return 1;
		}
		else {
			return 0;
		}
	}
	if (lance == 7) {
		int j = 0;
		for (j; j < 6; j++) {
			if (ListeJoueur[j].choix == 2) {
				ListeJoueur[j].argent += ListeJoueur[j].mise * 2;

			}
			ListeJoueur[j].mise = 0;
		}
		if (continuer() == 1) {
			return 1;
		}
		else {
			return 0;
		}
	}
	else {
		return 2;
	}
}
void miseDD(Joueur* ListeJoueur, int first) {
	if (first == 1) {
		int reponse;
		if ((2 * ListeJoueur[0].mise) < (ListeJoueur[0].argent)) {
			printf("Voulez-vous doubler votre mise ?\n1.Oui\n2.Non\n\n");
			scanf("%d", &reponse);
		
			if (reponse == 1) {
				ListeJoueur[0].argent -= ListeJoueur[0].mise;
				ListeJoueur[0].mise += ListeJoueur[0].mise;
				
			}
		}
		else {
			printf("Vous ne pouvez pas miser plus que votre argent !");
		}
		int i = 1;
		for (i; i < 6;i++) {
			int random = rand() % 2;
			if ((random == 1) && ((2 * ListeJoueur[i].mise) < ListeJoueur[i].argent)) {
				ListeJoueur[i].argent -= ListeJoueur[i].mise;
				ListeJoueur[i].mise += ListeJoueur[i].mise;
			}
		}
	}
	else {
		int reponse1;
		printf("Voulez-vous diviser votre mise par 2?\n1.Oui\n2.Non\n\n");
		scanf("%d", &reponse1);
		
		if (reponse1 == 1) {
			ListeJoueur[0].argent += ListeJoueur[0].mise/2;
			ListeJoueur[0].mise -= ListeJoueur[0].mise/2;
			first = 2;
		}
		int j = 1;
		for (j; j < 6;j++) {
			int random = rand() % 2;
			if ((random == 1) && ((2 * ListeJoueur[j].mise) < ListeJoueur[j].argent)) {
				ListeJoueur[j].argent += ListeJoueur[j].mise/2;
				ListeJoueur[j].mise -= ListeJoueur[j].mise/2;
			}
		}
	}
	printf("#####################\n#Vous avez mise %d \n", ListeJoueur[0].mise);
	int w = 1;
	for (w; w < 6; w++) {
		int mise_ordi = rand() % ListeJoueur[w].argent;
		ListeJoueur[w].mise += mise_ordi;
		ListeJoueur[w].argent -= mise_ordi;
		printf("#%s a mise %d\n", ListeJoueur[w].nom, ListeJoueur[w].mise);
	}
	printf("#####################\n\n");
}
int etape2(Joueur* ListeJoueur, int* point) {
	int encore = 1;
	int first = 0;
	while (encore) {
		if (first == 0) {
			misedeux(ListeJoueur);
			first++;
		}
		else {
			miseDD(ListeJoueur, first);
			first++;
		}
		int lance = lanceD();
		if (verifDD(ListeJoueur, lance, point, first) == 0) {
			return 0;
		}
		if (verifDD(ListeJoueur, lance, point, first) == 1) {
			break;
		}
	}
	return 1;
}
int continuer() {
	printf("Voulez-vous rejouer ?\n\n");
	char test[4];
	while ((getchar()) != '\n');
	fgets(test, sizeof(test), stdin);
	while ((getchar()) != '\n');
	if (strcmp(test, "oui") == 0) {
		return 1;
	}
	else {
		printf("Pas de soucis ! \nRetour au menu principal! \n\n");
		
		return 0;
	}
}
