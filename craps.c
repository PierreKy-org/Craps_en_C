#include <stdio.h>
#include<stdlib.h>
#include <time.h>
#include<math.h>
#include<string.h>
#include"craps.h"

void fichier_to_fichier(Joueur* ListeJoueur, int nb_joueur) {
	Joueur best = tri_score(ListeJoueur, nb_joueur);
	char nom[10][20];
	int score[10];
	FILE* fichier = NULL;
	fichier = fopen("highscore.txt", "r");
	if (fichier == NULL) {
		int fclose(fichier);
		fichier = fopen("highscore.txt", "w");
	}
	fseek(fichier, 0, SEEK_END);
	int nb= ftell(fichier);
	if(nb == 0) {
		int fclose(fichier);
		fichier = fopen("highscore.txt", "w");
		printf("ALLOOOOOOOOOOOOOOOOOOOOOOOO");
		printf("%s - %d", best.nom, best.argent);
		fprintf(fichier, "%s - %d", best.nom, best.argent);
	}
	else {
		int fclose(fichier);
		fichier = fopen("highscore.txt", "r");
		fseek(fichier, 0, SEEK_END);
		int fin = ftell(fichier);
		fseek(fichier, 0, SEEK_SET);
		printf("ALHUILE LOL\n");
		int w = 0;
		while (ftell(fichier) != fin) {
			fscanf(fichier, "%s - %d", nom[w], &score[w]);
			printf("%s - %d \n", nom[w], score[w]);
			w++;
		}
	}
	int fclose(fichier);
}


