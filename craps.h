typedef struct Joueur Joueur;
struct Joueur {
	int argent;
	char nom[50];
	int mise;
	int en_train_de_jouer;
	int choix;
};
int lanceD();
int miser(Joueur* ListeJoueur, int mode_jeu, int nb_joueur);
int verifD(Joueur* ListeJoueur, int lance, int mode_jeu, int nb_joueur);
int choisir(Joueur* ListeJoueur, int mode_jeu);
void etape1(Joueur* ListeJoueur, int mode_jeu, int nb_joueur);
void misedeux(Joueur* ListeJoueur, int mode_jeu, int nb_joueur);
int verifDD(Joueur* ListeJoueur, int lance, int* point, int first, int mode_jeu);
void miseDD(Joueur* ListeJoueur, int first, int mode_jeu, int nb_joueur);
int etape2(Joueur* ListeJoueur, int* point, int mode_jeu, int nb_joueur);
void montre_argent(Joueur* ListeJoueur, int mode_jeu, int nb_joueur);
int continuer(int mode_jeu);