#include "rectangle.h"

void creerRectangle(tRectangle *rectangle,int nX,int nY,int nWidth,int nHeight) {
    rectangle->nPosX = nX;
    rectangle->nPosY = nY;
    rectangle->nLargeur = nWidth;
    rectangle->nHauteur = nHeight;
}

int getPosXRectangle(tRectangle *rectangle) {
    return rectangle->nPosX;
}

int getPosYRectangle(tRectangle *rectangle) {
    return rectangle->nPosY;
}

int getLargeurRectangle(tRectangle *rectangle) {
    return rectangle->nLargeur;
}

int getHauteurRectangle(tRectangle *rectangle) {
    return rectangle->nHauteur;
}

void setPosXRectangle(tRectangle *rectangle,int nX) {
    rectangle->nPosX = nX;
}

void setPosYRectangle(tRectangle *rectangle,int nY) {
    rectangle->nPosY = nY;
}

void setLargeurRectangle(tRectangle *rectangle,int nWidth) {
    rectangle->nLargeur = nWidth;
}

void setHauteurRectangle(tRectangle *rectangle,int nHeight) {
    rectangle->nHauteur = nHeight;
}

void setPositionRectangle(tRectangle *rectangle,int nX,int nY) {
    setPosXRectangle(rectangle,nX);
    setPosYRectangle(rectangle,nY);
}
