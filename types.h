#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED


typedef enum{tour, tourRoi, archer, chevalier, dragon, gargouille} TuniteDuJeu;
typedef enum{sol, solEtAir, air } Tcible;
typedef enum{bleu, rouge} Tcouleur;

typedef struct {
    TuniteDuJeu nom;
    Tcible cibleAttaquable;	//indique la position des unités que l’on peut attaquer
    Tcible maposition;		//indique soit « air » soit « sol », utile pour savoir
                            //qui peut nous attaquer
    int pointsDeVie;
    float vitesseAttaque;	//en seconde, plus c’est petit plus c’est rapide
    int degats;
    int portee ;			//en mètre, distance sur laquelle on peut atteindre une
                            //cible

    float vitessedeplacement;	//en m/s
    int posX, posY;			//position sur le plateau de jeu
    int peutAttaquer;		//permet de gérer le fait que chaque unité attaque une
                            //seule fois par tour ;
                            //0 = a déjà attaqué, 1 = peut attaquer ce tour-ci
                            // à remettre à 1 au début de chaque tour
    int coutEnElixir;
	Tcouleur couleurUnite; //camp de l'unité (rouge ou bleu)
} Tunite;

typedef struct T_cell{
    struct T_cell *suiv;
    Tunite *pdata; //pointeur vers une unité
} *TListePlayer;

///********************* NOUVEAUTE ***************************


typedef struct {
    TListePlayer listeU;  //la liste des unités du joueur
    int elixir;
    Tcouleur couleurJoueur;
} TPlayer;

///********************* fin NOUVEAUTE ***************************

///********************* Ajout Arthur ***************************

// J'ai ajouter #include <stdbool.h> dans type.h et type.c
void afficheListPlayer(TListePlayer player);
int TailleTListPlayer(TListePlayer player);
bool estVideTlist(TListePlayer P);
char * tableauNomUniteDuJeu[]; // Pour afficher le nom des uniter avec la fonction afficheListPlayer

void AffectationCouleurDeCamp(TPlayer player); // A tester
int VerifieCampUniter(Tunite Uniter); // A tester
///********************* Fin Ajout Arthur ***************************

#endif // TYPES_H_INCLUDED
