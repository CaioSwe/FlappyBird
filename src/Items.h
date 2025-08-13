#ifndef _Items_h_
#define _Items_h_

#include "Utils.h"
#include "Delimiters.h"
#include "Lista.h"
#include "Player.h"
#include "ImageObject.h"

/*
Codes:
    1 = Poção de vida
    2 = Repelente de Monstro
    3 = Baú (pode ser mimico)
*/

typedef struct Item {
    char name[MAX_STRSIZE];
    char description[MAX_STRSIZE];
    int id;
    bool isMimic;
    bool used;

    int indice;

    ImageObject* sprite;
} Item;

Item* Item_Init(int id, ImageObject* spriteSheet);

void Item_ReInit(Item* item, int id, ImageObject* sprite);

Item* Item_Copy(Item* item);

void usarItem2(Item* item, Player* target);

const char* getItemName(Item* item);

const char* getItemDescription(Item* item);

int Item_getId(Item* item);

void setItemDescription(Item* item, const char* text);

void setItemName(Item* item, const char* text);

void setItemSprite(Item* item, ImageObject* sprite);

void ItemDestroy(Item* item);

void Item_InitList();

void Item_Free();

#endif