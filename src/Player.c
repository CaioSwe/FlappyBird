#include "Player.h"

static Lista* allPlayers = NULL;

typedef struct Moving{
    bool up;
    bool down;
    bool left;
    bool right;
} Moving;

typedef struct Animation{
    PositionAnimation* position;
    ScaleAnimation* scale;
    FramesAnimation frames;
} Animation;

typedef struct Inventario{
    Lista* utils;
} Inventario;

typedef struct Player{
    char name[MAX_STRSIZE];

    Texture2D spriteSheet;

    Animation* anim;
    
    Vector2 display;
    float deltaX;
    float deltaY;
    Vector2 coordinates;

    Rectangle source;
    Rectangle destination;

    float stepDistance;
    bool characterChoice;
    bool isControlled;

    MoveSet keys;
    Moving moving;
    bool locked;

    Stats stats;
    Inventario inventario;
    Pilha* pilha;

    Decision action;
} Player;

Player* Player_Init(Rectangle source, Rectangle destination, const char* spriteSheet){
    Player* player = (Player*)malloc(sizeof(Player));

    strncpy(player->name, "Default", MAX_STRSIZE);

    player->anim = (Animation*)malloc(sizeof(Animation));
    player->anim->position = (PositionAnimation*)malloc(sizeof(PositionAnimation));
    player->anim->scale = (ScaleAnimation*)malloc(sizeof(ScaleAnimation));

    if(spriteSheet != NULL) player->spriteSheet = LoadTexture(spriteSheet);
    
    player->anim->position->function = linearFunction;

    player->anim->frames = (FramesAnimation){true, 10.0f, 0.0f, 1, 0, 3, 0, 6, 6};

    player->display = (Vector2){0, 120.0f};
    player->deltaX = 160.0f;

    player->source = source;
    player->destination = destination;

    player->stepDistance = 1.0f;
    player->characterChoice = false;

    player->stats = (Stats){10.0f, 10.0f, 2.0f, 0.5f, 0.1f, 0.25f, false, false, 0, 0}; // Vida máxima, Vida, Ataque, Defesa, Evasão (Base), Repelente, Ouro

    player->inventario = (Inventario){criaLista()};

    player->action = IDLE;

    player->isControlled = true;

    player->pilha = criarPilha();

    if(allPlayers != NULL) inserirFim(allPlayers, player);

    return player;
}

void Player_Copy(Player* playerFrom, Player* playerTo){
    strncpy(playerTo->name, playerFrom->name, MAX_STRSIZE);
    
    playerFrom->anim->frames = playerTo->anim->frames;

    Animation_PositionCopy(playerFrom->anim->position, playerTo->anim->position);
    Animation_ScaleCopy(playerFrom->anim->scale, playerTo->anim->scale);

    playerTo->spriteSheet = playerFrom->spriteSheet;

    playerTo->display = playerFrom->display;
    playerTo->deltaX = playerFrom->deltaX;

    playerTo->source = playerFrom->source;
    playerTo->destination = playerFrom->destination;

    playerTo->stepDistance = playerFrom->stepDistance;
    playerTo->characterChoice = playerFrom->characterChoice;

    playerTo->stats = playerFrom->stats;

    playerTo->inventario.utils = playerFrom->inventario.utils;

    playerTo->action = playerFrom->action;

    playerTo->isControlled = false;
}

Player* Player_CopyF(Player* playerFrom){
    Player* playerTo = Player_Init(playerFrom->source, playerFrom->destination, NULL);
    Player_Copy(playerFrom, playerTo);

    return playerTo;
}

Vector2 Player_GetCoords(Player* player){
    return player->coordinates;
}

void Player_SetStepSize(Player* player, float stepSize){
    player->stepDistance = stepSize;
}

void Player_Update(Player* player, float deltaTime){
    Player_UpdatePosition(player, deltaTime);
    Player_UpdateSprite(player, true, true);

    player->coordinates.x = player->destination.x / player->stepDistance;
    player->coordinates.y = player->destination.y / player->stepDistance;
}

void Player_UpdateCoords(Player* player){
    player->coordinates.x = player->destination.x / player->stepDistance;
    player->coordinates.y = player->destination.y / player->stepDistance;
}

void Player_SetMoveSet(Player* player, MoveSet moveSet){
    player->keys = moveSet;
}

