#include "rectangle.h"
#include "cercle.h"
#include "vue.h"
#include "gameobjet.h"

int main(int argc, char *argv[]) //Modification du main pour inclure le main de la SDL2
{
    sdl_manager sdl; //Gestion de la sdl niveau affichage
    SDL_Event event; //Gestion des events
    SDL_Color drawColor = {255,0,0,255}; //Couleur utilisée pour dessiner

    //Création d'un rectangle
    tRectangle rect1;
    creerRectangle(&rect1,10,10,200,200);

    //Création d'un cercle
    tCercle cercle1;
    creerCercle(&cercle1,150,150,50);

    //Création d'un GameObjet
    tGameObjet objet1;
    creerGameObjet(&objet1,10,50,"server-icon.bmp");

    //Initialisation de la SDL
    SDLManager_Init(&sdl);

    //Dessin d'un rectangle puis remplissage
    SDL_DrawRectangle(sdl.pRenderer,getPosXRectangle(&rect1),getPosYRectangle(&rect1),getLargeurRectangle(&rect1),getHauteurRectangle(&rect1),500,drawColor);
    SDL_DrawFilledRectangle(sdl.pRenderer,getPosXRectangle(&rect1),getPosYRectangle(&rect1),getLargeurRectangle(&rect1),getHauteurRectangle(&rect1),500,drawColor);

    //Reset de l'affichage
    SDLManager_ClearScreen(sdl.pRenderer);

    //Dessin d'un cercle puis remplissage
    SDL_DrawCircle(sdl.pRenderer,cercle1.nCentreX,cercle1.nCentreY,cercle1.nRadius,500,drawColor);
    SDL_DrawFilledCircle(sdl.pRenderer,cercle1.nCentreX,cercle1.nCentreY,cercle1.nRadius,500,drawColor);

    //Réduction de la taille du rectangle
    setLargeurRectangle(&rect1,10);
    setHauteurRectangle(&rect1,10);

    //Boucle principale
    while (1) {
        //Gestion des events
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                //Si l'utilisateur clique, fin du programme
                case SDL_MOUSEBUTTONDOWN :
                        //Arrêt de la SDL
                        SDLManager_Stop(&sdl);
                        return 0;
                        break;
            }
        }
        SDLManager_ClearScreen(sdl.pRenderer);

        //Déplacement d'une image(gameobjet) et d'un rectangle à la position de la souris dans la fenêtre
        setPositionGameObjet(&objet1,event.motion.x,event.motion.y);
        SDLManager_DisplayImage(&sdl,getSpriteGameObjet(&objet1),getPosXGameObjet(&objet1),getPosYGameObjet(&objet1),0);
        setPositionRectangle(&rect1,event.motion.x,event.motion.y);
        SDL_DrawFilledRectangle(sdl.pRenderer,getPosXRectangle(&rect1),getPosYRectangle(&rect1),getLargeurRectangle(&rect1),getHauteurRectangle(&rect1),0,drawColor);

    }
}
