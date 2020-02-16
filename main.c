#include <stdio.h>
#include <stdlib.h>
#include "SDL2/SDL.h" //Appel de la bibliothèque SDL2

void SDL_DrawOctants(SDL_Renderer *pRenderer, int nCentreX,int nCentreY, int x, int y);
void SDL_DrawCircle(SDL_Renderer * pRenderer, int nCentreX, int nCentreY, int nRadius);
void SDL_DrawFilledCircle(SDL_Renderer* pRenderer, int nCentreX,int nCentreY, int nRadius);

int main(int argc, char *argv[]) //Modification du main pour inclure le main de la SDL2
{
    //Initialisation d'un pointeur de type fenêtre
    SDL_Window *pWindow=NULL;
    //Initialisation d'un pointeur de type renderer
    SDL_Renderer *pRenderer=NULL;

    //Initialisation d'un rectangle {position horizontale, position verticale, largeur, hauteur)
    SDL_Rect rect = {0,0,100,100};
    //Initialisation d'un point {position horizontale, position verticale}
    SDL_Point point = {0,0};


    //Initialisation d'un pointeur de type surface
    SDL_Surface *pSurface= NULL;

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

    pSurface = SDL_CreateRGBSurface(0,100,100,32,0,0,0,0);
    //Création de la surface avec SDL_CreateRGBSurface

    pSurface = SDL_GetWindowSurface(pWindow);
    //Surface de la fenêtre

    if(pSurface == NULL) {
        printf("La creation de la surface a echoue : %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    Uint32 color = SDL_MapRGB(pSurface->format,255,100,0);
    //Couleur qui va être apppliquée sur la surface, ici du orange

    SDL_FillRect(pSurface,NULL, color);
    //SDL_FillRect permet de remplir la surface d'une couleur

    SDL_UpdateWindowSurface(pWindow);
    //Mise à jour de l'affichage

    SDL_Delay(1500);

    SDL_FreeSurface(pSurface);
    SDL_DestroyRenderer(pRenderer); //Suppression du renderer
    SDL_DestroyWindow(pWindow); //Suppression de la fenêtre
    SDL_Quit();  //Fin de la SDL
    return 0;
}

//Dessin des 8 points (octants) de l'algorime de Bresenhams pour le circle
void SDL_DrawOctants(SDL_Renderer *pRenderer, int nCentreX,int nCentreY, int x, int y) {
    SDL_RenderDrawPoint(pRenderer,nCentreX+x,nCentreY+y);
    SDL_RenderDrawPoint(pRenderer,nCentreX-x,nCentreY+y);
    SDL_RenderDrawPoint(pRenderer,nCentreX+x,nCentreY-y);
    SDL_RenderDrawPoint(pRenderer,nCentreX-x,nCentreY-y);
    SDL_RenderDrawPoint(pRenderer,nCentreX+y,nCentreY+x);
    SDL_RenderDrawPoint(pRenderer,nCentreX-y,nCentreY+x);
    SDL_RenderDrawPoint(pRenderer,nCentreX+y,nCentreY-x);
    SDL_RenderDrawPoint(pRenderer,nCentreX-y,nCentreY-x);
}

//Dessin d'un cercle à l'aide de l'Algorithme de Bresenhams
void SDL_DrawCircle(SDL_Renderer * pRenderer, int nCentreX, int nCentreY, int nRadius) {
    int x = 0;
    int y = 0;
    int d;
    d = 3 - 2*nRadius;
    y = nRadius;

    SDL_DrawOctants(pRenderer,nCentreX,nCentreY,x,y);
    while (y >= x) {
        x++;
        if (d > 0) {
            y--;
            d = d +  4*(x-y)+10;
        } else {
            d = d + 4*x + 6;
        }
        SDL_DrawOctants(pRenderer,nCentreX,nCentreY,x,y);
    }
}

//Dessin d'un cercle rempli à l'aide de l'Algorithme de Bresenhams
void SDL_DrawFilledCircle(SDL_Renderer* pRenderer, int nCentreX,int nCentreY, int nRadius){
    int x = 0;
    int y = 0;
    int d;
    d = 3 - 2*nRadius;
    y = nRadius;

    SDL_DrawOctants(pRenderer,nCentreX,nCentreY,x,y);
    //Lignes horizontales entre les octants
    SDL_RenderDrawLine(pRenderer,nCentreX - x,nCentreY - y, nCentreX + x,nCentreY - y);
    SDL_RenderDrawLine(pRenderer,nCentreX - y,nCentreY + x, nCentreX + y,nCentreY + x);
    SDL_RenderDrawLine(pRenderer,nCentreX - y,nCentreY - x, nCentreX + y,nCentreY - x);
    SDL_RenderDrawLine(pRenderer,nCentreX - x,nCentreY + y, nCentreX + x,nCentreY + y);

    while (y >= x) {
        x++;
        if (d > 0) {
            y--;
            d = d +  4*(x-y)+10;
        } else {
            d = d + 4*x + 6;
        }
        SDL_DrawOctants(pRenderer,nCentreX,nCentreY,x,y);
        //Lignes horizontales entre les octants
        SDL_RenderDrawLine(pRenderer,nCentreX - x,nCentreY - y, nCentreX + x,nCentreY - y);
        SDL_RenderDrawLine(pRenderer,nCentreX - y,nCentreY + x, nCentreX + y,nCentreY + x);
        SDL_RenderDrawLine(pRenderer,nCentreX - y,nCentreY - x, nCentreX + y,nCentreY - x);
        SDL_RenderDrawLine(pRenderer,nCentreX - x,nCentreY + y, nCentreX + x,nCentreY + y);
    }
}
