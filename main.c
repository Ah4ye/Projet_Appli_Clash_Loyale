//NOM prénom étudiant 1 :
//NOM prénom étudiant 2 :

#include "SDL.h"
#include "maSDL.h"    //bibliothèque avec des fonction d'affichage pour le jeu 2048
#include "clashagain.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "zone.h"



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



        ///********************* NOUVEAUTE ***************************
        TplateauJeuUpgrade jeuUpgrade = AlloueTab2D_Tzone(LARGEURJEU,HAUTEURJEU);//code fourni

        TPlayer player1 = initPlayer(rouge);
        TPlayer player2 = initPlayer(bleu);
        ///********************* fin NOUVEAUTE ***************************

        prepareAllSpriteDuJeu(jeu,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
        maj_fenetre(pWindow);

        //A COMMENTER quand vous en aurez assez de cliquer sur ces popups ^^

        message("Welcome in ClashAgain","Ceci est un point de depart de votre future interface de votre jeu ClashAgain");
        message("et fin","ECHAP->quitter, A,D,C et G pour les achats d'unités (si version humain vs ordi)");

        /**********************************************************************/
        /*                                                                    */
        /*              DEFINISSEZ/INITIALISER ICI VOS VARIABLES              */
         init_P1_P2_Jeu(&player1,&player2);




        /* remarque : player1, player2 et jeuUpgrade  sont definis lignes 52-55

        // FIN de vos variables                                                              */
        /**********************************************************************/

        // boucle principale du jeu
        int cont = 1;



//        Tunite *ab = creeArcher(5,6);
//        Tunite *a = creeGargouille(5,7);
//        Tunite *ac = creeArcher(5,6);



//        AjouterUnite(&player1,creeArcher(5,9));
        AjouterUnite(&player1,creeGargouille(5,12));
//         AjouterUnite(&player1,creeArcher(2,17));

         AjouterUnite(&player2,creeChevalier(5,11));
//         AjouterUnite(&player2,creeGargouille(5,11));


//        AcheteUnite(&player1);
//        PositionnePlayerOnPlateau_Upgade(player1.listeU,jeuUpgrade);
//        PositionnePlayerOnPlateau_Upgade(player2.listeU,jeuUpgrade);
//        afiche(player1.listeU);
//
//        jeu = ConversionEnTplateauJeu(jeuUpgrade);
//        printf("lol");
//
//        printf("je sors de ma conversation \n ");
//        afiche(player1.listeU);
//        AcheteUnite(&player1);
//        afiche(player1.listeU);
        while ( cont != 0 ){   //VOUS DEVEZ GERER (DETECTER) LA FIN DU JEU -> tourRoiDetruite
                SDL_PumpEvents(); //do events

                /****************************** Nouveautés *****************************************/
                /*                                                                     */
                /*                                                                     */
                //APPELEZ ICI VOS FONCTIONS QUI FONT EVOLUER LE JEU
                    jeuUpgrade = AlloueTab2D_Tzone(LARGEURJEU,HAUTEURJEU);
                   initPlateauUPAvecNULL(jeuUpgrade,LARGEURJEU,HAUTEURJEU);
//                    AcheteUnite(&player1);
//                    AcheteUnite(&player2);



                    printf("-------\n");

                    TListePlayer contact = NULL ;

                    PositionnePlayerOnPlateau_Upgade(player2.listeU,jeuUpgrade);
                    PositionnePlayerOnPlateau_Upgade(player1.listeU,jeuUpgrade);

                    jeu = ConversionEnTplateauJeu(jeuUpgrade);
                    AffectationCouleurDeCamp(player1);
                    AffectationCouleurDeCamp(player2);
//                    printf("Couleur %d \n",player1.listeU->pdata->couleurUnite);
//                    contact = quiEstAPortee_Upgrade(jeuUpgrade,player1.listeU->pdata);
//                    printf("----Pill---\n");

//                    AffichePile(&blou);

                    printf("----TLIST---\n");

//                    deplacementToutUnite(player2.listeU,player1.listeU,jeuUpgrade);
//                    deplacementToutUnite(player1.listeU,player2.listeU,jeuUpgrade);
                    combat(player1.listeU,player2.listeU->pdata,jeuUpgrade);
//                    afficheListPlayer(contact);


                //  player1, player2 et jeuUpgrade                                                                    */

                // FIN DE VOS APPELS
                /******************************* fin nouveautés****************************************/

                ///********************* NOUVEAUTE ***************************
//                PositionnePlayerOnPlateau_Upgade( player1.listeU, jeuUpgrade);
                //PositionnePlayerOnPlateau_Upgade( player2.listeU, jeuUpgrade);

//                jeu = ConversionEnTplateauJeu(jeuUpgrade);
                ///********************* fin NOUVEAUTE ***************************

                //affichage du jeu à chaque tour
                efface_fenetre(pWinSurf);
                prepareAllSpriteDuJeu(jeu,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
                maj_fenetre(pWindow);
                SDL_Delay(150);  //valeur du délai à modifier éventuellement

                //LECTURE DE CERTAINES TOUCHES POUR LANCER LES RESTAURATIONS ET SAUVEGARDES
                const Uint8* pKeyStates = SDL_GetKeyboardState(NULL);
                if ( pKeyStates[SDL_SCANCODE_G] ){
                        /* Ajouter vos appels de fonctions ci-dessous qd le joueur appuye sur D */

                        // APPELEZ ICI VOTRE FONCTION DE SAUVEGARDE/RESTAURATION DEMANDEE
                        message("achat unité","Placer ici votre fonction d'achat d'une Gargouille");

                        //Ne pas modifiez les 4 lignes ci-dessous
                        efface_fenetre(pWinSurf);
                        prepareAllSpriteDuJeu(jeu,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
                        maj_fenetre(pWindow);
                        SDL_Delay(300);
                }
                if ( pKeyStates[SDL_SCANCODE_C] ){
                        /* Ajouter vos appels de fonctions ci-dessous qd le joueur appuye sur C */

                        // APPELEZ ICI VOTRE FONCTION DE SAUVEGARDE/RESTAURATION DEMANDEE
                        message("achat unité","Placer ici votre fonction d'achat d'un Chevalier");

                        //Ne pas modifiez les 4 lignes ci-dessous
                        efface_fenetre(pWinSurf);
                        prepareAllSpriteDuJeu(jeu,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
                        maj_fenetre(pWindow);
                        SDL_Delay(300);
                }
                if ( pKeyStates[SDL_SCANCODE_D] ){
                        /* Ajouter vos appels de fonctions ci-dessous qd le joueur appuye sur D */

                        // APPELEZ ICI VOTRE FONCTION DE SAUVEGARDE/RESTAURATION DEMANDEE
                        message("achat unité","Placer ici votre fonction d'achat d'un Dragon?");

                        //Ne pas modifiez les 4 lignes ci-dessous
                        efface_fenetre(pWinSurf);
                        prepareAllSpriteDuJeu(jeu,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
                        maj_fenetre(pWindow);
                        SDL_Delay(300);
                }
                if ( pKeyStates[SDL_SCANCODE_Q] ){
                        /* Ajouter vos appels de fonctions ci-dessous qd le joueur appyue sur S */

                        // APPELEZ ICI VOTRE FONCTION DE SAUVEGARDE/RESTAURATION DEMANDEE
                        message("achat unité","Placer ici votre fonction d'achat d'un Archer");

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
