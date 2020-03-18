#include "SDL.h"
#include "camera.h"

void MoveCameraVertical(SDL_Rect *pCamera,int nSpeed) {
    pCamera->y += nSpeed;
    pCamera->h += nSpeed;
}

void MoveCameraHorizontal(SDL_Rect *pCamera,int nSpeed) {
    pCamera->x += nSpeed;
    pCamera->w += nSpeed;
}
