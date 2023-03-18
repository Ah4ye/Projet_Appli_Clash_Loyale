#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "types.h"

void hello(){
    printf("hello\n");
};

char * tableauNomUniteDuJeu[] = {"Tour", "TourRoi", "Archer", "Chevalier", "Dragon", "Gargouille"} ; // Appelation pour simplifier ajoute de notre part

TListePlayer getptrNextCell(TListePlayer l)
{
    if(l->suiv==NULL)
    {
        return NULL;
    }
    else
    {
        return l->suiv;
    }
}

void swapPtrData( TListePlayer source, TListePlayer destination)
{

    if(estVideTlist(source)||(estVideTlist(destination)))
    {
        printf("liste vide");
    }
    Tunite *temp = source->pdata;

    source->pdata= destination->pdata;
    destination->pdata=temp;


}
TListePlayer ConcatTListPlayer ( TListePlayer P1 , TListePlayer P2)
{
        TListePlayer player = P2;
         TListePlayer temp = P1;
        while (!estVideTlist(temp))
        {
            AjouterUnite(&player,temp->pdata);
            temp = temp -> suiv ;
        }
        return player ;
}

void afficheListPlayer(TListePlayer player)
{
    if (estVide(player))
    {
        printf("List vide \n");
    }
    else
    {
        while(!estVide(player))
        {
            printf("Uniter dans la liste : %s \n", tableauNomUniteDuJeu[player->pdata->nom]);

            player = player ->suiv;
        }
    }
}




int TailleTListPlayer(TListePlayer player)//
{
    int taille = 0 ;
    while (!estVide(player))
    {
         player = player->suiv;
         taille += 1 ;
    }
    return taille ;
}




bool estVideTlist(TListePlayer P)
{
    if (P  == NULL) { return true ;}
    else return false ;

}

void AffectationCouleurDeCamp(TPlayer player)
{
    TListePlayer L = player.listeU;

    if( player.couleurJoueur == 0)
    {
        while (!estVideTlist(L))
        {
            L->pdata->couleurUnite = 0 ; // bleu
            L = L->suiv ;
        }
    }
    else
    {
        while (!estVideTlist(L))
        {
            L->pdata->couleurUnite = 1 ; // rouge
            L = L->suiv ;
        }
    }
}

int VerifieCampUniter(Tunite Uniter)
{
    if (Uniter.couleurUnite == 0) // 0 pour bleu
    {
        return 0 ;
    }
    else return 1 ; // 1 pour rouge
}