Joueur tri_score(Joueur* ListeJoueur,int nb_joueur) {
	int max = ListeJoueur[0].argent;
	int qui = 0;
	int i = 1;
	for (i; i < nb_joueur;i++) {
		if (ListeJoueur[i].argent > max) {
			max = ListeJoueur[i].argent;
			qui = i;
		}
	}
	return ListeJoueur[qui];
}
void montre_argent(Joueur* ListeJoueur, int mode_jeu, int nb_joueur) {
		int j = 0;
		for (j;j < nb_joueur;j++) {
			printf("%s, vous avez %d d'argent\n", ListeJoueur[j].nom, ListeJoueur[j].argent);
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
int verifD(Joueur* ListeJoueur, int lance, int mode_jeu, int nb_joueur) {
	if (lance == 7) {
		int i = 0;
		for (i; i < 6; i++) {
			if (ListeJoueur[i].choix == 1) {
				ListeJoueur[i].argent += ListeJoueur[i].mise * 2;
			}
			ListeJoueur[i].mise = 0;
		}
		if (continuer(mode_jeu) == 1) {
			fichier_to_fichier(ListeJoueur, nb_joueur);
			return 1;
		}
		else {
			fichier_to_fichier(ListeJoueur, nb_joueur);
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
		if (continuer(mode_jeu) == 1) {
			fichier_to_fichier(ListeJoueur, nb_joueur);
			return 1;
		}
		else {
			fichier_to_fichier(ListeJoueur, nb_joueur);
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
		if (continuer(mode_jeu) == 1) {
			fichier_to_fichier(ListeJoueur, nb_joueur);
			return 1;
		}
		else {
			fichier_to_fichier(ListeJoueur, nb_joueur);
			return 0;
		}
	}
	else {
		int* point = NULL;
		point = malloc(sizeof(int));
		*point = lance;
		printf("Le point est %d !\nL'etape 2 demarre!\n", *point);
		if (etape2(ListeJoueur, point, mode_jeu, nb_joueur) == 0) {
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
		encore = verifD(ListeJoueur, lance, mode_jeu, nb_joueur);
		montre_argent(ListeJoueur, mode_jeu, nb_joueur);
	}
}
void misedeux(Joueur* ListeJoueur, int mode_jeu, int nb_joueur) {
	int valide = 0;
	while (valide == 0) {
		if (mode_jeu == 2) {
			int j = 0;
			for (j;j < nb_joueur; j++) {
				printf("%s, ", ListeJoueur[j].nom);
				if (ListeJoueur[j].choix == 1) {
					int up_mise;
					printf("de combien voulez-vous augmenter la mise sur Pass ?\n\n");
					scanf("%d", &up_mise);
					if (up_mise > ListeJoueur[j].argent) {
						printf("Vous ne pouvez pas miser plus que votre argent !\n\n");
					}
					else {
						ListeJoueur[j].argent -= up_mise;
						ListeJoueur[j].mise += up_mise;
						printf("\n#Vous avez mise %d \n", ListeJoueur[j].mise);
						valide = 1;
					}

				}
				else {
					int down_mise;
					printf("De combien voulez-vous diminuer la mise sur Don't Pass ?\n\n");
					scanf("%d", &down_mise);
					if (down_mise > ListeJoueur[j].mise) {
						printf("Vous ne pouvez pas enlever plus que votre mise !\n\n");
					}
					else {
						ListeJoueur[j].argent += down_mise;
						ListeJoueur[j].mise -= down_mise;
						printf("\n#Vous avez mise %d \n", ListeJoueur[j].mise);
						valide = 1;
					}
				}
			}
		}
		if (mode_jeu == 1) {
			if (ListeJoueur[0].choix == 1) {
				int up_mise;
				printf("de combien voulez-vous augmenter la mise sur Pass ?\n\n");
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
					ListeJoueur[0].argent += down_mise;
					ListeJoueur[0].mise -= down_mise;
					printf("\n#Vous avez mise %d \n", ListeJoueur[0].mise);
					valide = 1;
				}
			}
		}
	}
	if (mode_jeu == 1){
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
}
int verifDD(Joueur* ListeJoueur, int lance, int* point, int first, int mode_jeu, int nb_joueur) {
	if (lance == *point) {
		int i = 0;
		for (i; i < 6; i++) {
			if (ListeJoueur[i].choix == 1) {
				ListeJoueur[i].argent += ListeJoueur[i].mise * 2;

			}
			
			ListeJoueur[i].mise = 0;
		}
		if (continuer(mode_jeu) == 1) {
			fichier_to_fichier(ListeJoueur, nb_joueur);
			return 1;
		}
		else {
			fichier_to_fichier(ListeJoueur, nb_joueur);
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
		if (continuer(mode_jeu) == 1) {
			fichier_to_fichier(ListeJoueur, nb_joueur);
			return 1;
		}
		else {
			fichier_to_fichier(ListeJoueur, nb_joueur);
			return 0;
		}
	}
	else {

		return 2;
	}
}
void miseDD(Joueur* ListeJoueur, int first, int mode_jeu, int nb_joueur) {
	
	if (first == 1) {
		int reponse;
		if (mode_jeu == 2) {
			int k = 0;
			for (k;k < nb_joueur;k++) {
				if ((2 * ListeJoueur[k].mise) < (ListeJoueur[k].argent)) {
					printf("%s, voulez-vous doubler votre mise ?\n1.Oui\n2.Non\n\n", ListeJoueur[k].nom);
					scanf("%d", &reponse);
					if (reponse == 1) {
						ListeJoueur[k].argent -= ListeJoueur[k].mise;
						ListeJoueur[k].mise += ListeJoueur[k].mise;
					}
				}
				else {
					printf("Vous ne pouvez pas miser plus que votre argent !");
				}
			}
		}
		if(mode_jeu == 1){
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
	}
	else {
		int reponse1;
		if (mode_jeu == 2) {
			int q = 0;
			for (q;q < nb_joueur;q++) {
				printf("%s, voulez-vous diviser votre mise par 2?\n1.Oui\n2.Non\n\n", ListeJoueur[q].nom);
				scanf("%d", &reponse1);

				if (reponse1 == 1) {
					ListeJoueur[q].argent += ListeJoueur[q].mise / 2;
					ListeJoueur[q].mise -= ListeJoueur[q].mise / 2;
					first = 2;
				}
			}
		}
		if (mode_jeu == 1) {
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
					ListeJoueur[j].argent += ListeJoueur[j].mise / 2;
					ListeJoueur[j].mise -= ListeJoueur[j].mise / 2;
				}
			}
		}
	}
	if (mode_jeu == 2) {
		int g = 0;
		for (g;g < nb_joueur;g++) {
			printf("%s, vous avez mise %d \n", ListeJoueur[g].nom,ListeJoueur[g].mise);
		}
	}
	if (mode_jeu == 1) {
		printf("#####################\n#Vous avez mise %d \n", ListeJoueur[0].mise);
		int w = 1;
		for (w; w < 6; w++) {
			int mise_ordi = rand() % ListeJoueur[w].argent;
			ListeJoueur[w].mise += mise_ordi;
			ListeJoueur[w].argent -= mise_ordi;
			printf("#%s a mise %d\n", ListeJoueur[w].nom, ListeJoueur[w].mise);
		}
	}
	printf("#####################\n\n");
}
int etape2(Joueur* ListeJoueur, int* point, int mode_jeu, int nb_joueur) {
	int encore = 1;
	int first = 0;
	while (encore) {
		if (first == 0) {
			misedeux(ListeJoueur, mode_jeu, nb_joueur);
			first++;
		}
		else {
			miseDD(ListeJoueur, first, mode_jeu, nb_joueur);
			first++;
		}
		int lance = lanceD();
		if (verifDD(ListeJoueur, lance, point, first, mode_jeu, nb_joueur) == 0) {
			return 0;
		}
		if (verifDD(ListeJoueur, lance, point, first, mode_jeu, nb_joueur) == 1) {
			break;
		}
	}
	return 1;
}
int continuer(int mode_jeu) {
	if (mode_jeu == 1) {
		printf("Voulez-vous rejouer ?\n\n");
	}
	else {
		printf("Voulez-vous tous rejouer ?\n\n");
	}
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
