#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#define TILESET_LARGEUR 12
#define TILESET_HAUTEUR 9
#define LARGEUR 31
#define HAUTEUR 22
#define TILE_SIZE 32


void InitMap(int cMap[HAUTEUR][LARGEUR]);
void InitRandomMap(int cMap[HAUTEUR][LARGEUR]);


#endif // MAP_H_INCLUDED
