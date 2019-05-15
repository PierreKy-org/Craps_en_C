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
			ListeJoueur[0] = *j1;
			for (int i = 1; i < 6; i++) {
				Joueur* ordi;
				ordi = (Joueur*)malloc(sizeof(Joueur));
				int ale = rand() % 12;
				strcpy(ordi->nom, NomOrdi[ale]);
				ListeJoueur[i] = *ordi;
				ListeJoueur[i].argent = 1000;
			}
			printf("Une nouvelle partie vient de demarrer %s ! \n\n", ListeJoueur[0].nom);
			printf("Vous jouez avec %s, %s, %s, %s et %s.\n\n", ListeJoueur[1].nom, ListeJoueur[2].nom, ListeJoueur[3].nom, ListeJoueur[4].nom, ListeJoueur[5].nom);
			miser(ListeJoueur);
			int lance = lanceD();
			verifD(ListeJoueur, lance, ListeJoueur[0].mise);
			printf("T'as %d d'argent\n", ListeJoueur[0].argent);
			system("pause");
			fin = 1;
			break;

		case '2':
			printf("Multijoueur\n\n");
			break;

		case '3':
			printf("Highscore\n\n");
			break;

		case '4':
			fin = 1;
			break;

		default:
			printf("Choix errone\n\n");
		}
	}

	return 0;
}