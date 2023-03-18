#include "SDL.h"
#include "clashloyal.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>


char * tableauNomUniteDuJeuC[] = {"Tour", "TourRoi", "Archer", "Chevalier", "Dragon", "Gargouille"} ; // Appelation pour simplifier ajoute de notre part
//typedef Tunite* ** TplateauJeu;

TplateauJeu AlloueTab2D(int largeur, int hauteur){
    TplateauJeu jeu;
    jeu = (Tunite***)malloc(sizeof(Tunite**)*largeur);
    for (int i=0;i<largeur;i++){
        jeu[i] = (Tunite**)malloc(sizeof(Tunite*)*hauteur);
    }
    return jeu;  //tab2D contenant des pointeurs
}
void initPlateauAvecNULL(TplateauJeu jeu,int largeur, int hauteur){
    for (int i=0;i<largeur;i++){
        for (int j=0;j<hauteur;j++){
            jeu[i][j] = NULL;
        }
    }
}

void affichePlateauConsole(TplateauJeu jeu, int largeur, int hauteur){
    //pour un affichage sur la console, en relation avec enum TuniteDuJeu
    const char* InitialeUnite[6]={"T", "R", "A", "C", "D", "G"};

    printf("\n");
    for (int j=0;j<hauteur;j++){
        for (int i=0;i<largeur;i++){
                // A ne pas donner aux etudiants
            if (jeu[i][j] != NULL){
                    printf("%s",InitialeUnite[jeu[i][j]->nom]);
            }
            else printf(" ");  //cad pas d'unité sur cette case
        }
        printf("\n");
    }
}

Tunite *creeTour(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = tour;
    nouv->cibleAttaquable = solEtAir;
    nouv->maposition = sol;
    nouv->pointsDeVie = 500;
    nouv->vitesseAttaque = 1.0;
    nouv->degats = 100;
    nouv->portee = 3;
    nouv->vitessedeplacement = 0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    nouv->coutEnElixir = 0;
    return nouv;
}
Tunite *creeTourRoi(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = tourRoi;
    nouv->cibleAttaquable = solEtAir;
    nouv->maposition = sol;
    nouv->pointsDeVie = 800;
    nouv->vitesseAttaque = 1.2;
    nouv->degats = 140;
    nouv->portee = 4;
    nouv->vitessedeplacement = 0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    nouv->coutEnElixir = 0;
    return nouv;
}


Tunite *creeArcher(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = archer;
    nouv->cibleAttaquable = solEtAir;
    nouv->maposition = sol;
    nouv->pointsDeVie = 80;
    nouv->vitesseAttaque = 0.7;
    nouv->degats = 120;
    nouv->portee = 3;
    nouv->vitessedeplacement = 1.0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    nouv->coutEnElixir = 2;
    return nouv;
}

Tunite *creeGargouille(int posx, int posy)
{
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = gargouille;
    nouv->cibleAttaquable = solEtAir;
    nouv->maposition = air;
    nouv->pointsDeVie = 300;
    nouv->vitesseAttaque = 0.6;
    nouv->degats = 90;
    nouv->portee = 1;
    nouv->vitessedeplacement = 3.0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    nouv->coutEnElixir = 1;
    return nouv;
}

Tunite *creeDragon(int posx, int posy)
{
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = dragon;
    nouv->cibleAttaquable = solEtAir;
    nouv->maposition = air;
    nouv->pointsDeVie = 200;
    nouv->vitesseAttaque = 1.1;
    nouv->degats = 70;
    nouv->portee = 2;
    nouv->vitessedeplacement = 2.0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    nouv->coutEnElixir = 3;
    return nouv;
}

Tunite *creeChevalier(int posx, int posy)
{
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = chevalier;
    nouv->cibleAttaquable = sol;
    nouv->maposition = sol;
    nouv->pointsDeVie = 400;
    nouv->vitesseAttaque = 1.5;
    nouv->degats = 150;
    nouv->portee = 1;
    nouv->vitessedeplacement = 2.0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    nouv->coutEnElixir = 4;
    return nouv;
}


bool tourRoiDetruite(TListePlayer player)//
{

    if (estVide(player))
    {
        printf("List vide pour tour detruite \n");
    }
    else
    {
        while( player->pdata->nom != tourRoi)
        {

            player = player -> suiv;

        }
    //return true;
      if ( player->pdata->pointsDeVie == 0 )
        {
            return 1 ;
        }
        else return 0 ;

    }
}

