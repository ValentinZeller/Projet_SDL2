#include "map.h"
#include <stdlib.h>

void InitMap(int cMap[HAUTEUR][LARGEUR]) {
    int i = 0,j = 0;
    for (i=0; i<LARGEUR;i++) {
        for (j=0;j<HAUTEUR; j++) {
            if (j == 0) {
                if (i == 0) {
                    cMap[j][i] = 0;
                } else if (i == (LARGEUR-1)) {
                    cMap[j][i] = 2;
                } else {
                    cMap[j][i] = 1;
                }
            } else if (j == HAUTEUR -1 ) {
                if (i == 0) {
                    cMap[j][i] = 24;
                } else if (i == (LARGEUR -1)) {
                    cMap[j][i] = 26;
                } else {
                    cMap[j][i] = 25;
                }
            } else {
                if (i == 0) {
                    cMap[j][i] = 12;
                } else if (i == (LARGEUR-1)) {
                    cMap[j][i] = 14;
                } else {
                    cMap[j][i] = 13;
                }
            }
        }
    }
}

void InitRandomMap(int cMap[HAUTEUR][LARGEUR]) {
    int i,j;
    for (i=0;i<LARGEUR;i++) {
        for (j=0;j<HAUTEUR;j++) {
            cMap[j][i] = rand() % 27;
        }
    }
}
