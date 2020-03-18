//**********************************************
//Fichier : vue.h
//
//Classe : sdl_manager
//Description : Gestion de l'affichage avec la SDL
//Attributs :
//
//Notes :
//**********************************************

#ifndef VUE_H_INCLUDED
#define VUE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "SDL.h" //Appel de la bibliothèque SDL2
#include "SDL_image.h" //Appel de la bibliothèque SDL2_image
#include "map.h"

typedef struct sdl_manager{
    SDL_Window *pWindow;
    SDL_Renderer *pRenderer;
    SDL_Texture *pTexture;
    SDL_Surface *pSurface;
}sdl_manager;

extern void SDLManager_Init(sdl_manager *sdl);
extern void SDLManager_DisplayImage(sdl_manager *sdl,char *pPicturePath,int nPosX, int nPosY,int nDelay);
extern void SDLManager_ClearScreen(SDL_Renderer *pRenderer);
extern void SDLManager_Refresh(SDL_Renderer *pRenderer,int nDelay);
extern void SDLManager_Stop(sdl_manager *sdl);

extern void SDL_DrawOctants(SDL_Renderer *pRenderer, int nCentreX,int nCentreY, int x, int y);
extern void SDL_DrawCircle(SDL_Renderer * pRenderer, int nCentreX, int nCentreY, int nRadius,int nDelay,SDL_Color color);
extern void SDL_DrawFilledCircle(SDL_Renderer* pRenderer, int nCentreX,int nCentreY, int nRadius,int nDelay,SDL_Color color);

extern void SDL_DrawRectangle(SDL_Renderer *pRenderer, int nPosX, int nPosY, int nLargeur, int nHauteur,int nDelay,SDL_Color color);
extern void SDL_DrawFilledRectangle(SDL_Renderer *pRenderer, int nPosX, int nPosY, int nLargeur, int nHauteur,int nDelay,SDL_Color color);

void AfficherMap(sdl_manager sdl,int cMap[][31],SDL_Rect Camera,SDL_Rect src, SDL_Rect dst);
#endif // VUE_H_INCLUDED
