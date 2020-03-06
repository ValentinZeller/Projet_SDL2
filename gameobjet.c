#include "gameobjet.h"

void creerGameObjet(tGameObjet *objet,int nX, int nY, char *picture) {
    objet->nPosX = nX;
    objet->nPosY = nY;
    objet->cSprite = picture;
}

int getPosXGameObjet(tGameObjet *objet) {
    return objet->nPosX;
}

int getPosYGameObjet(tGameObjet *objet) {
    return objet->nPosY;
}

char * getSpriteGameObjet(tGameObjet *objet) {
    return objet->cSprite;
}

void setPosXGameObjet(tGameObjet *objet,int nX) {
    objet->nPosX = nX;
}

void setPosYGameObjet(tGameObjet *objet,int nY) {
    objet->nPosY = nY;
}

void setSpriteGameObjet(tGameObjet *objet,char *picture) {
    objet->cSprite = picture;
}

void setPositionGameObjet(tGameObjet *objet,int nX, int nY) {
    setPosXGameObjet(objet,nX);
    setPosYGameObjet(objet,nY);
}
