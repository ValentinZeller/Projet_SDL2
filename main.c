#include <stdio.h>
#include <stdlib.h>
#include "SDL2/SDL.h" //Appel de la biblioth�que SDL2

void SDL_DrawOctants(SDL_Renderer *pRenderer, int nCentreX,int nCentreY, int x, int y);
void SDL_DrawCircle(SDL_Renderer * pRenderer, int nCentreX, int nCentreY, int nRadius);
void SDL_DrawFilledCircle(SDL_Renderer* pRenderer, int nCentreX,int nCentreY, int nRadius);

int main(int argc, char *argv[]) //Modification du main pour inclure le main de la SDL2
{
    //Initialisation d'un pointeur de type fen�tre
    SDL_Window *pWindow=NULL;
    //Initialisation d'un pointeur de type renderer
    SDL_Renderer *pRenderer=NULL;
    //Initialisation d'un pointeur de type texture
    SDL_Texture *pTexture=NULL;

    //Initialisation d'un rectangle {position horizontale, position verticale, largeur, hauteur)
    SDL_Rect rect = {10,10,100,100};
    //Initialisation d'un point {position horizontale, position verticale}
    SDL_Point point = {0,0};

    if (SDL_Init(SDL_INIT_VIDEO) < 0){
    //SDL_Init permet d'initialiser la SDL
    //SDL_INIT_VIDEO est le sous-syst�me pour l'affichage raphique
    //Si SDL_Init renvoit -1, on affiche l'erreur et on stop le programme
        printf("SDL_Init Error: %s\n",SDL_GetError());;
        return 1;
    }

    pWindow = SDL_CreateWindow("Une fenetre SDL",SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, 600, 600, SDL_WINDOW_RESIZABLE);
        // Cr�ation de la fen�tre avec SDL_CreateWindow (titre de la fen�tre, position horizontale, position verticale, largeur, hauteur et les flags
        //SDL_WINDOWS_CENTERED permet de centrer la fen�tre
        //SDL_WINDOW_RESIZABLE permet de changer la taille de la fen�tre pendant l'execution

    if (pWindow == NULL) { //Si la fen�tre est vide, on stop le programme
        printf("Erreur lors de la creation d'une fenetre : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    pRenderer = SDL_CreateRenderer(pWindow,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    //Cr�ation du renderer avec SDL_CreateRenderer(pointeur de fen�tre,index, flags)
    //l'index -1 permet de s�lectionner le premier driver qui g�re le rendu
    //SDL_RENDERER_ACCELERATED permet d'utiliser l'acc�l�ration mat�rielle
    //SDL_RENDERER_PRESENTVSYNC permet de synchroniser le renderer sur le taux de raffraichissement

    //Il est aussi possible d'utiliser SDL_CreateWindowAndRenderer pour cr�er la fen�tre et son renderer

    if (pRenderer == NULL) {//Si le renderer est vide, on stop le programme
        printf("Erreur lors de la cr�ation du render : %s\n",SDL_GetError());
        return EXIT_FAILURE;

    }
    SDL_SetRenderDrawColor(pRenderer, 255,0,0,255);//D�finit une couleur pour dessiner(ici le rouge)

    //Possibilit� de cr�er une couleur avec le type SDL_Color
    //Posibilit� de r�cup�rer la couleur utilis�e pour dessinger avec SDL_GetRenderDrawColor
    SDL_RenderClear(pRenderer);//Applique la couleur sur tout l'�cran

    SDL_SetRenderDrawColor(pRenderer,0,0,0,255);
    SDL_RenderDrawRect(pRenderer,&rect);//Dessine le rectangle
    SDL_RenderPresent(pRenderer);//Fait un rendu
    SDL_Delay(1500);  //Pause de 1.5 secondes pour voir la fen�tre

    SDL_RenderFillRect(pRenderer,&rect);//Remplissage du rectangle de la couleur noir
    SDL_RenderPresent(pRenderer);//Fait un rendu//Dessin d'un cercle � l'aide de l'Algorithme de Bresenhams
    SDL_Delay(1500);  //Pause de 1.5 secondes pour voir la fen�tre

    SDL_SetRenderDrawColor(pRenderer, 255,0,0,255);//D�finit une couleur pour dessiner(ici le rouge)
    SDL_RenderClear(pRenderer);//Applique la couleur sur tout l'�cran
    SDL_SetRenderDrawColor(pRenderer, 0,0,0,255);

    SDL_DrawCircle(pRenderer,100,100,40);//Dessin du cercle
    SDL_RenderPresent(pRenderer);//Fait un rendu
    SDL_Delay(1500);  //Pause de 1.5 secondes pour voir la fen�tre

    SDL_DrawFilledCircle(pRenderer,100,100,40);//Remplissage du cercle
    SDL_RenderPresent(pRenderer);//Fait un rendu
    SDL_Delay(1500);  //Pause de 1.5 secondes pour voir la fen�tre

    SDL_DestroyRenderer(pRenderer); //Suppression du renderer
    SDL_DestroyWindow(pWindow); //Suppression de la fen�tre
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

//Dessin d'un cercle � l'aide de l'Algorithme de Bresenhams
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

//Dessin d'un cercle rempli � l'aide de l'Algorithme de Bresenhams
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
