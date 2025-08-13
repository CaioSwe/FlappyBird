#include "TileSet.h"

void CreateGround(int** mapa, int i, int j, int squaresize, Lista* chao, ImageObject* tileSet){
    ImageObject* c = Image_Init(NULL);
    Image_Copy(tileSet, c, true);

    c->x = squaresize*j;
    c->y = squaresize*i;
    
    inserirFim(chao, c);
}

void HandleTile(int** mapa, int i, int j, int squaresize, Lista* paredes, ImageObject* tileSet, int target){
    if (mapa[i][j] != target) return;

    bool up = (i > 0) && mapa[i-1][j] == target;
    bool down = (i < TAM-1) && mapa[i+1][j] == target;
    bool left = (j > 0) && mapa[i][j-1] == target;
    bool right = (j < TAM-1) && mapa[i][j+1] == target;

    bool topleft = (i > 0 && j > 0) && mapa[i-1][j-1] == target;
    bool topright = (i > 0 && j < TAM-1) && mapa[i-1][j+1] == target;
    bool bottomleft = (i < TAM-1 && j > 0) && mapa[i+1][j-1] == target;
    bool bottomright = (i < TAM-1 && j < TAM-1) && mapa[i+1][j+1] == target;

    ImageObject* tl = Image_Init(NULL);
    ImageObject* tr = Image_Init(NULL);
    ImageObject* bl = Image_Init(NULL);
    ImageObject* br = Image_Init(NULL);

    Image_Copy(tileSet, tl, true);
    Image_Copy(tileSet, tr, true);
    Image_Copy(tileSet, bl, true);
    Image_Copy(tileSet, br, true);

    tl->destination.x = j * squaresize;
    tl->destination.y = i * squaresize;
    tr->destination.x = j * squaresize + squaresize/2;
    tr->destination.y = i * squaresize;
    bl->destination.x = j * squaresize;
    bl->destination.y = i * squaresize + squaresize/2;
    br->destination.x = j * squaresize + squaresize/2;
    br->destination.y = i * squaresize + squaresize/2;

    float deltaX = 16;
    float deltaY = 16;

    if (left){
        tl->source.x = deltaX * 4;
        bl->source.x = deltaX * 1;

        if (up){
            tl->source.x = deltaX * 8;

            if (topleft){
                tl->source.x = deltaX * 0;
            }
        }
        if (down){
            bl->source.x = deltaX * 6;

            if (bottomleft){
                bl->source.x = deltaX * 0;
            }
        }
    }
    else{
        tl->source.x = deltaX * 3;
        bl->source.x = deltaX * 3;

        if (!up){
            tl->source.x = deltaX * 10;
        }
        if (!down){
            bl->source.x = deltaX * 12;
        }
    }
    if (right){
        tr->source.x = deltaX * 4;
        br->source.x = deltaX * 1;

        if (up){
            tr->source.x = deltaX * 7;

            if (topright){
                tr->source.x = deltaX * 0;
            }
        }
        if (down){
            br->source.x = deltaX * 5;

            if (bottomright){
                br->source.x = deltaX * 0;
            }
        }
    }
    else{
        tr->source.x = deltaX * 2;
        br->source.x = deltaX * 2;

        if (!up){
            tr->source.x = deltaX * 9;
        }
        if (!down){
            br->source.x = deltaX * 11;
        }
    }

    inserirFim(paredes, tl);
    inserirFim(paredes, tr);
    inserirFim(paredes, bl);
    inserirFim(paredes, br);
}

void UpdateTile(int** mapa, int posX, int posY, int squaresize, Lista* paredes, ImageObject* tileSet){
    HandleTile(mapa, posX, posY, squaresize, paredes, tileSet, 2);
}

void UpdateNeighborTiles(int** mapa, int posY, int posX, int squaresize, Lista* paredes, ImageObject* tileSet){
    UpdateTile(mapa, posX, posY-1, squaresize, paredes, tileSet);
    UpdateTile(mapa, posX-1, posY, squaresize, paredes, tileSet);
    UpdateTile(mapa, posX-1, posY-1, squaresize, paredes, tileSet);

    UpdateTile(mapa, posX-1, posY+1, squaresize, paredes, tileSet);
    UpdateTile(mapa, posX+1, posY-1, squaresize, paredes, tileSet);

    UpdateTile(mapa, posX, posY+1, squaresize, paredes, tileSet);
    UpdateTile(mapa, posX+1, posY, squaresize, paredes, tileSet);
    UpdateTile(mapa, posX+1, posY+1, squaresize, paredes, tileSet);
}