void Player_UpdatePosition(Player* player, float deltaTime){
    if(!player->anim->position->animating && !player->locked){
        if(IsKeyDown(player->keys.up)) Player_StepTo(player, (Vector2){0,-1}, true);
        if(IsKeyDown(player->keys.down)) Player_StepTo(player, (Vector2){0,1}, true);
        if(IsKeyDown(player->keys.left)) Player_StepTo(player, (Vector2){-1,0}, true);
        if(IsKeyDown(player->keys.right)) Player_StepTo(player, (Vector2){1,0}, true);
    }

    Vector2 current = UpdateItemPosition(player->anim->position, deltaTime);

    player->destination.x = current.x;
    player->destination.y = current.y;
}

void Player_Resize(Player* player, float ratio, float interval){
    ResizeItem(player->anim->scale, ratio, interval);
}

void Player_UpdateSize(Player* player, float deltaTime){
    player->destination = UpdateItemSize(player->anim->scale, player->destination, deltaTime);
}

void Player_ChangeCharacter(Player* player){
    player->characterChoice = !player->characterChoice;
}

Turn Player_UpdateSprite(Player* player, bool reverse, bool loop){
    Turn animState = {false, false, false, false};

    player->anim->frames.framesCounter++;

    if ((player->anim->frames.framesCounter >= (60/player->anim->frames.framesSpeed)) && player->anim->frames.animating){
        player->anim->frames.framesCounter = 0;
        player->anim->frames.currentFrame += player->anim->frames.animationDirection;

        if(reverse){
            if (player->anim->frames.currentFrame > player->anim->frames.amountOfFrames - 1){
                player->anim->frames.animationDirection = -1;
                player->anim->frames.currentFrame = player->anim->frames.amountOfFrames - 2;
            }
            if (player->anim->frames.currentFrame < 0){
                player->anim->frames.animationDirection = 1;
                player->anim->frames.currentFrame = 1;
                animState.animationEnd = true;
            }
        }
        else{
            if(player->anim->frames.currentFrame > player->anim->frames.amountOfFrames - 1){
                animState.animationEnd = true;
                player->anim->frames.currentFrame = player->anim->frames.amountOfFrames - 1;

                if(loop){
                    player->anim->frames.currentFrame = 0;
                }
            }
        }

        if (player->anim->frames.currentFrame != 0) player->anim->frames.padding += player->anim->frames.framesPadding * player->anim->frames.animationDirection;
        else player->anim->frames.padding = 0.0f;

        player->display.x = (float)player->anim->frames.currentFrame*player->deltaX + player->anim->frames.padding;
    }


    if(!player->anim->frames.animating && player->isControlled){
        player->anim->frames.framesCounter = 0;
        player->anim->frames.currentFrame = 1;
        player->display.x = (float)player->anim->frames.currentFrame*160.0f + 10.0f;
        player->anim->frames.animationDirection = -1;
    }

    int character = (player->characterChoice) ? 2020.0f : 0.0f;

    if(!player->anim->position->animating && !player->locked && player->isControlled){
        if(IsKeyDown(player->keys.up) || player->moving.up) player->display.y = 450.0f;
        if(IsKeyDown(player->keys.down) || player->moving.down) player->display.y = 120.0f;
        if(IsKeyDown(player->keys.left) || player->moving.left) player->display.y = 780.0f;
        if(IsKeyDown(player->keys.right) || player->moving.right) player->display.y = 1110.0f;
    }

    bool allKeys = (IsKeyDown(player->keys.up) || IsKeyDown(player->keys.down) || IsKeyDown(player->keys.left) || IsKeyDown(player->keys.right));

    player->anim->frames.animating = (allKeys || player->anim->position->animating) ? true : false;

    player->source.x = player->display.x;
    player->source.y = player->display.y + character;

    animState.animating = player->anim->frames.animating;
    return animState;
}