void PositionnePlayerOnPlateau(TListePlayer player, TplateauJeu jeu)//
{
    while ( player != NULL)
    {
        if ( jeu[player->pdata->posX][player->pdata->posY]== NULL)
        {
             jeu[player->pdata->posX][player->pdata->posY]= player->pdata;
             printf("unite placee \n");
        }
//        else printf("Case deja occuper par une unite ou autre \n");

        player = player->suiv ;

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


void tri_Bulle(float T[],int taille)
{

    int i;
    float inverse = 0 ;
    int k ;

    for ( k = 0 ; k<= taille ; k++){
        for( i = 0 ; i< taille ; i++){
        if( T[i]>T[i+1]){
            inverse = T[i];
            T[i] = T[i+1];
            T[i+1] = inverse ;
            }
        }
    }
}


TListePlayer vitesseAtk(TListePlayer player)
{
    TListePlayer Rapide = NULL ;
    TListePlayer temp = player ;
    int taille = TailleTListPlayer(temp) ; // Taille de la liste Player
    int v = 0 ;
    float *tab = malloc(sizeof(float)*taille); // allocation d’un tableau de "taille" cases entieres
    TListePlayer temp2 = player ;
    int i ;
    for ( v = 0 ; v < taille ; v ++ ) // Attribution des vitesses d'attaques dans un Tableau tab
    {
        tab[v] = temp2->pdata->vitesseAttaque ;
        temp2 = temp2 ->suiv ;
    }
    tri_Bulle(tab,taille-1); // Tri du Tableau tab en fonction de leur vitesse d'attaque

    TListePlayer temp3 = player ;
    v = 0 ;
    while ( taille > 0  ) //  Boucle visant à remplir une TlistePlayer avec les vitesses triée ( du plus rapide  au plus lent)
    {
        while ( temp3->pdata->vitesseAttaque != tab[v]) // Je cherche l'unité en fonction de la vitesse voulu, ici la plus rapide, donc la première du Tableau tab
        {
            temp3 = temp3->suiv ;
        }
        v = v + 1 ;  // v permet de parcourir tout les valeurs du tableau
        taille -= 1 ;
        AjouterUnite(&Rapide,temp3->pdata);
        temp3 = player ;
    }
    return Rapide ;
}

TListePlayer quiEstAPorteePourDeplacement(TListePlayer player, Tunite *uneUniteDeLautreJoueur)//fonction permettant au unité de s'arreter une fois qu'elles sont à portée d'une autre unité
{

    TListePlayer porter = NULL ;
    while(!estVide(player)) // Boucle permettant d'ajouter les unités qui sont a portée de uneUniteDeLautreJoueur
    {
        double x1=(player->pdata->posX);
        double x2=(uneUniteDeLautreJoueur->posX);

        double y1=(player->pdata->posY);
        double y2=(uneUniteDeLautreJoueur->posY);
        double  d = sqrt( (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)); // Calcule de la distance entre 2 unités en fonctions de leurs position X et Y



        if ( d <= uneUniteDeLautreJoueur->portee ) // si la distance est inférieur ou egale a sa porter je l'ajoute
        {
            AjouterUnite(&porter,player->pdata) ;

        }
        player = player->suiv;
    }


    return porter; // je renvoie la liste des unité a portée de uneUniteDeLautreJoueur

}

TListePlayer quiEstAPorteePourCombat(TListePlayer player, Tunite *uneUniteDeLautreJoueur)//fonction permettant aux unités d'attaquer une fois qu'elles sont à portée d'une autre unité
{

    TListePlayer porter = NULL ;
    while(!estVide(player)) // Boucle permettant d'ajouter uneUniteDeLautreJoueur qui est a portée des l'unités de player
    {
        double x1=(player->pdata->posX);
        double x2=(uneUniteDeLautreJoueur->posX);

        double y1=(player->pdata->posY);
        double y2=(uneUniteDeLautreJoueur->posY);
        double  d = (double)sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)); // Calcule de la distance entre 2 unités en fonctions de leurs position X et Y



        if ( d  <= player->pdata->portee ) // Ligne qui diffère de la précèdente , de cette façons ont regarde les unitées qui peuvent attaquer en même temps uneUniteDeLautreJoueur
        {
            printf(" Valeur de la porter %f \n",d);
            AjouterUnite(&porter,player->pdata) ;

        }
        player = player->suiv;
    }


    return porter;

}


