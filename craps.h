typedef struct Joueur Joueur;
struct Joueur {
	int argent;
	char nom[50];
	int mise;
	int en_train_de_jouer;
	int choix;
};
int lanceD();
void miser(Joueur* ListeJoueur);
void verifD(Joueur* ListeJoueur, int lance, int mise);
int choisir(Joueur* ListeJoueur);