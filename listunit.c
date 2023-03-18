
#include "listunit.h"

char * tableauNomUniteDuJeu[] = {"Tour", "TourRoi", "Archer", "Chevalier", "Dragon", "Gargouille"} ; // Appelation pour simplifier ajoute de notre part


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


void AjouterUnite(TListePlayer *player, Tunite *nouvelleUnite)
{
    struct T_cell *nouv = malloc(sizeof(struct T_cell));
    nouv ->pdata = nouvelleUnite ;
    nouv -> suiv = *player ;
    *player = nouv;


}

void supprimerUnite(TListePlayer *player, Tunite *UniteDetruite)
{

    if (estVide(player))
    {
        return 0 ;
    }
    else
    {
        struct T_cell* temp = *player;
        struct T_cell* temp2 = *player;
        if ( temp->pdata == UniteDetruite)
        {
            *player = temp -> suiv ;
           // free(temp->pdata);
            free(temp);

        }
        else
        {
             while( (temp -> suiv != NULL) && (temp->pdata!=  UniteDetruite ) )
             {
                temp = temp -> suiv ;
                if((temp->pdata == UniteDetruite) && (temp->suiv!=NULL))
                {
                    while(temp2->suiv!=temp)
                    {
                        temp2=temp2->suiv;
                    }
                    temp2->suiv=temp->suiv;
                    free(temp);
                }
                else
                {
                    if((temp -> suiv == NULL) && (temp->pdata==  UniteDetruite ))
                    {
                        while(temp2->suiv->suiv!=NULL)
                        {
                            temp2=temp2->suiv;
                        }
                        free(temp);
                        temp2->suiv=NULL;
                    }
                    else if((temp->suiv == NULL)&& (temp->pdata != UniteDetruite))
                    {
                        printf("unite detruite pas dans liste");
                    }
                }
             }
        }
    }
}




bool estVide(TListePlayer P)
{
    if (P  == NULL) { return true ;}
    else return false ;

}
