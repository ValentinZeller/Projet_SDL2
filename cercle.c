#include "cercle.h"

void creerCercle(tCercle *cercle,int nX,int nY,int nRayon) {
    cercle->nCentreX = nX;
    cercle->nCentreY = nY;
    cercle->nRadius = nRayon;
}

int getCentreXCercle(tCercle *cercle) {
    return cercle->nCentreX;
}

int getCentreYCercle(tCercle *cercle) {
    return cercle->nCentreY;
}

int getRadiusCercle(tCercle *cercle) {
    return cercle->nRadius;
}

void setCentreXCercle(tCercle *cercle,int nX) {
    cercle->nCentreX = nX;
}

void setCentreYCercle(tCercle *cercle,int nY) {
    cercle->nCentreY = nY;
}

void setRadiusCercle(tCercle *cercle,int nRayon) {
    cercle->nRadius = nRayon;
}

void setPositionCercle(tCercle *cercle,int nX,int nY) {
    setCentreXCercle(cercle,nX);
    setCentreYCercle(cercle,nY);
}
