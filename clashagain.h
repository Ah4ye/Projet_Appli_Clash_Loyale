#ifndef CLASHAGAIN_H_INCLUDED
#define CLASHAGAIN_H_INCLUDED

#define LARGEURJEU 11
#define HAUTEURJEU 19

///********************* NOUVEAUTE ***************************
#include "zone.h"
#include "types.h"


typedef Tunite* ** TplateauJeu; //le plateau du jeu pour l'affichage (reprise du systreme du projet clashLoyal)
typedef Tzone ** TplateauJeuUpgrade;  ////tableau a deux dimensions de largeur 11 et hauteur 19 contenant des Tzone


///********************* fin NOUVEAUTE ***************************
/// **** AFFICAHGE ******
TplateauJeuUpgrade AlloueTab2D_Tzone(int largeur, int hauteur);  //fourni dans clashagain.c
TplateauJeu AlloueTab2D(int largeur, int hauteur);
void initPlateauAvecNULL(TplateauJeu jeu,int largeur, int hauteur);
void affichePlateauConsole(TplateauJeu jeu, int largeur, int hauteur);
void initPlateauUPAvecNULL(TplateauJeuUpgrade jeu,int largeur, int hauteur);
void PositionnePlayerOnPlateau_Upgade(TListePlayer player, TplateauJeuUpgrade jeuUpgrade);
TplateauJeu ConversionEnTplateauJeu(TplateauJeuUpgrade jeuEncours);

///***** unite *****
Tunite *creeTour(int posx, int posy);
Tunite *creeTourRoi(int posx, int posy);
Tunite *creeArcher(int posx, int posy);
Tunite *creeGargouille(int posx, int posy);
Tunite *creeDragon(int posx, int posy);
Tunite *creeChevalier(int posx, int posy);

/// *** init player/list/bool fin partie ***
void init_P1_P2_Jeu(TPlayer *player1, TPlayer *player2);
TListePlayer initTlistPlayer();
TPlayer initPlayer(Tcouleur couleur);
bool tourRoiDetruite(TListePlayer player);

/// **** gerer uniter ****
//void supprimerUnite(TListePlayer *player, Tunite *UniteDetruite);
void AjouterUnite(TListePlayer *player, Tunite *nouvelleUnite);
void AcheteUnite(TPlayer *player);
void supprimerUnite(TListePlayer *player, Tunite *UniteDetruite);

/// *** partie **

//void combat(TListePlayer player, Tunite *uneUniteDeLautreJoueur);  //devient void
bool UniterRapide(Tunite* A, Tunite *B);
bool UniterVie(Tunite* A, Tunite *B);
void TriParAttribut(TListePlayer player, bool (*fcomp)(Tunite* A, Tunite *B));
TListePlayer quiEstAPortee_Upgrade(TplateauJeuUpgrade jeuEncours, Tunite *uneUniteDeLautreJoueur);
void combat(TListePlayer player, Tunite *uneUniteDeLautreJoueur ,TplateauJeuUpgrade jeuEncours );

TListePlayer quiEstAPortee_Upgrade(TplateauJeuUpgrade jeuEncours, Tunite *uneUniteDeLautreJoueur);
bool Aporter(Tunite *unite, Tunite *uniteAutreJoueur);
TListePlayer AllUnite(TplateauJeuUpgrade jeuEncours , int posX , int posY);




#endif // CLASHAGAIN_H_INCLUDED
