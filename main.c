//essai du code c sous gcc et windows
#include <stdio.h>
#include<stdlib.h>
#include <time.h>
#include<math.h>
#include "craps.h"

typedef struct Joueur Joueur;
typedef struct De de;

int main(void)
{
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
			printf("Entrez votre nom : ");
			Joueur* ListeJoueur;
			Joueur* j1;
			j1 = (Joueur*)malloc(sizeof(Joueur));
			scanf("%s", j1->nom);
			j1->argent = 1000;
			ListeJoueur = (Joueur*)malloc(nb_joueur * sizeof(Joueur));
			ListeJoueur[0] = *j1;
			printf("Une nouvelle partie vient de démarrer %s ! \n\n", ListeJoueur[0].nom);
			etape1(ListeJoueur);
			system("pause");

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