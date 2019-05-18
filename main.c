//essai du code c sous gcc et windows
#include <stdio.h>
#include<stdlib.h>
#include <time.h>
#include<math.h>
#include<string.h>
#include "craps.h"

typedef struct Joueur Joueur;


int main(void)
{
	srand(time(NULL));
	char NomOrdi[12][30] = { "Etienne", "Philippe", "Edouard", "Carole", "Emilie", "Lea", "Andrea", "Gregory", "Alizee", "Julie", "Michel", "Michelle" };
	Joueur* ListeJoueur;
	int nb_joueur = 1;
	int fin = 0;
	while (!fin)
	{
		int c;
		printf("#################\n# 1.Solo        #\n# 2.Multijoueur #\n# 3.Highscore   #\n# 4.Quitter     #\n#################\n");
		c = getchar();
		if (c != '\n' && c != EOF)
		{
			int d;
			while ((d = getchar()) != '\n' && d != EOF);
		}

		switch (c)
		{
		case '1':
			ListeJoueur = (Joueur*)malloc(6 * sizeof(Joueur));
			Joueur* j1;
			j1 = (Joueur*)malloc(sizeof(Joueur));
			printf("Entrez votre nom : ");
			scanf("%s", j1->nom);
			j1->argent = 1000;
			j1->mise = 0;
			ListeJoueur[0] = *j1;
			int i = 1;
			for (i; i < 6; i++) {
				Joueur* ordi;
				ordi = (Joueur*)malloc(sizeof(Joueur));
				int ale = rand() % 12;
				strcpy(ordi->nom, NomOrdi[ale]);
				ListeJoueur[i] = *ordi;
				ListeJoueur[i].argent = 1000;
				ListeJoueur[i].mise = 0;
			}
			etape1(ListeJoueur, 1, 6);
			free(ListeJoueur);
			break;

		case '2':
			printf("Combien de joueur ?\n\n");
			int nb_joueur;
			scanf("%d", &nb_joueur);
			while (getchar()!='\n');
			printf("Il y a donc %d joueurs dans cette partie\n\n", nb_joueur);
			ListeJoueur = (Joueur*)malloc(nb_joueur * sizeof(Joueur));
			int j = 0;
			for (j; j < nb_joueur; j++) {
				Joueur* j1;
				j1 = (Joueur*)malloc(sizeof(Joueur));
				printf("Entrez le nom du joueur %d: ", (j+1));
				scanf("%s", j1->nom);
				j1->argent = 1000;
				j1->mise = 0;
				ListeJoueur[j] = *j1;
			}
			etape1(ListeJoueur, 2, nb_joueur);
			free(ListeJoueur);
			break;

		case '3':
			printf("Highscore\n\n");
			FILE* fichier = NULL;
			char nom[10][20];
			int score[10];
			fichier = fopen("highscore.txt", "r");
			fseek(fichier, 0, SEEK_END);
			int fin = ftell(fichier);
			fseek(fichier, 0, SEEK_SET);
			int w = 0;
			while (ftell(fichier) != fin) {
				fscanf(fichier, "%s - %d", nom[w], &score[w]);
				printf("%s - %d \n", nom[w], score[w]);
				w++;
			}
			int fclose(fichier);
			break;

		case '4':
			exit(0);
			break;

		default:
			printf("Choix errone\n\n");
		}
	}

	return 0;
}
