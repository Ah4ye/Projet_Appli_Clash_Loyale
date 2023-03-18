#ifndef LISTUNIT_H_INCLUDED
#define LISTUNIT_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "clashloyal.h"
#include <string.h>
#include <math.h>

void AjouterUnite(TListePlayer *player, Tunite *nouvelleUnite);

void supprimerUnite(TListePlayer *player, Tunite *UniteDetruite) ;

void afficheListPlayer(TListePlayer player);

bool estVide(TListePlayer P);


#endif // LISTUNIT_H_INCLUDED
