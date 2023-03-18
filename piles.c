#include <stdlib.h>
#include <stdio.h>
#include "piles.h"

pile creerPileVide(){
    return NULL;
}

int estVide(pile p){
    if (p == NULL)
        return 1;
    else
        return 0;
}

pile empiler(pile p, Tunite *c){
    pile new_elem = (pile)malloc(sizeof(struct cellule));
    new_elem->elem = c;
    new_elem->suiv = p;
    return new_elem;      //la Pile pointe sur la tête de la pile
}

pile depiler(pile p){
pile p2 = p;
    if (p!=NULL){
        p2 = p->suiv;     // nouvelle tête
        free(p);          // liberation de la mémoire sur l'ancienne tête
    }
return p2;
}

int hauteurPile(pile p){
    if (p == NULL)
        return 0;
    else return 1 + hauteurPile(p->suiv);
}

Tunite* tetePile(pile p){
    if (p!=NULL)
        return p->elem;
    else{
        printf("\nPile vide: erreur dans tetepile\n");
        exit(EXIT_FAILURE);
    }
}

void AffichePile(pile *p)
{
    pile temp = *p ;
    pile temp2 = creerPileVide() ;
    if ( estVide(temp) )
    {
        printf("Pile Vide pas dAffichage");
    }
    else
    {
        int i = 0 ;
        while (!estVide(temp))
        {
            printf("n°%d Unite : %d et adresse : %p\n",i,temp->elem->nom,temp->elem);
            temp2 = empiler(temp2,tetePile(temp));

            i += 1 ;
            temp = depiler(temp);

        }
        while (!estVide(temp2) )
        {
            temp = empiler(temp,tetePile(temp2));
            temp2 = depiler(temp2);
        }
        *p = temp ;
    }

}
