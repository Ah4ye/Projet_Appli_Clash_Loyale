

#include "SDL.h"
#include "maSDL.h"    //bibliothèque avec des fonction d'affichage pour le jeu 2048
#include "clashloyal.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>



/*--------- Main ---------------------*/
int main(int argc, char* argv[])
{
    SDL_Window *pWindow;
    SDL_Init(SDL_INIT_VIDEO);

    pWindow = SDL_CreateWindow(
        "Appuyez sur ECHAP pour quitter, S/C ET D/V les gerer les sauvegardes",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        LARGEURJEU*40,
        HAUTEURJEU*40,
        SDL_WINDOW_SHOWN
    );

    SDL_Surface* pWinSurf = SDL_GetWindowSurface(pWindow);  //le sprite qui couvre tout l'écran
    SDL_Surface* pSpriteTour = SDL_LoadBMP("./data/Tour.bmp");  //indice 0 dans tabSprite (via l'enum TuniteDuJeu)
    SDL_Surface* pSpriteTourRoi = SDL_LoadBMP("./data/TourRoi.bmp"); //indice 1
    SDL_Surface* pSpriteArcher = SDL_LoadBMP("./data/Archer.bmp"); //indice 2
    SDL_Surface* pSpriteChevalier = SDL_LoadBMP("./data/Chevalier.bmp"); //indice 3
    SDL_Surface* pSpriteDragon = SDL_LoadBMP("./data/Dragon.bmp"); //indice 4
    SDL_Surface* pSpriteGargouille = SDL_LoadBMP("./data/Gargouille.bmp"); //indice 5
    SDL_Surface* pSpriteEau = SDL_LoadBMP("./data/Eau.bmp"); //indice 6  Ne figure pas dans l'enum TuniteDuJeu
    SDL_Surface* pSpriteHerbe = SDL_LoadBMP("./data/Herbe.bmp"); //indice 7 idem
    SDL_Surface* pSpritePont = SDL_LoadBMP("./data/Pont.bmp"); //indice 8 idem
    SDL_Surface* pSpriteTerre = SDL_LoadBMP("./data/Terre.bmp"); //indice 9 idem

    // ASTUCE : on stocke le sprite d'une unité à l'indice de son nom dans le type enum TuniteDuJeu, dans le tableau TabSprite
    // SAUF pour l'Eau, l''herbe et le pont qui apparaitront en l absence d'unité (NULL dans le plateau) et en foction de certains indices x,y définissant le chemin central
    SDL_Surface* TabSprite[10]={pSpriteTour,pSpriteTourRoi,pSpriteArcher,pSpriteChevalier,pSpriteDragon,pSpriteGargouille,pSpriteEau,pSpriteHerbe,pSpritePont,pSpriteTerre};


    if ( pSpriteTour )  //si le permier sprite a bien été chargé, on suppose que les autres aussi
    {
        TplateauJeu jeu = AlloueTab2D(LARGEURJEU,HAUTEURJEU);
        initPlateauAvecNULL(jeu,LARGEURJEU,HAUTEURJEU);
        affichePlateauConsole(jeu,LARGEURJEU,HAUTEURJEU);

        prepareAllSpriteDuJeu(jeu,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
        maj_fenetre(pWindow);

        //A COMMENTER quand vous en aurez assez de cliquer sur ces popups ^^

      /*  message("Welcome in ClashLoyal","Ceci est un point de depart de votre future interface de votre jeu ClahLoyal");
        message("et fin","ECHAP->quitter, S/C ET D/V les gerer les sauvegardes");*/

        /**********************************************************************/
        /*                                                                    */
        /*              DEFINISSEZ/INITIALISER ICI VOS VARIABLES              */
        /*
        // FIN de vos variables                                                              */
        /**********************************************************************/

        initPlateauAvecNULL ;

        TListePlayer P1 = NULL;
        TListePlayer P2 = NULL;

        AjouterUnite(&P2,creeTourRoi(5,1));
        AjouterUnite(&P1,creeTourRoi(5,17));


       AjouterUnite(&P2,creeTour(5,3)) ;
       AjouterUnite(&P1,creeTour(5,15) );

// Test de l'uniter qui longe la rivière
//        AjouterUnite(&P2,creeChevalier(0,8));


        srand(time(NULL));
        Tunite *achat1 = NULL;
        Tunite *achat2 = NULL;

        int elixirPlayer1 = 5;
        int elixirPlayer2 = 5;
        int tourMana=0;

        int i = 0; // Permet de ralentir le jeu ( aucune modif à faire )


         // boucle principale du jeu

        int cont = 1;
        while ( cont != 0 ){   //VOUS DEVEZ GERER (DETECTER) LA FIN DU JEU -> tourRoiDetruite
                SDL_PumpEvents(); //do events


                 int spawnJoueur1 = rand()%2;
                int spawnJoueur2 = rand()%2;

                 TListePlayer temp = P1;
                TListePlayer temp2 = P2;

                if (i == 1) // Permet de ralentir le jeu ( vous pouvez modifiez tant que i > 0)
                {

                        while ( temp->suiv != NULL) // Verifie qu'aucune unité ne soit morte sinon elle est supprimée
                        {
                            if (temp->pdata->pointsDeVie == 0)
                            {
                                jeu[temp->pdata->posX][temp->pdata->posY]= NULL;
                                supprimerUnite(&P1,temp->pdata);
                            }
                            temp = temp->suiv ;
                        }
                        while ( temp2->suiv != NULL) // Verifie qu'aucune unité ne soit morte sinon elle est supprimée
                        {
                            if (temp2->pdata->pointsDeVie == 0)
                            {
                                jeu[temp2->pdata->posX][temp2->pdata->posY]= NULL;
                                supprimerUnite(&P2,temp2->pdata);
                            }
                            temp2 = temp2->suiv ;
                        }

                        CombatTout(P1,P2);
                        CombatTout(P2,P1);
                        deplacementToutUnitePont(P1,jeu,P2);
                        deplacementToutUnitePont(P2,jeu,P1);






                        if ( tourRoiDetruite(P2) /**|| tourRoiDetruite(player2)==1 */) // Arrete le jeu si le Roi P2 est Mort
                        {
                                printf("Rip le roi 2 \n");
                                message("Fin","Le Joueur 1 Remporte la partie");
                                cont = 0;

                        }
                        if ( tourRoiDetruite(P1) /**|| tourRoiDetruite(player2)==1 */) // Arrete le jeu si le Roi P2 est Mort
                        {
                                printf("Rip le roi 1 \n");
                                message("Fin","Le Joueur 2 Remporte la partie");
                                cont = 0;

                        }
                        else printf("|Ca continue|\n");  // Pas de Roi Mort donc ça continue
                        i = 0 ;

                        if (spawnJoueur1 ==1)
                        {
                            achat1 = AcheteUnite2(&elixirPlayer1);
                            if (achat1->posX !=0 && achat1->posY!=0)AjouterUnite(&P1,achat1);
                        }
                        else if ( spawnJoueur2 ==1)
                        {
                            achat2 = AcheteUnite2(&elixirPlayer2);
                            if (achat2->posX !=0 && achat2->posY!=0)
                            {
                                    AjouterUnite(&P2,achat2);
                                    achat2->posY = 3;
                            }
                        }

                        if (tourMana ==5)
                        {
                            elixirPlayer1 +=1;
                            elixirPlayer2 +=1;
                            tourMana = 0;

                        }else tourMana +=1;

                }
                i = i +1 ;


                PositionnePlayerOnPlateau(P1,jeu);
                PositionnePlayerOnPlateau(P2,jeu);

















                /***********************************************************************/
                /*                                                                     */
                /*                                                                     */
                //APPELEZ ICI VOS FONCTIONS QUI FONT EVOLUER LE JEU
                /*                                                                     */
                /*                                                                     */
                // FIN DE VOS APPELS
                /***********************************************************************/
                //affichage du jeu à chaque tour
                efface_fenetre(pWinSurf);
                prepareAllSpriteDuJeu(jeu,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
                maj_fenetre(pWindow);
                SDL_Delay(150);  //valeur du délai à modifier éventuellement

                //LECTURE DE CERTAINES TOUCHES POUR LANCER LES RESTAURATIONS ET SAUVEGARDES
                const Uint8* pKeyStates = SDL_GetKeyboardState(NULL);


                        TplateauJeu Sjeu  ;
                        TListePlayer S1  ;
                        TListePlayer S2  ;
                        int ElexirS1  ;
                        int ElexirS2  ;



                if ( pKeyStates[SDL_SCANCODE_V] ){
                        /* Ajouter vos appels de fonctions ci-dessous qd le joueur appuye sur D */

                        // APPELEZ ICI VOTRE FONCTION DE SAUVEGARDE/RESTAURATION DEMANDEE
                        message("Sauvegarde","Placer ici votre fonction de restauration/sauvegarde");

                        //Ne pas modifiez les 4 lignes ci-dessous
                        efface_fenetre(pWinSurf);
                        prepareAllSpriteDuJeu(jeu,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
                        maj_fenetre(pWindow);
                        SDL_Delay(300);
                }
                if ( pKeyStates[SDL_SCANCODE_C] ){
                        /* Ajouter vos appels de fonctions ci-dessous qd le joueur appuye sur C */

                        // APPELEZ ICI VOTRE FONCTION DE SAUVEGARDE/RESTAURATION DEMANDEE

                        message("Sauvegarde","Placer ici votre fonction de restauration/sauvegarde");

                        //Ne pas modifiez les 4 lignes ci-dessous
                        efface_fenetre(pWinSurf);
                        prepareAllSpriteDuJeu(jeu,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
                        maj_fenetre(pWindow);
                        SDL_Delay(300);
                }
                if ( pKeyStates[SDL_SCANCODE_D] ){
                        /* Ajouter vos appels de fonctions ci-dessous qd le joueur appuye sur D */


                        jeu = Sjeu ;
                        P1 = S1 ;
                        P2 = S2 ;
                        elixirPlayer1 = ElexirS1 ;
                        elixirPlayer2 =  ElexirS2 ;




                        // APPELEZ ICI VOTRE FONCTION DE SAUVEGARDE/RESTAURATION DEMANDEE
                        message("Sauvegarde","Placer ici votre fonction de restauration/sauvegarde");

                        //Ne pas modifiez les 4 lignes ci-dessous
                        efface_fenetre(pWinSurf);
                        prepareAllSpriteDuJeu(jeu,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
                        maj_fenetre(pWindow);
                        SDL_Delay(300);
                }
                if ( pKeyStates[SDL_SCANCODE_S] ){
                        /* Ajouter vos appels de fonctions ci-dessous qd le joueur appyue sur S */

                        // APPELEZ ICI VOTRE FONCTION DE SAUVEGARDE/RESTAURATION DEMANDEE



                         Sjeu = jeu ;
                         S1 = P1 ;
                         S2 = P2 ;
                         ElexirS1 = elixirPlayer1 ;
                         ElexirS2 = elixirPlayer2 ;


                        message("Sauvegarde","Placer ici votre fonction de restauration/sauvegarde");



                        //Ne pas modifiez les 4 lignes ci-dessous
                        efface_fenetre(pWinSurf);
                        prepareAllSpriteDuJeu(jeu,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
                        maj_fenetre(pWindow);
                        SDL_Delay(300);
                }
                if ( pKeyStates[SDL_SCANCODE_ESCAPE] ){
                        cont = 0;  //sortie de la boucle
                }

        }
        //fin boucle du jeu

        SDL_FreeSurface(pSpriteTour); // Libération de la ressource occupée par le sprite
        SDL_FreeSurface(pSpriteTourRoi);
        SDL_FreeSurface(pSpriteArcher);
        SDL_FreeSurface(pSpriteChevalier);
        SDL_FreeSurface(pSpriteDragon);
        SDL_FreeSurface(pSpriteGargouille);
        SDL_FreeSurface(pSpriteEau);
        SDL_FreeSurface(pSpriteHerbe);
        SDL_FreeSurface(pSpritePont);
        SDL_FreeSurface(pWinSurf);
    }
    else
    {
        fprintf(stdout,"Échec de chargement du sprite (%s)\n",SDL_GetError());
    }

    SDL_DestroyWindow(pWindow);
    SDL_Quit();
    return 0;
}
