#include "rectangle.h"
#include "cercle.h"
#include "vue.h"
#include "gameobjet.h"
#include "map.h"



int main(int argc, char *argv[]) //Modification du main pour inclure le main de la SDL2
{
    sdl_manager sdl; //Gestion de la sdl niveau affichage
    SDL_Rect Rect_dest = {0,0,TILE_SIZE,TILE_SIZE},Rect_src = {0,0,TILE_SIZE,TILE_SIZE};
    SDL_Rect Camera = {0,0,10,10};
    SDL_Event event;
    SDL_Color color = {255,255,0,1};
    SDL_Surface *tileset;

    //Le niveau
    int cMap[HAUTEUR][LARGEUR] = {0};
    InitRandomMap(cMap);

    //Initialisation de la SDL
    SDLManager_Init(&sdl);

    tileset = IMG_Load("assets/Terrain.png");
    sdl.pTexture = SDL_CreateTextureFromSurface(sdl.pRenderer,tileset);

    //Boucle principale
    while (1) {
        //Gestion des events
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                //Si l'utilisateur clique, fin du programme
                case SDL_MOUSEBUTTONDOWN :
                        //Arrêt de la SDL
                        SDLManager_Stop(&sdl);
                        return 0;
                        break;
                case SDL_KEYDOWN :
                    //Déplacement de la caméra
                    if ((event.key.keysym.sym == SDLK_UP)&&(Camera.y > 0)) {
                        Camera.y += -2;
                        Camera.h += -2;
                    }
                    if ((event.key.keysym.sym == SDLK_LEFT)&&(Camera.x > 0)) {
                        Camera.x += -2;
                        Camera.w += -2;

                    }
                    if ((event.key.keysym.sym == SDLK_RIGHT)&&(Camera.w < LARGEUR)) {
                        Camera.x += 2;
                        Camera.w += 2;
                    }
                    if ((event.key.keysym.sym == SDLK_DOWN)&&(Camera.h < HAUTEUR)) {
                        Camera.y += 2;
                        Camera.h += 2;
                    }
            }
        }
        //Affichage de la map vue par la caméra
        AfficherMap(sdl,cMap,Camera,Rect_src,Rect_dest);
        SDLManager_Refresh(sdl.pRenderer,0);
        SDLManager_ClearScreen(sdl.pRenderer);
    }
    //Arrêt de la SDL
    SDLManager_Stop(&sdl);
    return 0;
}


