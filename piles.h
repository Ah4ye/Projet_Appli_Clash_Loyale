#ifndef PILES_H_INCLUDED
#define PILES_H_INCLUDED

#include <stdbool.h>
#include "types.h"

// On va gérer ici une pile de cartons de chaussures, défini dans types.h

typedef struct cellule {
    Tunite* elem;            //PILE DE POINTEUR SUR TUNITE
    struct cellule *suiv;
} *pile;

pile creerPileVide();
int estVide(pile p);
pile empiler(pile p, Tunite* c);
pile depiler(pile p);
int hauteurPile(pile p);
Tunite* tetePile(pile p);
void AffichePile(pile *p);
//Tunite* tetepileADR(pile p);  //fonction supprimée de la librairie



#endif // PILES_H_INCLUDED
