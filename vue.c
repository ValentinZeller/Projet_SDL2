//**********************************************
//Fichier : vue.c
//
//Classe : sdl_manager
//**********************************************

#include "vue.h"

//**********************************************************
//Description : Initialisation de la SDL et du gestionnaire de de la SDL
//Entree : Le gestionnaire de la SDL
//Sortie :
//**********************************************************
void SDLManager_Init(sdl_manager *sdl) {
    sdl->pWindow = NULL;
    sdl->pRenderer = NULL;
    sdl->pSurface = NULL;
    sdl->pTexture = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("SDL_Init Error: %s\n",SDL_GetError());;
        return EXIT_FAILURE;
    }

    sdl->pWindow = SDL_CreateWindow("Une fenetre SDL",SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, 1024, 720, SDL_WINDOW_RESIZABLE);
    if (sdl->pWindow == NULL) { //Si la fenêtre est vide, on stop le programme
        printf("Erreur lors de la creation d'une fenetre : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    sdl->pRenderer = SDL_CreateRenderer(sdl->pWindow,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (sdl->pRenderer == NULL) {//Si le renderer est vide, on stop le programme
        printf("Erreur lors de la création du render : %s\n",SDL_GetError());
        return EXIT_FAILURE;

    }
}

//**********************************************************
//Description : Remettre l'affichage en noir
//Entree : Gestionnaire de la SDL
//Sortie :
//**********************************************************
void SDLManager_ClearScreen(SDL_Renderer *pRenderer) {
    SDL_SetRenderDrawColor(pRenderer,0,0,0,255);
    SDL_RenderClear(pRenderer);
}

//**********************************************************
//Description : Affichage d'une image à une position
//Entree : Gestionnaire de la SDL
//          Chemin d'accès vers l'image
//          Position X et Y sur l'écran
//          0 ou 1, si 1, l'affichage est d'abord reset en noir puis affichage, sinon l'image sera affichée par dessus
//          Delais après l'affichage pour freeze l'écran
//Sortie :
//**********************************************************
void SDLManager_DisplayImage(sdl_manager *sdl,char *pPicturePath,int nPosX, int nPosY, int nDelay) {
    SDL_Rect dist = {nPosX,nPosY,0,0};

    sdl->pSurface = SDL_LoadBMP(pPicturePath);//Charger une image

    if(sdl->pSurface == NULL) {
        printf("La creation de la surface a echoue : %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    sdl->pTexture = SDL_CreateTexture(sdl->pRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,100,100);
    sdl->pTexture = SDL_CreateTextureFromSurface(sdl->pRenderer,sdl->pSurface);

    SDL_QueryTexture(sdl->pTexture,NULL,NULL,&dist.w,&dist.h);
    //Récupération de la largeur et de la hauteur de la texture avec SDL_QueryTexture(texture,format de pixel,restriction d'accès,largeur(pointeur pour stocker),hauteur(pointeur pour stocker))

    SDL_RenderCopy(sdl->pRenderer, sdl->pTexture, NULL, &dist);
    //Affichage de la texture avec SDL_RenderCopy(renderer,texture,partie de la texture à afficher ,zone où est affiché la texture)
    SDLManager_Refresh(sdl->pRenderer,nDelay);
}

//**********************************************************
//Description : Raffraichissement de l'affichage
//Entree : Le gestionnaire de la SDL et le delais d'affichage
//Sortie :
//**********************************************************
void SDLManager_Refresh(SDL_Renderer *pRenderer,int nDelay) {
    SDL_RenderPresent(pRenderer);
    SDL_Delay(nDelay);
}


//**********************************************************
//Description : Arrêt de la SDL
//Entree : Le gestionnaire de la SDL
//Sortie :
//**********************************************************
void SDLManager_Stop(sdl_manager *sdl) {

    /* Libération des instances */
    SDL_DestroyTexture(sdl->pTexture); //Suppression de la texture
    SDL_FreeSurface(sdl->pSurface); //Suppression de la surface
    SDL_DestroyRenderer(sdl->pRenderer); //Suppression du renderer
    SDL_DestroyWindow(sdl->pWindow); //Suppression de la fenêtre

    SDL_Quit();  //Fin de la SDL
}

//**********************************************************
//Description : Dessin des 8 points (octants) de l'algorime de Bresenhams pour le circle
//Entree : Moteur de rendu
//          Position X et Y du centre du cercle
//          Position X et Y du point servant à dessiner la bordure du cercle
//Sortie :
//**********************************************************
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

//**********************************************************
//Description : Dessin d'un cercle à l'aide de l'Algorithme de Bresenhams
//Entree : Moteur de rendu
//          Position X et Y du centre du cercle
//          Rayon du cercle
//Sortie :
//**********************************************************
void SDL_DrawCircle(SDL_Renderer * pRenderer, int nCentreX, int nCentreY, int nRadius,int nDelay,SDL_Color color) {
    int x = 0;
    int y = 0;
    int d;
    d = 3 - 2*nRadius;
    y = nRadius;
    SDL_SetRenderDrawColor(pRenderer,color.r,color.g,color.b,color.a);
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
    SDLManager_Refresh(pRenderer,nDelay);
}

//**********************************************************
//Description : Dessin d'un cercle rempli à l'aide de l'Algorithme de Bresenhams
//Entree : Moteur de rendu
//          Position X et Y du centre du cercle
//          Rayon du cercle
//Sortie :
//**********************************************************
void SDL_DrawFilledCircle(SDL_Renderer* pRenderer, int nCentreX,int nCentreY, int nRadius,int nDelay,SDL_Color color){
    int x = 0;
    int y = 0;
    int d;
    d = 3 - 2*nRadius;
    y = nRadius;
    SDL_SetRenderDrawColor(pRenderer,color.r,color.g,color.b,color.a);
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
    SDLManager_Refresh(pRenderer,nDelay);
}

//**********************************************************
//Description : Dessin d'un rectangle
//Entree : Moteur de rendu
//          Position X et Y du coin gauche du rectangle
//          Largeur et hauteur du rectangle
//Sortie :
//**********************************************************
void SDL_DrawRectangle(SDL_Renderer *pRenderer, int nPosX, int nPosY, int nLargeur, int nHauteur,int nDelay,SDL_Color color) {
    SDL_Rect rect = {nPosX,nPosY,nLargeur,nHauteur};
    SDL_SetRenderDrawColor(pRenderer,color.r,color.g,color.b,color.a);
    SDL_RenderDrawRect(pRenderer,&rect);
    SDLManager_Refresh(pRenderer,nDelay);
}

//**********************************************************
//Description : Dessin d'un rectangle rempli
//Entree : Moteur de rendu
//          Position X et Y du coin gauche du rectangle
//          Largeur et hauteur du rectangle
//Sortie :
//**********************************************************
void SDL_DrawFilledRectangle(SDL_Renderer *pRenderer, int nPosX, int nPosY, int nLargeur, int nHauteur,int nDelay,SDL_Color color) {
    SDL_Rect rect = {nPosX,nPosY,nLargeur,nHauteur};
    SDL_SetRenderDrawColor(pRenderer,color.r,color.g,color.b,color.a);
    SDL_RenderFillRect(pRenderer,&rect);
    SDLManager_Refresh(pRenderer,nDelay);
}


