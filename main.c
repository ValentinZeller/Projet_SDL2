#include "rectangle.h"
#include "cercle.h"
#include "vue.h"
#include "gameobjet.h"
#include "map.h"

void AfficherMap(sdl_manager sdl,int cMap[HAUTEUR][LARGEUR],SDL_Rect Camera,SDL_Rect src, SDL_Rect dst);

int main(int argc, char *argv[]) //Modification du main pour inclure le main de la SDL2
{
    sdl_manager sdl; //Gestion de la sdl niveau affichage
    SDL_Rect Rect_dest = {0,0,TILE_SIZE,TILE_SIZE},Rect_src = {0,0,TILE_SIZE,TILE_SIZE};
    SDL_Rect Camera = {0,0,10,10};

    int i,j;

    //Le tileset
    SDL_Surface *tileset;

    //Le niveau
    int cMap[HAUTEUR][LARGEUR] = {0};

    InitRandomMap(cMap);

    //Initialisation de la SDL
    SDLManager_Init(&sdl);

    //Chargement du tileset
    tileset = IMG_Load("assets/Terrain.png");
    sdl.pTexture = SDL_CreateTextureFromSurface(sdl.pRenderer,tileset);

    //Affichage
    AfficherMap(sdl,cMap,Camera,Rect_src,Rect_dest);
    SDLManager_Refresh(sdl.pRenderer,500);
    SDL_RenderClear(sdl.pRenderer);

    //Scrolling diagonal
    for (i=0;i<2;i++) {
        for (j=0;j<2;j++) {
            Camera.x += 1;
            Camera.y += 1;
            Camera.w += 1;
            Camera.h += 1;
            AfficherMap(sdl,cMap,Camera,Rect_src,Rect_dest);
            SDLManager_Refresh(sdl.pRenderer,500);
            SDL_RenderClear(sdl.pRenderer);
        }
    }
    //Arrêt de la SDL
    SDLManager_Stop(&sdl);
    return 0;
}

void AfficherMap(sdl_manager sdl,int cMap[HAUTEUR][LARGEUR],SDL_Rect Camera,SDL_Rect src, SDL_Rect dst) {
    //i et j pour placer les tiles à l'écran, tileindex pour sélectionner la bonne tile dans le tileset
    int i,j, tileindex;
    for (i=Camera.x;i<Camera.w;i++) {
        for (j=Camera.y;j<Camera.h;j++) {

            dst.x = i*TILE_SIZE;
            dst.y = j*TILE_SIZE;

            tileindex = cMap[j][i];

            src.x = (tileindex % TILESET_LARGEUR)*TILE_SIZE;
            src.y = (int)(tileindex / TILESET_HAUTEUR)*TILE_SIZE;

            SDL_RenderCopy(sdl.pRenderer,sdl.pTexture,&src,&dst);
        }
    }
}
