#include "rectangle.h"
#include "cercle.h"
#include "vue.h"
#include "gameobjet.h"
#include <ctype.h>

#define TILESET_LARGEUR 12
#define TILESET_HAUTEUR 9
#define LARGEUR 12
#define HAUTEUR 5
#define TILE_SIZE 32

int main(int argc, char *argv[]) //Modification du main pour inclure le main de la SDL2
{
    sdl_manager sdl; //Gestion de la sdl niveau affichage
    SDL_Rect Rect_dest = {0,0,TILE_SIZE,TILE_SIZE},Rect_src = {0,0,TILE_SIZE,TILE_SIZE};
    //i et j pour placer les tiles à l'écran, tileindex pour sélectionner la bonne tile dans le tileset
    int i,j, tileindex;

    //Le tileset
    SDL_Surface *tileset;

    //Le niveau
    int cMap[HAUTEUR][LARGEUR] = {
     {0,1,1,1,1,1,1,1,1,1,1,2},
     {12,13,13,13,13,13,13,13,13,13,13,14},
     {12,13,13,13,13,13,13,13,13,13,13,14},
     {12,13,13,13,13,13,13,13,13,13,13,14},
     {24,25,25,25,25,25,25,25,25,25,25,26},
    };

    //Initialisation de la SDL
    SDLManager_Init(&sdl);

    //Chargement du tileset
    tileset = IMG_Load("assets/Terrain.png");
    sdl.pTexture = SDL_CreateTextureFromSurface(sdl.pRenderer,tileset);

    //Création de l'affichage du niveau
    for (i=0;i<LARGEUR;i++) {
        for (j=0;j<HAUTEUR;j++) {

            Rect_dest.x = i*TILE_SIZE;
            Rect_dest.y = j*TILE_SIZE;

            tileindex = cMap[j][i];

            Rect_src.x = (tileindex % TILESET_LARGEUR)*TILE_SIZE;
            Rect_src.y = (int)(tileindex / TILESET_HAUTEUR)*TILE_SIZE;

            SDL_RenderCopy(sdl.pRenderer,sdl.pTexture,&Rect_src,&Rect_dest);
        }
    }


    SDL_RenderPresent(sdl.pRenderer);
    SDL_Delay(1500);


    //Arrêt de la SDL
    SDLManager_Stop(&sdl);
    return 0;
}
