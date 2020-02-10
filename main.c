#include <stdio.h>
#include <stdlib.h>
#include "SDL2/SDL.h" //Appel de la bibliothèque SDL2

int main(int argc, char *argv[]) //Modification du main pour inclure le main de la SDL2
{
    //Initialisation d'un pointeur de type fenêtre
    SDL_Window *pWindow=NULL;
    //Initialisation d'un pointeur de type renderer
    SDL_Renderer *pRenderer=NULL;
    //Initialisation d'un pointeur de type texture
    SDL_Texture *pTexture=NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0){
    //SDL_Init permet d'initialiser la SDL
    //SDL_INIT_VIDEO est le sous-système pour l'affichage raphique
    //Si SDL_Init renvoit -1, on affiche l'erreur et on stop le programme
        printf("SDL_Init Error: %s\n",SDL_GetError());;
        return 1;
    }

    pWindow = SDL_CreateWindow("Une fenetre SDL",SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, 600, 600, SDL_WINDOW_RESIZABLE);
        // Création de la fenêtre avec SDL_CreateWindow (titre de la fenêtre, position horizontale, position verticale, largeur, hauteur et les flags
        //SDL_WINDOWS_CENTERED permet de centrer la fenêtre
        //SDL_WINDOW_RESIZABLE permet de changer la taille de la fenêtre pendant l'execution

    if (pWindow == NULL)  //Si la fenêtre est vide, on stop le programme
    {
        printf("Erreur lors de la creation d'une fenetre : %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Delay(3000);  //Pause de 3 secondes pour voir la fenêtre

    SDL_DestroyWindow(pWindow); //Suppression de la fenêtre
    SDL_Quit();  //Fin de la SDL
    return 0;
}
