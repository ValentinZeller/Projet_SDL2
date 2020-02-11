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

    //Initialisation d'un rectangle {position horizontale, position verticale, largeur, hauteur)
    SDL_Rect rect = {10,10,200,200};
    //Initialisation d'un point {position horizontale, position verticale}
    SDL_Point point = {15,30};

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

    if (pWindow == NULL) { //Si la fenêtre est vide, on stop le programme
        printf("Erreur lors de la creation d'une fenetre : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    pRenderer = SDL_CreateRenderer(pWindow,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    //Création du renderer avec SDL_CreateRenderer(pointeur de fenêtre,index, flags)
    //l'index -1 permet de sélectionner le premier driver qui gére le rendu
    //SDL_RENDERER_ACCELERATED permet d'utiliser l'accélération matérielle
    //SDL_RENDERER_PRESENTVSYNC permet de synchroniser le renderer sur le taux de raffraichissement

    //Il est aussi possible d'utiliser SDL_CreateWindowAndRenderer pour créer la fenêtre et son renderer

    if (pRenderer == NULL) {//Si le renderer est vide, on stop le programme
        printf("Erreur lors de la création du render : %s\n",SDL_GetError());
        return EXIT_FAILURE;

    }
    SDL_SetRenderDrawColor(pRenderer, 0,0,255,255);//Définit une couleur (ici le bleu)
    SDL_RenderClear(pRenderer);//Applique la couleur sur tout l'écran


    SDL_RenderPresent(pRenderer);//Fait un rendu
    SDL_Delay(3000);  //Pause de 3 secondes pour voir la fenêtre


    SDL_DestroyRenderer(pRenderer); //Suppression du renderer
    SDL_DestroyWindow(pWindow); //Suppression de la fenêtre
    SDL_Quit();  //Fin de la SDL
    return 0;
}
