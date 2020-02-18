#include <stdio.h>
#include <stdlib.h>
#include "SDL2/SDL.h" //Appel de la bibliothèque SDL2

void SDL_DrawOctants(SDL_Renderer *pRenderer, int nCentreX,int nCentreY, int x, int y);
void SDL_DrawCircle(SDL_Renderer * pRenderer, int nCentreX, int nCentreY, int nRadius);
void SDL_DrawFilledCircle(SDL_Renderer* pRenderer, int nCentreX,int nCentreY, int nRadius);

int main(int argc, char *argv[]) //Modification du main pour inclure le main de la SDL2
{
    SDL_Window *pWindow=NULL;
    SDL_Renderer *pRenderer=NULL;
    SDL_Rect rect = {0,0,100,100}, dist = {0,0,0,0};
    SDL_Surface *pSurface= NULL;

    /* Initialisation d'une texture */
    SDL_Texture *pTexture = NULL;


    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("SDL_Init Error: %s\n",SDL_GetError());;
        return 1;
    }

    pWindow = SDL_CreateWindow("Une fenetre SDL",SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, 600, 600, SDL_WINDOW_RESIZABLE);
    if (pWindow == NULL) { //Si la fenêtre est vide, on stop le programme
        printf("Erreur lors de la creation d'une fenetre : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    pRenderer = SDL_CreateRenderer(pWindow,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (pRenderer == NULL) {//Si le renderer est vide, on stop le programme
        printf("Erreur lors de la création du render : %s\n",SDL_GetError());
        return EXIT_FAILURE;

    }

    pSurface = SDL_LoadBMP("minecraft.bmp");//Charger une image

    if(pSurface == NULL) {
        printf("La creation de la surface a echoue : %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    pTexture = SDL_CreateTexture(pRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,100,100);
    /* Création de la texture avec SDL_CreateTexture(renderer, format de pixel, restriction d'accès, largeur, hauteur)
        Format : RGBA
        Accès : Permet d'utiliser la texture comme cible de rendu (comme un renderer)
    */

    pTexture = SDL_CreateTextureFromSurface(pRenderer,pSurface);
    //Création d'une texture à partir d'une surface avec SDL_CreateTextureFromSurface(renderer,surface)


    SDL_QueryTexture(pTexture,NULL,NULL,&dist.w,&dist.h);
    //Récupération de la largeur et de la hauteur de la texture avec SDL_QueryTexture(texture,format de pixel,restriction d'accès,largeur(pointeur pour stocker),hauteur(pointeur pour stocker))

    SDL_RenderCopy(pRenderer, pTexture, NULL, &dist);
    //Affichage de la texture avec SDL_RenderCopy(renderer,texture,partie de la texture à afficher ,zone où est affiché la texture)

    SDL_RenderPresent(pRenderer);

    SDL_Delay(1500);


    SDL_DestroyTexture(pTexture);
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