Turn Player_UpdateSpriteExt(Player* player, bool reverse, bool loop, int reverseFrames, bool leaveAnim){
    Turn animState = {false, false, false, false};

    player->anim->frames.framesCounter++;

    if ((player->anim->frames.framesCounter >= (60/player->anim->frames.framesSpeed)) && player->anim->frames.animating){
        player->anim->frames.framesCounter = 0;
        player->anim->frames.currentFrame += player->anim->frames.animationDirection;

        if(reverse){
            if (player->anim->frames.currentFrame > player->anim->frames.amountOfFrames - 1){
                player->anim->frames.animationDirection = -1;
                player->anim->frames.currentFrame = player->anim->frames.amountOfFrames - 2;
            }
            if (player->anim->frames.currentFrame < player->anim->frames.amountOfFrames - reverseFrames - 1 && !leaveAnim){
                player->anim->frames.animationDirection = 1;
                player->anim->frames.currentFrame = player->anim->frames.amountOfFrames - reverseFrames;
            }
            if (player->anim->frames.currentFrame <= 0){
                player->anim->frames.animationDirection = 1;
                player->anim->frames.currentFrame = 0;
                animState.animationEnd = true;
            }
        }
        else{
            if(player->anim->frames.currentFrame > player->anim->frames.amountOfFrames - 1){
                animState.animationEnd = true;
                player->anim->frames.currentFrame = player->anim->frames.amountOfFrames - 1;

                if(loop){
                    player->anim->frames.currentFrame = 0;
                }
            }
        }

        if (player->anim->frames.currentFrame != 0) player->anim->frames.padding += player->anim->frames.framesPadding * player->anim->frames.animationDirection;
        else player->anim->frames.padding = 0.0f;

        player->display.x = (float)player->anim->frames.currentFrame*player->deltaX + player->anim->frames.padding;
    }


    if(!player->anim->frames.animating && player->isControlled){
        player->anim->frames.framesCounter = 0;
        player->anim->frames.currentFrame = 1;
        player->display.x = (float)player->anim->frames.currentFrame*160.0f + 10.0f;
        player->anim->frames.animationDirection = -1;
    }

    int character = (player->characterChoice) ? 2020.0f : 0.0f;

    if(!player->anim->position->animating && !player->locked && player->isControlled){
        if(IsKeyDown(player->keys.up) || player->moving.up) player->display.y = 450.0f;
        if(IsKeyDown(player->keys.down) || player->moving.down) player->display.y = 120.0f;
        if(IsKeyDown(player->keys.left) || player->moving.left) player->display.y = 780.0f;
        if(IsKeyDown(player->keys.right) || player->moving.right) player->display.y = 1110.0f;
    }

    bool allKeys = (IsKeyDown(player->keys.up) || IsKeyDown(player->keys.down) || IsKeyDown(player->keys.left) || IsKeyDown(player->keys.right));

    player->anim->frames.animating = (allKeys || player->anim->position->animating) ? true : false;

    player->source.x = player->display.x;
    player->source.y = player->display.y + character;

    animState.animating = player->anim->frames.animating;
    return animState;
}

void Player_ChangeSprite(Player* player, int amountOfFrames, int pos){
    if((int)player->display.y == (int)(pos * player->deltaY)) return;

    player->anim->frames.amountOfFrames = amountOfFrames;
    player->display.y = pos * player->deltaY;
    player->anim->frames.currentFrame = 0;
    player->display.x = (float)player->anim->frames.currentFrame*player->deltaX + player->anim->frames.padding;
    player->anim->frames.framesCounter = 0;
}

void Player_StepTo(Player* player, Vector2 direction, bool updateSprite){
    if(abs((int)direction.x) == abs((int)direction.y)) return;
    
    Vector2 finalPoint = (Vector2){player->destination.x + player->stepDistance * direction.x, player->destination.y + player->stepDistance * direction.y};
    Vector2 startPoint = (Vector2){player->destination.x, player->destination.y};

    player->moving.up = (direction.y == -1) ? true : false;
    player->moving.down = (direction.y == 1) ? true : false;
    player->moving.left = (direction.x == -1) ? true : false;
    player->moving.right = (direction.x == 1) ? true : false;

    if(updateSprite) Player_UpdateSprite(player, true, true);

    MoveItemTo(player->anim->position, startPoint, finalPoint, 0.3f);
}

void Player_MoveTo(Player* player, Vector2 newPos, float interval){
    MoveItemTo(player->anim->position, (Vector2){player->destination.x, player->destination.y}, newPos, interval);
}

void Player_SetSpriteSheet(Player* player, const char* spriteSheet){
    player->spriteSheet = LoadTexture(spriteSheet);
}

void Player_SetSourceRec(Player* player, Rectangle newSource){
    player->source = newSource;
    player->display = (Vector2){newSource.x, newSource.y};
}

void Player_SetDestRec(Player* player, Rectangle newDest){
    player->destination = newDest;
}

void Player_SetSpriteSize(Player* player, int width, int height){
    player->destination.width = width;
    player->destination.height = height;
}

void Player_Draw(Player* player){
    DrawTexturePro(player->spriteSheet, player->source, player->destination, (Vector2){0,0}, 0.0f, WHITE);
}

/////////////////////////////////////////////////////////////////////////

bool isLife50(Player* player){
    return (player->stats.health >= player->stats.maxHealth*1/2);
}

bool isLife30(Player* player){
    return (player->stats.health >= player->stats.maxHealth*3/10);
}

//////////////////////////////////////////////////////////////////////////

void Player_TakeDamage(Player* player, float damage){
    float finalDamage = (player->stats.defending) ? ((1 - player->stats.defense) * damage) : damage;

    player->stats.health -= finalDamage;

    if(player->stats.health < 0) player->stats.health = 0;
}