TListePlayer combat(TListePlayer player, Tunite *uneUniteDeLautreJoueur)
{

    TListePlayer fight = NULL ;
    fight =  quiEstAPorteePourCombat(player,uneUniteDeLautreJoueur); // Regarde qui est à portée
    TListePlayer Rapide = vitesseAtk(fight); // Tri la liste des unitées à portée en fonction de leur vitesse d'attaque

    printf("    Liste fight : \n");
     afficheListPlayer (fight); //affiche liste des unitées a portée et qui vont attaquer
     printf("    Liste Rapide : \n"); // affiche liste des unitées a portée + Triée en fonctions de la plus Rapide
    afficheListPlayer (Rapide);

    if (estVide(Rapide))
    {
        printf("ERROR pas d'uniter a porter ou liste player vide \n"); // ici pas de combat
        return 0 ;
    }
    else // debut du combat :
    {

        TListePlayer temp = Rapide ;

        {
            if ( uneUniteDeLautreJoueur->pointsDeVie > 0 ) // On verifie ces points de vie
            {
                int vie = uneUniteDeLautreJoueur->pointsDeVie - temp->pdata->degats ; // On crée une variable vie moins les degats qu'il va subir pour éviter de rentrer dans des valeurs negatives
                if ( temp->pdata->peutAttaquer == 1  && temp->pdata->cibleAttaquable == 1) // Ici L'unité peut attaquer et elle peut attaquer les unitées aèriennes et terrestre
                {

                    if ( vie > 0) // Ici l'unitée va survivre, on applique les modifications et ont renvoie donc la vie restante
                    {
                        uneUniteDeLautreJoueur->pointsDeVie = vie ;
                    }
                    else // Ici l'unitée est morte, je fixe ces points de vie à 0
                    {
                        uneUniteDeLautreJoueur->pointsDeVie = 0 ;
                    }
                }
                else if ( temp->pdata->peutAttaquer == 1 && (temp->pdata->cibleAttaquable == uneUniteDeLautreJoueur->maposition)) //L'unité  ne peut attaquer qu'un seul type d'unitée
                {
                    int vie = uneUniteDeLautreJoueur->pointsDeVie - temp->pdata->degats ;
                    if ( vie > 0)
                    {
                        uneUniteDeLautreJoueur->pointsDeVie = vie ;
                    }
                    else // Ici l'unitée est morte, je fixe ces points de vie à 0
                    {
                        uneUniteDeLautreJoueur->pointsDeVie = 0 ;
                    }
                }
                printf("Uniter reste pdv : %d \n", uneUniteDeLautreJoueur->pointsDeVie); // Les deux printf me permettent de savoir qui à subi les degats et combiens il lui en reste
                printf("L'unite qui a prise les degat : %s \n",tableauNomUniteDuJeuC[uneUniteDeLautreJoueur->nom]);
            }

        }
    }
    return player ;
}


void CombatTout(TListePlayer player,TListePlayer player2) // Permet de faire combattre
{

        TListePlayer temp = player ;

         while (player2->suiv != NULL) // Fait combattre toute les unitées sauf dans le cas ou il reste 1 seule unitée
         {
             combat(temp,player2->pdata);

              player2 = player2->suiv ;
         }

         if (player2->suiv == NULL) // Regle le problème de combat dans le cas ou il n'y a qu'une seule unité
         {
// j'ai été obliger de fonctionner comme cela, car une boucle while avec seulement (player != NULL) donc sans le ("->suiv") ne traite pas toute les unitées
             combat(temp,player2->pdata);
              player2 = player2->suiv ;
         }



}









