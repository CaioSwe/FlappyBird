#ifndef _TileSet_h_
#define _TileSet_h_

#include "Lista.h"
#include "ImageObject.h"
#include "Utils.h"
#include "Delimiters.h"

void CreateGround(int** mapa, int i, int j, int squaresize, Lista* chao, ImageObject* tileSet);

void HandleTile(int** mapa, int i, int j, int squaresize, Lista* paredes, ImageObject* tileSet, int target);

void UpdateTile(int** mapa, int posX, int posY, int squaresize, Lista* paredes, ImageObject* tileSet);

void UpdateNeighborTiles(int** mapa, int posY, int posX, int squaresize, Lista* paredes, ImageObject* tileSet);

void UpdateTileSet(ImageObject* spriteBase);

#endif