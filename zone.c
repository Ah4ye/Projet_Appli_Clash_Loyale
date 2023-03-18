#include "zone.h"
#include <stdio.h>
#include <stdlib.h>

bool estvide(Tzone z)
{
    estVide(z) ;
}

Tzone creerTzoneVide(void)
{
    Tzone z = creerPileVide();
    return z ;
}

Tzone ajouterUnitedansZone(Tzone z, Tunite *u)
{
    struct cellule *nouv = malloc(sizeof(struct cellule));
    nouv ->elem = u ;
    nouv -> suiv = z ;
    z = nouv;

    return z ;
}



Tzone rempiler(Tzone source, Tzone* destination)
{
    while(!(estvide(source)))
    {
        *destination = empiler(*destination,tetePile(source));
        source = depiler(source);
    }

    return *destination;
}

Tzone supprimerUnitedansZone(Tzone* z, Tunite *u)
{
    Tzone tmp = creerTzoneVide();
    while(!(estvide(*z)) && tetePile(*z) != u)
    {
        tmp = empiler(tmp,tetePile(*z));
        *z = depiler(*z);
    }
    *z = depiler(*z);

    *z = rempiler(tmp,z);

    return *z;
}


bool UniteEstPresentedansZone(Tzone z, Tunite *u)
{
    if (!estvide(z))
    {
        return true ;
    }
    else return false ;
}



bool UniteAuSolPresente(Tzone *z)
{
    Tzone save = creerTzoneVide() ;
    int reponse = 0 ;
    while (!estVide(*z))
    {
        if ( (tetePile(z)->maposition == sol ))
        {
            reponse = 1 ;
        }
        save = empiler(save,tetePile(*z));
        *z = depiler(*z);
    }
    while ( !estvide(save))
    {
        *z = empiler(*z,tetePile(save));
        save = depiler(save) ;
    }
    return reponse ;
}


bool UniteEnVolPresente(Tzone *z)
{
    Tzone save = creerTzoneVide() ;
    int reponse = 0 ;
    while (!estVide(*z))
    {
        if ( (tetePile(z)->maposition == air ))
        {
            reponse = 1 ;
        }
        save = empiler(save,tetePile(*z));
        *z = depiler(*z);
    }
    while ( !estvide(save))
    {
        *z = empiler(*z,tetePile(save));
        save = depiler(save) ;
    }
    return reponse ;
}


TListePlayer getAllUnitInZone(Tzone *z){

    TListePlayer l = NULL;
    Tzone save = creerTzoneVide();
    while ( !estVide(*z) )
    {

        AjouterUnite(&l,tetePile(*z));
        save = empiler(save,tetePile(*z));
        *z = depiler(*z);
    }
    while ( !estvide(save))
    {
        *z = empiler(*z,tetePile(save));

        save = depiler(save) ;
    }

    return l;
}




Tunite* ElemTzone(Tzone z)
{
    return tetePile(z);
}



int compterZone(Tzone *z){
    int nb = 0 ;
    Tzone temp= *z, save = creerTzoneVide();
    while (!estvide(temp))
    {
        nb += 1;

        save = empiler(save,tetePile(temp));
        temp = depiler(temp);

    }

    while ( !estvide(save))
    {
            temp = empiler(temp,tetePile(save));
            save = depiler(save);
    }
    *z = temp;


    return nb;
}
