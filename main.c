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

    //Création d'un rectangle
    tRectangle rect1;
    creerRectangle(&rect1,10,10,200,200);

    //Le niveau
    int cMap[HAUTEUR][LARGEUR] = {0};

    InitRandomMap(cMap);
    AfficherMap(sdl,cMap,Camera,Rect_src,Rect_dest);

    //Initialisation de la SDL
    SDLManager_Init(&sdl);


    tileset = IMG_Load("assets/Terrain.png");
    sdl.pTexture = SDL_CreateTextureFromSurface(sdl.pRenderer,tileset);
    AfficherMap(sdl,cMap,Camera,Rect_src,Rect_dest);
    SDLManager_Refresh(sdl.pRenderer,500);

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
                    //Lors de la pression sur une touche, apparition d'un rectangle
                    SDL_DrawFilledRectangle(sdl.pRenderer,rand()%1024,rand()%720,20,20,1,color);
                case SDL_QUIT :
                    printf("Fin de la SDL2");


            }
        }
    }
    //Arrêt de la SDL
    SDLManager_Stop(&sdl);
    return 0;
}