void deplacementUnitePont(TListePlayer player,TplateauJeu jeu,TListePlayer player2)//Deplace une unitée d'un point A à un point B
{
    TListePlayer temp3 = player ;
    TListePlayer temp = player ;
    while ( temp->pdata->nom != tourRoi) // Je vérifie la position du Roi *point de répère des unitées*
    {
        temp = temp ->suiv ;
    }
    TListePlayer temp2 = player ;

    if ( temp->pdata->posY == 17 )// Si la position du Roi est 17 dans ce cas les unitées se dirige vers le Roi opposé
    {    // Chaque Déplacement vérifie si la case suivant est bien disponible avant de l'occuper
         if ( temp2->pdata->vitessedeplacement > 0.0  && !quiEstAPorteePourDeplacement(player2,temp2->pdata))
            // Si l'unitée peut se déplacer et qu'il n'est pas porter d'une unitée, adverse car sinon il combat, alors il avance
         {
             if(temp2->pdata->maposition == 2  ) // Unitée aerienne
             {
                if ( temp2->pdata->posY != 2  && jeu[temp2->pdata->posX][temp2->pdata->posY-1]== NULL)
                // L'uniter avance tout droit
                {
                    jeu[temp2->pdata->posX][temp2->pdata->posY]= NULL;
                    temp2->pdata->posY = temp2->pdata->posY-1 ;
                }
                if (temp2->pdata->posY <=8 && temp2->pdata->posX !=5 && jeu[temp2->pdata->posX][temp2->pdata->posY-1]== NULL)
                {
            // A partir du moment ou l'unité quitte le camp allié, une fois à la rivière, elle va chercher à rejoindre le chemin principale
                    jeu[temp2->pdata->posX][temp2->pdata->posY]= NULL;
                    if (temp2->pdata->posX>5 && jeu[temp2->pdata->posX-1][temp2->pdata->posY]== NULL)
                    {
                        temp2->pdata->posX = temp2->pdata->posX-1 ;
                    }
                    if (temp2->pdata->posX<5 && jeu[temp2->pdata->posX+1][temp2->pdata->posY]== NULL)
                    {
                        temp2->pdata->posX = temp2->pdata->posX+1 ;
                    }
                }
                if (jeu[temp2->pdata->posX][temp2->pdata->posY]!= NULL) // En cas de blocage l'uniter aerienne va contourner l'obstacle
                {
                    jeu[temp2->pdata->posX][temp2->pdata->posY]= NULL;
                    if (temp2->pdata->posX>5 && jeu[temp2->pdata->posX-1][temp2->pdata->posY]== NULL)// contourne l'obstacle à gauche
                    {
                        temp2->pdata->posX = temp2->pdata->posX-1 ;
                    }
                    else // contourne l'obstacle à droite
                    {
                        temp2->pdata->posX = temp2->pdata->posX+1 ;
                    }
                }
             }
             else // terrestre
             {
               if (temp2->pdata->posX > 5 && temp2->pdata->posX != 5   && jeu[temp2->pdata->posX-1][temp2->pdata->posY]== NULL)
               // L'uniter cherche a rejoindre le chemin principale si elle est du coté gauche
                {
                    jeu[temp2->pdata->posX][temp2->pdata->posY]= NULL;
                    temp2->pdata->posX = temp2->pdata->posX-1 ;
                }
                else if (temp2->pdata->posX < 5 && temp2->pdata->posX != 5  && jeu[temp2->pdata->posX+1][temp2->pdata->posY]== NULL)
                // L'uniter cherche a rejoindre le chemin principale si elle est du coté droit
                {
                    jeu[temp2->pdata->posX][temp2->pdata->posY]= NULL;
                    temp2->pdata->posX = temp2->pdata->posX+1 ;
                }
                if ( (temp2->pdata->posY < 10 || temp2->pdata->posY > 10 && jeu[temp2->pdata->posX][temp2->pdata->posY-1]== NULL)  && jeu[temp2->pdata->posX][temp2->pdata->posY-1]== NULL)// partie basse du plateau, avance
                // L'uniter ne peut traverser la rivière donc elle va longer la rivère jusqu'au pont
                {
                    jeu[temp2->pdata->posX][temp2->pdata->posY]= NULL;
                    temp2->pdata->posY = temp2->pdata->posY-1 ;
                }
                else if (temp2->pdata->posX == 5 && temp2->pdata->posY == 10 && jeu[temp2->pdata->posX][temp2->pdata->posY-1]== NULL  )
                    //On est avant le pont et on passe le pont
                {
                    jeu[temp2->pdata->posX][temp2->pdata->posY]= NULL;
                    temp2->pdata->posY = temp2->pdata->posY-1 ;
                }
             }
         }
    }
    else // Pareil que précèdement mais dans le cas ou le roi se situe au coté opposé
    {
         if ( temp2->pdata->vitessedeplacement > 0.0 && !quiEstAPorteePourDeplacement(player2,temp2->pdata) )
         {
             if(temp2->pdata->maposition == 2  ) // aerienne
             {
                if ( temp2->pdata->posY != 16  && jeu[temp2->pdata->posX][temp2->pdata->posY+1]== NULL)
                {
                    jeu[temp2->pdata->posX][temp2->pdata->posY]= NULL;
                    temp2->pdata->posY = temp2->pdata->posY+1 ;
                }
                if (temp2->pdata->posY >=10 && temp2->pdata->posX !=5)
                {
                    jeu[temp2->pdata->posX][temp2->pdata->posY]= NULL;
                    if (temp2->pdata->posX>5 && jeu[temp2->pdata->posX-1][temp2->pdata->posY]== NULL)
                    {
                        temp2->pdata->posX = temp2->pdata->posX-1 ;
                    }
                    if (temp2->pdata->posX<5 && jeu[temp2->pdata->posX+1][temp2->pdata->posY]== NULL)
                    {
                        temp2->pdata->posX = temp2->pdata->posX+1 ;
                    }
                }
                if (jeu[temp2->pdata->posX][temp2->pdata->posY]!= NULL)
                {
                    jeu[temp2->pdata->posX][temp2->pdata->posY]= NULL;
                    if (temp2->pdata->posX>5 && jeu[temp2->pdata->posX-1][temp2->pdata->posY]== NULL)
                    {
                        temp2->pdata->posX = temp2->pdata->posX-1 ;
                    }
                    else
                    {
                        temp2->pdata->posX = temp2->pdata->posX+1 ;
                    }
                }
             }
             else // terrestre
             {
               if (temp2->pdata->posX > 5    && jeu[temp2->pdata->posX-1][temp2->pdata->posY]== NULL)
                {
                    jeu[temp2->pdata->posX][temp2->pdata->posY]= NULL;
                    temp2->pdata->posX = temp2->pdata->posX-1 ;
                }
                else if (temp2->pdata->posX < 5   && jeu[temp2->pdata->posX+1][temp2->pdata->posY]== NULL)
                {
                    jeu[temp2->pdata->posX][temp2->pdata->posY]= NULL;
                    temp2->pdata->posX = temp2->pdata->posX+1 ;
                }

                if ((temp2->pdata->posY < 8 ||  temp2->pdata->posY > 8) && jeu[temp2->pdata->posX][temp2->pdata->posY+1]== NULL) // partie haute du plateau, avance
                {
                    jeu[temp2->pdata->posX][temp2->pdata->posY]= NULL;
                    temp2->pdata->posY = temp2->pdata->posY+1 ;
                }

                else if (temp2->pdata->posX == 5 && temp2->pdata->posY == 8  && jeu[temp2->pdata->posX][temp2->pdata->posY+1]== NULL )//passe le pont
                {
                    jeu[temp2->pdata->posX][temp2->pdata->posY]= NULL;
                    temp2->pdata->posY = temp2->pdata->posY+1 ;
                }
             }
         }
    }
}