void Player_UpdateAtk(Player* player, float newAtk){
    player->stats.attack = newAtk;
}

void Player_UpdateDef(Player* player, float newDef){
    player->stats.defense = newDef;
}

void Player_getHealing(Player* player, float heal){
    if(player->stats.health + heal > player->stats.maxHealth) player->stats.health = player->stats.maxHealth;
    else player->stats.health += heal;
}

void Player_Print(Player* player){
    player->stats.health += 1.0f;
}

//////////////////////////////////////////////////////////////////////////////////////

Rectangle Player_getDestRec(Player* player){
    return player->destination;
}

Vector2 Player_getDisplay(Player* player){
    return player->display;
}

Decision Player_getAction(Player* player){
    return player->action;
}

float Player_getDeltaY(Player* player){
    return player->deltaY;
}

PositionAnimation* Player_getAnimationPosition(Player* player){
    return player->anim->position;
}

ScaleAnimation* Player_getAnimationScale(Player* player){
    return player->anim->scale;
}

FramesAnimation Player_getAnimationFrames(Player* player){
    return player->anim->frames;
}

Stats Player_getStats(Player* player){
    return player->stats;
}

Lista* Player_getInventarioUtils(Player* player){
    return player->inventario.utils;
}

bool Player_getAnimationPositionAnimating(Player* player){
    return player->anim->position->animating;
}

const char* Player_getName(Player* player){
    return player->name;
}

int Player_getAnimationFramesBaseSpeed(Player* player){
    return player->anim->frames.baseSpeed;
}

Lista* Player_getInventario(Player* player){
    return player->inventario.utils;
}

Pilha* Player_getPilha(Player* player){
    return player->pilha;
}

MoveSet Player_getMoveSet(Player* player){
    return player->keys;
}

bool Player_getLocked(Player* player){
    return player->locked;
}

Texture2D Player_getSprite(Player* player){
    return player->spriteSheet;
}

//////////////////////////////////////////////////////////////////////////////////////

void Player_setAction(Player* player, Decision decision){
    player->action = decision;
}

void Player_setDisplay(Player* player, Vector2 newDisplay){
    player->display = newDisplay;
}

void Player_setDeltaX(Player* player, float newDelta){
    player->deltaX = newDelta;
}

void Player_setDeltaY(Player* player, float newDelta){
    player->deltaY = newDelta;
}

void Player_setAnimationFrames(Player* player, FramesAnimation frames){
    player->anim->frames = frames;
}

void Player_setCharacter(Player* player, float point){
    player->characterChoice = point;
}

void Player_setAnimationFramesAnimating(Player* player, bool state){
    player->anim->frames.animating = state;
}

void Player_setLocked(Player* player, bool locked){
    player->locked = locked;
}

void Player_setName(Player* player, const char* name){
    strncpy(player->name, name, MAX_STRSIZE);
}

void Player_setControl(Player* player, bool state){
    player->isControlled = state;
}

void Player_setDefense(Player* player, bool state){
    player->stats.defending = state;
}

void Player_setRepelent(Player* player, int amount){
    player->stats.repelent = amount;
}

void Player_setAnimationFramesBaseSpeed(Player* player, int baseSpeed){
    player->anim->frames.baseSpeed = baseSpeed;
}

void Player_setAnimationFramesSpeed(Player* player, int frameSpeed){
    player->anim->frames.framesSpeed = frameSpeed;
}

void Player_setAnimationFramesDirection(Player* player, int direction){
    player->anim->frames.animationDirection = direction;
}

void Player_setStats(Player* player, Stats stats){
    player->stats = stats;
}

void Player_setAttack(Player* player, float attack){
    player->stats.attack = attack;
}

void Player_addGold(Player* player, int amount){
    player->stats.gold += amount;
}

void Player_subRepelent(Player* player, int amount){
    player->stats.repelent = (player->stats.repelent >= amount) ? player->stats.repelent - amount : 0;
}

bool Player_tryRun(Player* player){
    return (rand()%100 <= (int)(player->stats.evasionRate*100));
}

bool Player_dodged(Player* player){
    return (rand()%100 <= (int)(player->stats.dodge*100));
}

//////////////////////////////////////////////////////////////////////

void Player_InitList(){
    if(allPlayers == NULL) allPlayers = criaLista();
}

void freeTexture_Player(const void* item){
    UnloadTexture(((const Player*)item)->spriteSheet);
}

void Player_Free(){
    percorrerLista(allPlayers, freeTexture_Player);
    limparLista(allPlayers, true);
}