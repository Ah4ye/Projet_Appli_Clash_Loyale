#ifndef ZONE_H_INCLUDED
#define ZONE_H_INCLUDED

///********************* NOUVEAUTE ***************************
#include "piles.h"
///********************* NOUVEAUTE ***************************

typedef pile Tzone;


TListePlayer getAllUnitInZone(Tzone *z);


Tzone creerTzoneVide(void);
Tzone ajouterUnitedansZone(Tzone z, Tunite *u);
Tzone supprimerUnitedansZone(Tzone *z,Tunite *u);
bool UniteEstPresentedansZone(Tzone z, Tunite *u);
bool UniteAuSolPresente(Tzone *z);
bool UniteEnVolPresente(Tzone *z);
bool estvide(Tzone z) ;
Tunite *ElemTzone(Tzone z);
int compterZone(Tzone *z);
void afficheZone(Tzone *z);
// et toutes les fonctions qui vous serez utiles sur/avec les Tzone?





#endif // ZONE_H_INCLUDED
