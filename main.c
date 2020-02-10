#include <stdio.h>
#include <stdlib.h>
#include "SDL2/SDL.h" //Appel de la biblioth�que SDL2

int main(int argc, char *argv[]) //Modification du main pour inclure le main de la SDL2
{
    //Initialisation d'un pointeur de type fen�tre
    SDL_Window *pWindow=NULL;
    //Initialisation d'un pointeur de type renderer
    SDL_Renderer *pRenderer=NULL;
    //Initialisation d'un pointeur de type texture
    SDL_Texture *pTexture=NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0){
    //SDL_Init permet d'initialiser la SDL
    //SDL_INIT_VIDEO est le sous-syst�me pour l'affichage raphique
    //Si SDL_Init renvoit -1, on affiche l'erreur et on stop le programme
        printf("SDL_Init Error: %s\n",SDL_GetError());;
        return 1;
    }

    return 0;
}
