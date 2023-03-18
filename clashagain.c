#include "SDL.h"
#include "clashagain.h"
#include <stdio.h>
#include <stdlib.h>

///********************* NOUVEAUTE ***************************
#include "zone.h"
#include "types.h"
///********************* NOUVEAUTE ***************************

//types utilisés:
typedef Tunite* ** TplateauJeu;
typedef Tzone ** TplateauUpgrade;

/// **** AFFICAHGE ******

void PositionnePlayerOnPlateau_Upgade(TListePlayer player, TplateauJeuUpgrade jeuUpgrade){

    while(player != NULL ){
        Tunite *unit = (player->pdata) ;
        Tzone zone = jeuUpgrade[unit->posX][unit->posY];
        zone = ajouterUnitedansZone(zone,unit) ;
        jeuUpgrade[unit->posX][unit->posY] = zone ;
        player = player -> suiv ;
    }
}


TplateauJeu ConversionEnTplateauJeu(TplateauUpgrade jeuEncours){
    TplateauJeu jeu = AlloueTab2D(LARGEURJEU,HAUTEURJEU);
    int L , H ;
    for(L=0; L<LARGEURJEU;L++){
        for(H=0; H<HAUTEURJEU ; H++){

            if( estvide(jeuEncours[L][H]) )
                jeu[L][H] = NULL ;

            else {
                    TListePlayer T = NULL ;
                    T = getAllUnitInZone(&jeuEncours[L][H]);

                    if( UniteEnVolPresente(&jeuEncours[L][H])){
                            TListePlayer p = getAllUnitInZone(jeuEncours[L][H]);
                            TListePlayer p2 = p ;
                            while ( p->pdata->maposition != air )
                            {
                               p = p -> suiv ;
                            }
                            jeu[L][H] = p->pdata ;
                            p = p2;
                    // sinon prendre la premiere unité terreste
                    }
                      else
                        { jeu[L][H] = T->pdata ;}
            }
        }
    }
    return jeu;
}

void initPlateauUPAvecNULL(TplateauJeuUpgrade jeu,int largeur, int hauteur){
    for (int i=0;i<largeur;i++){
        for (int j=0;j<hauteur;j++){
            jeu[i][j] = creerTzoneVide();
        }
    }

}

TplateauJeuUpgrade AlloueTab2D_Tzone(int largeur, int hauteur){
    TplateauJeuUpgrade jeu;
    jeu = (Tzone**)malloc(sizeof(Tzone*)*largeur);
    for (int i=0;i<largeur;i++){
        jeu[i] = (Tzone*)malloc(sizeof(Tzone)*hauteur);
    }
    return jeu;  //tab2D contenant des pointeurs
}

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


