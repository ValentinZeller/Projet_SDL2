#include "rectangle.h"
#include "cercle.h"
#include "vue.h"
#include "gameobjet.h"

int main(int argc, char *argv[]) //Modification du main pour inclure le main de la SDL2
{
    sdl_manager sdl; //Gestion de la sdl niveau affichage
    SDL_Rect rect = {100,100,240,400},src= {0,0,16,28};
    SDL_Surface *image = NULL;

    //Initialisation de la SDL
    SDLManager_Init(&sdl);

    SDL_SetRenderDrawColor(sdl.pRenderer,255,255,255,1);
    SDL_RenderClear(sdl.pRenderer);

    //Chargement de l'image
    image = IMG_Load("tiles.png");

    //Création de la texture
    sdl.pTexture = SDL_CreateTextureFromSurface(sdl.pRenderer,image);

    int i =0;

    //Sprite animé
    for (i=0;i<8;i++) {
        src.x = i*16;
        //Préparation à l'affichage
        SDL_RenderCopy(sdl.pRenderer,sdl.pTexture,&src,&rect);
        //Raffraichissement
        SDL_RenderPresent(sdl.pRenderer);
        SDL_Delay(400);
    }

    //Arrêt de la SDL
    SDLManager_Stop(&sdl);
    return 0;
}
