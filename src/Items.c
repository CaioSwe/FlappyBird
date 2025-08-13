#include "Items.h"

static Lista* allItems = NULL;

Item* Item_Init(int id, ImageObject* spriteSheet){
    Item* item = (Item*)malloc(sizeof(Item));

    item->id = id;
    item->isMimic = (rand() % 100) < 30;
    item->indice = 0;
    item->used = false;

    switch (id){
    case 1:
        strncpy(item->name, "Health Potion", MAX_STRSIZE);
        strncpy(item->description, "It considerably heals you life energy.", MAX_STRSIZE);
        break;
    case 2:
        strncpy(item->name, "Incense", MAX_STRSIZE);
        strncpy(item->description, "It makes it so your scent is undetectable to monsters.", MAX_STRSIZE);
        break;
    case 3:
        strncpy(item->name, "Treasure Chest", MAX_STRSIZE);
        strncpy(item->description, "It gives you a random amount of gold.", MAX_STRSIZE);
        break;
    default:
        strncpy(item->name, "Default Text", MAX_STRSIZE);
        strncpy(item->description, "Default description.", MAX_STRSIZE);
        break;
    }

    item->sprite = spriteSheet;

    if(allItems != NULL) inserirFim(allItems, item);

    return item;
}

void Item_ReInit(Item* item, int id, ImageObject* sprite){
    item->id = id;
    item->isMimic = (rand() % 100) <= 30;

    switch (id){
    case 1:
        strncpy(item->name, "Health Potion", MAX_STRSIZE);
        strncpy(item->description, "It considerably heals you life energy.", MAX_STRSIZE);
        break;
    case 2:
        strncpy(item->name, "Incense", MAX_STRSIZE);
        strncpy(item->description, "It makes it so your scent is undetectable to monsters.", MAX_STRSIZE);
        break;
    case 3:
        strncpy(item->name, "Treasure Chest", MAX_STRSIZE);
        strncpy(item->description, "It gives you a random amount of gold.", MAX_STRSIZE);
        break;
    default:
        strncpy(item->name, "Default Text", MAX_STRSIZE);
        strncpy(item->description, "Default description.", MAX_STRSIZE);
        break;
    }

    item->sprite = sprite;
}

Item* Item_Copy(Item* itemFrom){
    ImageObject* img = Image_Init(NULL);
    Image_Copy(itemFrom->sprite, img, true);

    Item* itemTo = Item_Init(itemFrom->id, img);

    return itemTo;
}

void usarItem2(Item* item, Player* target){
    Stats playerStats = Player_getStats(target);

    item->used = true;

    switch (item->id){
    case 1: // Health Potion
        printf("\nHP: %.2f", playerStats.health);

        int hp = playerStats.health + 4.0f;
        if(hp <= playerStats.maxHealth) Player_getHealing(target, hp - playerStats.health);
        else          Player_getHealing(target, playerStats.maxHealth - playerStats.health);
        printf("\nHealth Potion used!");

        printf("\nHP: %.2f", Player_getStats(target).health);
        break;
    case 2: // Monster's Repelent
        Player_setRepelent(target, 10);
        printf("\nMonster's Repelent used!");
        break;
    }
}

const char* getItemName(Item* item){
    return item->name;
}

const char* getItemDescription(Item* item){
    return item->description;
}

int Item_getId(Item* item){
    return item->id;
}

void setItemDescription(Item* item, const char* text){
    strncpy(item->description, text, MAX_STRSIZE);
}

void setItemName(Item* item, const char* text){
    strncpy(item->name, text, MAX_STRSIZE);
}

void setItemSprite(Item* item, ImageObject* sprite){
    item->sprite = sprite;
}

void ItemDestroy(Item* item){
    free(item->sprite);
    free(item);
}

void Item_InitList(){
    if(allItems == NULL) allItems = criaLista();
}

void Item_Free(){
    limparLista(allItems, true);
}