void deplacementToutUnitePont(TListePlayer player,TplateauJeu jeu,TListePlayer player2) // Deplace toutes les unitées
{
         while (player->suiv != NULL)
         {
             float vitesse = player->pdata->vitessedeplacement ; // Applique la vitesse de deplacement

            while ( vitesse > 0)
            {
                          deplacementUnitePont(player,jeu,player2);
                          vitesse = vitesse - 1 ;
            }


             player = player -> suiv ;
         }
}



Tunite *AcheteUnite2(int *elixirEnStockduJoueur) //
{
    srand(time(NULL));
    int i = rand()%2;

    Tunite* temp = NULL;
    if (i==0)
    {
        int leftOrRight  = rand()%2;
        int X = rand()%3; //générateur d'emplacements aléatoires

        if (leftOrRight ==0)X += 2;
        else X += 6;

        int Y = 15;

        int f =rand()%10;

        if (f==0 || f== 1 || f== 2)temp = creeArcher(X,Y);

        if (f==3||f==4 || f== 5)temp = creeChevalier(X,Y);

        if (f==6 ||f== 7)temp = creeDragon(X,Y);

        if (f==8 ||f==9 )temp = creeGargouille(X,Y);

        if (*elixirEnStockduJoueur < temp->coutEnElixir)temp =creeArcher(0,0);

        if(temp->posX != 0 && temp->posY!=0)
        {
            *elixirEnStockduJoueur -= temp->coutEnElixir;
        }
        return temp;


        printf("pipi\n");
    }
    else
    {
        temp =creeArcher(0,0);

    }
    return temp;
}