/// **** init PLAYER/LISTE  BOOL endgame ****
TListePlayer initTlistPlayer(){
    TPlayer bob = initPlayer(rouge);
    return bob.listeU;
}
TPlayer initPlayer(Tcouleur couleur){
    TPlayer p;
    p.couleurJoueur = couleur ;
    p.elixir = 6 ;
    p.listeU = NULL ;

    return p;
}
void init_P1_P2_Jeu(TPlayer *player1, TPlayer *player2){


    AjouterUnite(&( (*player1).listeU),creeTourRoi(5,1));
    AjouterUnite(&( (*player1).listeU),creeTour(5,3));
    AjouterUnite(&( (*player2).listeU),creeTourRoi(5,17));
    AjouterUnite(&( (*player2).listeU),creeTour(5,15));

}
bool tourRoiDetruite(TListePlayer player){
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




/// **** uniter ***
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
    nouv->degats = 120;
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
Tunite *creeGargouille(int posx, int posy){
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
Tunite *creeDragon(int posx, int posy){
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
Tunite *creeChevalier(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = chevalier;
    nouv->cibleAttaquable = sol;
    nouv->maposition = sol;
    nouv->pointsDeVie =400;
    nouv->vitesseAttaque = 1.5;
    nouv->degats = 250;
    nouv->portee = 1;
    nouv->vitessedeplacement = 2.0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    nouv->coutEnElixir = 4;
    return nouv;
}

/// **** gerer unite ****
void AjouterUnite(TListePlayer *player, Tunite *nouvelleUnite){
    struct T_cell *nouv = malloc(sizeof(struct T_cell));
    nouv ->pdata = nouvelleUnite ;
    nouv -> suiv = *player ;
    *player = nouv;
}
void AcheteUnite(TPlayer *player){

    Tunite *U1= NULL ;
    Tcouleur camp = player->couleurJoueur ;
    int elixirEnStockduJoueur = player->elixir ;
    int nombreAlea = rand()%100 +1 ;
    printf("\n %d   %d",nombreAlea , elixirEnStockduJoueur);
    if(nombreAlea>50){   // une chance sur 2 d'invoquer une troupe

        switch(elixirEnStockduJoueur){ // tirage aleatoire des cartes qu'il peut jouer par rapport à son nombre d'elixir et choisit si
                                        // apparait à gauche ou droite de la tour ( 3 cases max )
            case 0:{
                break;}

            case 1:{  // Seulement gargouille car pas + d elixir
                elixirEnStockduJoueur=elixirEnStockduJoueur -1;

                if (nombreAlea<=75){  // tirage pour savoir si on la met à droite ou gauche
                    U1 = creeGargouille((rand()%3 +2),3);//cree une gargouille dans les cases à gauche de la tour
                }else {
                    U1 = creeGargouille(rand()%3 +6,3);//cree une gargouille dans les cases à droite de la tour
                }
                U1->couleurUnite = camp;
                AjouterUnite(player,U1);
                player->elixir = elixirEnStockduJoueur ; //on retourne l'unité créé
                break;//on sort du switch, une unité a été créé
            }

            case 2:{

                int nombreAlea2 = rand()%100 +1;
                if(nombreAlea2>50){//premier tirage, avec cet elixir seul l'archer et la gargouille peuvent etre créés, 50% de chance pour les deux
                    elixirEnStockduJoueur=elixirEnStockduJoueur -2;

                    if (nombreAlea2<=75){//même tirage pour droite et gauche pour l'archer
                        U1 = creeArcher(rand()%3 +2,3);
                    }
                   else { U1 = creeArcher(rand()%3 +6,3); }
                }
                else{
                    elixirEnStockduJoueur=elixirEnStockduJoueur -1;

                    if (nombreAlea2<=25){//même tirage pour droite et gauche pour la gargouille
                        U1=creeGargouille(rand()%3 +2,3);
                }
                else{ U1 = creeGargouille(rand()%3 +6,3); }
                }
            U1->couleurUnite = camp;
            AjouterUnite(player,U1);
            player->elixir = elixirEnStockduJoueur ;
            break;
            }

            case 3:{//3 unites possibles avec 3 elixirs
                int nombreAlea3 = rand()%30 + 1;// 1 chance sur 3 pour chaque unite d'etre créé

                if(nombreAlea3>20){
                    elixirEnStockduJoueur=elixirEnStockduJoueur -3;

                    if (nombreAlea3<=25){
                            U1 = creeDragon(rand()%3 +2,3);//creation du dragon à gauche de la tour
                    }
                    else { U1 = creeDragon(rand()%3 +6,3); }//creation du dragon à droite de la tour
                }
                else if(nombreAlea3>10){
                    elixirEnStockduJoueur=elixirEnStockduJoueur -2;
                    if (nombreAlea3<=15){
                            U1 = creeArcher(rand()%3 +2,3);
                    }
                    else { U1 = creeArcher(rand()%3 +6,3); }
                }
                else{
                    elixirEnStockduJoueur=elixirEnStockduJoueur -1;
                    if (nombreAlea3<=5){
                        U1=creeGargouille(rand()%3 +2,3);
                    }
                    else { U1 = creeGargouille(rand()%3 +6,3); }
                }
            U1->couleurUnite = camp;
            AjouterUnite(player,U1);
            player->elixir = elixirEnStockduJoueur ;
            break;
            }

            default :{// avec 4 elixirs ou plus, on peut creer toutes les unités.
                printf("la");
                int nombreAlea4 = rand()%200 +1;

                if(nombreAlea4<=50){// 1 chances sur 4
                    elixirEnStockduJoueur=elixirEnStockduJoueur -1;
                    if (nombreAlea4<=25){
                        U1=creeGargouille(rand()%3 +2,3);
                    }
                    else { U1 = creeGargouille(rand()%3 +6,3); }
                }

                if(nombreAlea4>50 && nombreAlea4<=100){
                    elixirEnStockduJoueur=elixirEnStockduJoueur -2;
                    if (nombreAlea4<=75){
                            U1 = creeArcher(rand()%3 +2,3);
                    }
                    else { U1 = creeArcher(rand()%3 +6,3); }
                }

                if(nombreAlea4>100 && nombreAlea4<=150){
                    elixirEnStockduJoueur=elixirEnStockduJoueur -3;
                    if (nombreAlea4<=125){
                            U1 = creeDragon(rand()%3 +2,3);
                    }
                    else { U1 = creeDragon(rand()%3 +6,3);}
                }
                if(nombreAlea4>150){
                    elixirEnStockduJoueur=elixirEnStockduJoueur -4;

                    if (nombreAlea4<=175){//on peut creer le chevalier car + de 4 elixirs.
                        U1=creeChevalier(rand()%3 +2,3);
                    }
                    else{ U1 = creeChevalier(rand()%3 +6,3); }
                }
                printf("pas la ");
                U1->couleurUnite = camp;
                AjouterUnite(player,U1);
                afiche(player->listeU);
                player->elixir = elixirEnStockduJoueur ;
                break;
            }
        }
    }
    else{ } // idem normalement ici return NULL;
}
void afiche(TListePlayer P){
    printf("\n [ ");
    while (P!=NULL){
        printf(" %d et pv : %d peut : %p posXY : %d  %d \n", P->pdata->nom,P->pdata->pointsDeVie,P->pdata,P->pdata->posX,P->pdata->posY);
        P=P->suiv;
    }
    printf(" ] \n");
}


/// **** partie ***

bool UniterRapide(Tunite* A, Tunite *B)
{

   return A->vitesseAttaque > B->vitesseAttaque ;
}

bool UniterVie(Tunite* A, Tunite *B)
{
   return A->pointsDeVie > B->pointsDeVie ;
}



void TriParAttribut(TListePlayer player, bool (*fcomp)(Tunite* A, Tunite *B)){
    TListePlayer encours = player ;
    TListePlayer encour2 = player ;
    TListePlayer temp = NULL ;
   for (encours ; !estVideTlist(encours)  ; encours= getptrNextCell(encours))
   {

        temp = encours ;
        encour2 = encours ;
       for (encour2 ; !estVideTlist(encour2) ; encour2 = getptrNextCell(encour2) )
       {
            if ( fcomp( temp->pdata , encour2->pdata) )
           {
                temp = encour2 ;
           }
       }
        swapPtrData(encours,temp);
   }
}


TListePlayer quiEstAPortee_Upgrade(TplateauJeuUpgrade jeuEncours, Tunite *uneUniteDeLautreJoueur){
        int porterMax = uneUniteDeLautreJoueur->portee;
        int i = porterMax ;
        int k = porterMax ;

        int X = uneUniteDeLautreJoueur->posX ;
        int Y = uneUniteDeLautreJoueur->posY ;
        TListePlayer Portee = NULL;
        while (i >= 0  )
        {
            if ( X+i <= LARGEURJEU )
                {
                    if( i > 0 ){ Portee = ConcatTListPlayer(getAllUnitInZone(&jeuEncours[X+i][Y]),Portee);}
                    while ( k > 0)
                    {
                        if ( uneUniteDeLautreJoueur->posY+k <= HAUTEURJEU )
                        {
                            Portee = ConcatTListPlayer(getAllUnitInZone(&jeuEncours[X+i][Y+k]),Portee);
                        }

                        if ( uneUniteDeLautreJoueur->posY-k >= 0 && i > 0 ) // proposition avec i >0 pas de doublons
                        {
                            Portee = ConcatTListPlayer(getAllUnitInZone(&jeuEncours[X+i][Y-k]),Portee);//doublon
                        }
                        k -= 1 ;
                    }
                    k = porterMax ;
                }
             if ( X-i >= 0 )
             {
                    if( i > 0 ){Portee = ConcatTListPlayer(getAllUnitInZone(&jeuEncours[X-i][Y]),Portee);}
                     //Ligne droite i
                    while ( k > 0)
                    {
                        if ( Y-k >= 0 )
                        {
                                Portee = ConcatTListPlayer(getAllUnitInZone(&jeuEncours[X-i][Y-k]) ,Portee);//doublon
                        }
                        if ( Y+k <= HAUTEURJEU && i>0 )// proposition avec i > 0 pas de doublon
                        {
                                Portee = ConcatTListPlayer(getAllUnitInZone(&jeuEncours[X-i][Y+k]),Portee);
                        }
                        k -= 1 ;
                    }
                    k = porterMax ;
             }
                i -= 1 ;
        }

        TListePlayer PorterIci = getAllUnitInZone(&jeuEncours[X][Y]);
        TListePlayer temp = PorterIci ;
//        TListePlayer PorterIci = NULL ;

        while ( !estVideTlist(temp))
        {
            if (temp ->pdata == uneUniteDeLautreJoueur )
            {
                supprimerUnite(&PorterIci, uneUniteDeLautreJoueur);
            }
            temp =temp->suiv ;
        }
        Portee = ConcatTListPlayer(PorterIci,Portee);
        return Portee ;
}

void combat(TListePlayer player, Tunite *uneUniteDeLautreJoueur ,TplateauJeuUpgrade jeuEncours ){//Rajoute de TplateauUpgrade pour utiliser la fnct quiEstAPorter
    // Liste du Plus Rapide
//    TListePlayer ListeVitesseATK = initTlistPlayer();
//    ListeVitesseATK = quiEstAPortee_Upgrade(jeuEncours,uneUniteDeLautreJoueur);
//    TriParAttribut(ListeVitesseATK,UniterRapide);

    //Liste en fonctions des points de vie (PDV)
    TListePlayer ListePDV = NULL;
    ListePDV = quiEstAPortee_Upgrade(jeuEncours,uneUniteDeLautreJoueur);
    TriParAttribut(ListePDV,UniterVie);
    afficheListPlayer(ListePDV);
     //PDV de la Cible


    if ( uneUniteDeLautreJoueur->peutAttaquer == 1 && ( uneUniteDeLautreJoueur->peutAttaquer == 1 ))
    {
        int vie = ListePDV->pdata->pointsDeVie - uneUniteDeLautreJoueur->degats ;
        if ( vie > 0 )
        {
            ListePDV->pdata->pointsDeVie = vie ;
        }
        else
        {
            ListePDV->pdata->pointsDeVie = 0 ;
//            supprimerUnite(&ListePDV,ListePDV->pdata);
        }
    }
     else if ( uneUniteDeLautreJoueur->peutAttaquer == 1 && (ListePDV->pdata->maposition == uneUniteDeLautreJoueur->cibleAttaquable) )
     {
        int vie = ListePDV->pdata->pointsDeVie - uneUniteDeLautreJoueur->degats ;
        if ( vie > 0 )
        {
            // Faire une boucle while pour trouver l'uniter a qui affecter la vie apres avoir subis les degats
            ListePDV->pdata->pointsDeVie = vie ;
        }
        else
        {
            ListePDV->pdata->pointsDeVie = 0 ;
//            supprimerUnite(&ListePDV,ListePDV->pdata);

        }
     }
        printf("Uniter qui tape : %d \n", uneUniteDeLautreJoueur->nom );
        printf("Uniter qui est frapper : %d \n", ListePDV->pdata->nom );
      printf("Uniter reste pdv : %d \n", ListePDV->pdata->pointsDeVie);
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

void deplacement(TListePlayer player,TListePlayer player2,TplateauJeuUpgrade jeuEncours)//Deplace une unitée d'un point A à un point B
{

    TListePlayer temp = player ;
    TListePlayer temp2 = player ;

    if ( temp->pdata->couleurUnite == 1 )
    {
         if ( temp2->pdata->vitessedeplacement > 0.0   )
         {
             if(temp2->pdata->maposition == 2  ) // Unitée aerienne
             {
                if ( temp2->pdata->posY != 2 )
                // L'uniter avance tout droit
                {
                    temp2->pdata->posY = temp2->pdata->posY-1 ;
                }
                if (temp2->pdata->posY <=8 && temp2->pdata->posX !=5 )
                {
            // A partir du moment ou l'unité quitte le camp allié, une fois à la rivière, elle va chercher à rejoindre le chemin principale
                    if (temp2->pdata->posX>5 )
                    {
                        temp2->pdata->posX = temp2->pdata->posX-1 ;
                    }
                    if (temp2->pdata->posX<5 )
                    {
                        temp2->pdata->posX = temp2->pdata->posX+1 ;
                    }
                }
             }
             else // terrestre
             {
               if (temp2->pdata->posX > 5 && temp2->pdata->posX != 5  )
               // L'uniter cherche a rejoindre le chemin principale si elle est du coté gauche
                {
                    temp2->pdata->posX = temp2->pdata->posX-1 ;
                }
                else if (temp2->pdata->posX < 5 && temp2->pdata->posX != 5 )
                // L'uniter cherche a rejoindre le chemin principale si elle est du coté droit
                {
                    temp2->pdata->posX = temp2->pdata->posX+1 ;
                }
                if ( ((temp2->pdata->posY < 10 || temp2->pdata->posY > 10) ) && temp2->pdata->posY > 2 )// partie basse du plateau, avance
                // L'uniter ne peut traverser la rivière donc elle va longer la rivère jusqu'au pont
                {
                    temp2->pdata->posY = temp2->pdata->posY-1 ;
                }
                else if (temp2->pdata->posX == 5 && temp2->pdata->posY == 10   )
                    //On est avant le pont et on passe le pont
                {
                    temp2->pdata->posY = temp2->pdata->posY-1 ;
                }
             }
         }
    }
    else // Pareil que précèdement mais dans le cas ou le roi se situe au coté opposé
    {
         if ( temp2->pdata->vitessedeplacement > 0.0 )
         {
             if(temp2->pdata->maposition == 2  ) // aerienne
             {
                if ( temp2->pdata->posY != 16  )
                {
                    temp2->pdata->posY = temp2->pdata->posY+1 ;
                }
                if (temp2->pdata->posY >=10 && temp2->pdata->posX !=5)
                {
                    if (temp2->pdata->posX>5 )
                    {
                        temp2->pdata->posX = temp2->pdata->posX-1 ;
                    }
                    if (temp2->pdata->posX<5 )
                    {
                        temp2->pdata->posX = temp2->pdata->posX+1 ;
                    }
                }
             }
             else // terrestre
             {
               if (temp2->pdata->posX > 5    )
                {
                    temp2->pdata->posX = temp2->pdata->posX-1 ;
                }
                else if (temp2->pdata->posX < 5   )
                {
                    temp2->pdata->posX = temp2->pdata->posX+1 ;
                }
                if (  ((temp2->pdata->posY < 8 ||  temp2->pdata->posY > 8)) &&   temp2->pdata->posY < 16   ) // partie haute du plateau, avance
                {
                    temp2->pdata->posY = temp2->pdata->posY+1 ;
                }
                else if (temp2->pdata->posX == 5 && temp2->pdata->posY == 8   )//passe le pont
                {
                    temp2->pdata->posY = temp2->pdata->posY+1 ;
                }
             }
         }
    }
}


void deplacementToutUnite(TListePlayer player,TplateauJeuUpgrade jeuEncours ,TListePlayer player2) // Deplace toutes les unitées
{
         while (player->suiv != NULL)
         {
//             float vitesse = player->pdata->vitessedeplacement ; // Applique la vitesse de deplacement
            float vitesse = 1 ; // Sans Application de la vitesse de deplacement
            while ( vitesse > 0)
            {
                          deplacement(player,jeuEncours,player2);
                          vitesse = vitesse - 1 ;
            }
             player = player -> suiv ;
         }
}



//TListePlayer AllUnite(TplateauJeuUpgrade jeuEncours , int posX , int posY){
//
//    int porterMax = 4;
//    int x,y;
//
//    TListePlayer Portee = initTlistPlayer();
//    for(x=posX-porterMax; x<=porterMax+posX;x++){
//            for(y=posY-porterMax;y<=porterMax+posX-1;y++){
//                if ( (x  >= 0 && y  >= 0) && ( x <= HAUTEURJEU && y <=LARGEURJEU) && (x!=posX || y!=posY )){
//
//                    if ( !estvide(jeuEncours[x][y])){
//
//                            AjouterUnite(&Portee,jeuEncours[x][y]->elem);
//                            Portee->pdata->couleurUnite = jeuEncours[x][y]->elem->couleurUnite ;
//                    }
//                }
//            }
//        }
//    return Portee;
//}
//TListePlayer quiEstAPortee_Upgrade(TplateauJeuUpgrade jeuEncours, Tunite *uneUniteDeLautreJoueur){
//
//        TListePlayer save = initTlistPlayer();
//        Tcouleur camp = uneUniteDeLautreJoueur->couleurUnite ;
//        TListePlayer Portee = AllUnite(jeuEncours,uneUniteDeLautreJoueur->posX,uneUniteDeLautreJoueur->posY);
//        printf("porter : \n");
//        afiche(Portee);
//        while (Portee!=NULL){
//            Tunite *unit = Portee->pdata ;
//            if(Portee->pdata->couleurUnite != camp && Aporter(unit,uneUniteDeLautreJoueur)){
//                printf("oui\n\n");
//                AjouterUnite(&save,unit);
//            }
//            Portee = Portee->suiv;
//        }
//        afiche(save);
//        return save ;
//}

//bool Aporter(Tunite *unite, Tunite *uniteAutreJoueur){
//
//    double DistanceX = (unite->posX) -  uniteAutreJoueur->posX;
//    double DistanceY = (unite->posY) -  uniteAutreJoueur->posY;
//
//
//    double DistanceFinal = sqrt( (DistanceX*DistanceX)  +  (DistanceY*DistanceY)  );
//    // calcule la distance entre 2 unités puis si cette distance est <= a la porté et qu'il peut l'attaquer  alors renvoie true
//    if (  unite->portee >= DistanceFinal && ((unite->cibleAttaquable == solEtAir && (uniteAutreJoueur->maposition== air   || uniteAutreJoueur->maposition== sol)) || (unite->cibleAttaquable == sol && uniteAutreJoueur->maposition== sol) ) )
//        return true;
//    else {return false;}}

