#ifndef CERCLE_H_INCLUDED
#define CERCLE_H_INCLUDED

typedef struct tCercle {
    int nCentreX,nCentreY,nRadius;
}tCercle;

extern void creerCercle(tCercle *cercle,int nX,int nY,int nRayon);

extern int getCentreXCercle(tCercle *cercle);
extern int getCentreYCercle(tCercle *cercle);
extern int getRadiusCercle(tCercle *cercle);

extern void setCentreXCercle(tCercle *cercle,int nX);
extern void setCentreYCercle(tCercle *cercle,int nY);
extern void setRadiusCercle(tCercle *cercle,int nRayon);

extern void setPositionCercle(tCercle *cercle,int nX,int nY);

#endif // CERCLE_H_INCLUDED
