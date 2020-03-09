#include "rectangle.h"
#include "cercle.h"
#include "vue.h"
#include "gameobjet.h"

int main(int argc, char *argv[]) //Modification du main pour inclure le main de la SDL2
{
    sdl_manager sdl; //Gestion de la sdl niveau affichage
    SDL_Rect rect = {0,0,240,400};
    SDL_Surface *image = NULL;

    //Initialisation de la SDL
    SDLManager_Init(&sdl);

    //Chargement de l'image
    image = IMG_Load("minecraft.png");

    //Création de la texture
    sdl.pTexture = SDL_CreateTextureFromSurface(sdl.pRenderer,image);

    //Préparation à l'affichage
    SDL_RenderCopy(sdl.pRenderer,sdl.pTexture,NULL,&rect);

    //Raffraichissement
    SDL_RenderPresent(sdl.pRenderer);

    SDL_Delay(2500);

    //Arrêt de la SDL
    SDLManager_Stop(&sdl);
    return 0;
}
