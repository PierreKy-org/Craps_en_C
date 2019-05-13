typedef struct Joueur Joueur;
struct Joueur {
	int argent;
	char nom[50];
	int mise;
	int en_train_de_jouer;
	int choix;
};

void etape1(Joueur* ListeJoueur);
