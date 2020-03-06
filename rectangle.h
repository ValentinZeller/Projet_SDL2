#ifndef RECTANGLE_H_INCLUDED
#define RECTANGLE_H_INCLUDED

typedef struct tRectangle {
    int nPosX,nPosY,nLargeur,nHauteur;
}tRectangle;

extern void creerRectangle(tRectangle *rectangle,int nX,int nY,int nWidth,int nHeight);

extern int getPosXRectangle(tRectangle *rectangle);
extern int getPosYRectangle(tRectangle *rectangle);
extern int getLargeurRectangle(tRectangle *rectangle);
extern int getHauteurRectangle(tRectangle *rectangle);

extern void setPosXRectangle(tRectangle *rectangle,int nX);
extern void setPosYRectangle(tRectangle *rectangle,int nY);
extern void setLargeurRectangle(tRectangle *rectangle,int nWidth);
extern void setHauteurRectangle(tRectangle *rectangle,int nHeight);

extern void setPositionRectangle(tRectangle *rectangle,int nX,int nY);

#endif // RECTANGLE_H_INCLUDED
