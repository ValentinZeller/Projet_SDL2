#ifndef GAMEOBJET_H_INCLUDED
#define GAMEOBJET_H_INCLUDED

typedef struct tGameObjet {
    int nPosX,nPosY;
    char *cSprite;
}tGameObjet;

extern void creerGameObjet(tGameObjet *objet,int nX, int nY, char *picture);

extern int getPosXGameObjet(tGameObjet *objet);
extern int getPosYGameObjet(tGameObjet *objet);
extern char * getSpriteGameObjet(tGameObjet *objet);

extern void setPosXGameObjet(tGameObjet *objet,int nX);
extern void setPosYGameObjet(tGameObjet *objet,int nY);
extern void setSpriteGameObjet(tGameObjet *objet,char *picture);

extern void setPositionGameObjet(tGameObjet *objet,int nX, int nY);


#endif // GAMEOBJET_H_INCLUDED
