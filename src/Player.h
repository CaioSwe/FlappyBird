#ifndef _Player_h_
#define _Player_h_

#include "Utils.h"
#include "Delimiters.h"
#include "Lista.h"
#include "Animation.h"
#include "Pilha.h"

typedef enum Decision{
    IDLE,
    ATTACK,
    HURT,
    HEAL,
    DEFEND,
    WALK,
    DEAD
} Decision;

typedef struct MoveSet{
    int up;
    int down;
    int left;
    int right;
} MoveSet;

typedef struct Moving Moving;

typedef struct Animation Animation;

typedef struct Stats{
    float maxHealth;
    float health;
    float attack;
    float defense;
    float evasionRate;
    float dodge;

    bool attacking;
    bool defending;

    int repelent;

    int gold;
} Stats;

typedef struct Inventario Inventario;

typedef struct Player Player;

Player* Player_Init(Rectangle source, Rectangle destination, const char* spriteSheet);

void Player_Copy(Player* playerFrom, Player* playerTo);

Player* Player_CopyF(Player* playerFrom);

void Player_UpdateAtk(Player* player, float newAtk);

void Player_UpdateDef(Player* player, float newDef);

Vector2 Player_GetCoords(Player* player);

void Player_SetStepSize(Player* player, float stepSize);

void Player_Update(Player* player, float deltaTime);

void Player_UpdateCoords(Player* player);

void Player_SetMoveSet(Player* player, MoveSet moveSet);

void Player_UpdatePosition(Player* player, float deltaTime);

void Player_UpdateSize(Player* player, float deltaTime);

void Player_ChangeCharacter(Player* player);

Turn Player_UpdateSprite(Player* player, bool reverse, bool loop);

Turn Player_UpdateSpriteExt(Player* player, bool reverse, bool loop, int reverseFrames, bool leaveAnim);

void Player_ChangeSprite(Player* player, int amountOfFrames, int pos);

void Player_StepTo(Player* player, Vector2 direction, bool updateSprite);

void Player_MoveTo(Player* player, Vector2 newPos, float interval);

void Player_Resize(Player* player, float ratio, float interval);

void Player_SetSpriteSheet(Player* player, const char* spriteSheet);

void Player_SetSourceRec(Player* player, Rectangle newSource);

void Player_SetDestRec(Player* player, Rectangle newDest);

void Player_SetSpriteSize(Player* player, int width, int height);

void Player_Draw(Player* player);

///////////////////////////////////////////////////////////////////////

bool isLife50(Player* player);

bool isLife30(Player* player);

//////////////////////////////////////////////////////////////////////////

void Player_TakeDamage(Player* player, float damage);

void Player_UpdateAtk(Player* player, float newAtk);

void Player_UpdateDef(Player* player, float newDef);

void Player_getHealing(Player* player, float heal);

void Player_Print(Player* player);

////////////////////////////////////////////////////////////////////////////

Rectangle Player_getDestRec(Player* player);

Vector2 Player_getDisplay(Player* player);

Decision Player_getAction(Player* player);

float Player_getDeltaY(Player* player);

PositionAnimation* Player_getAnimationPosition(Player* player);

ScaleAnimation* Player_getAnimationScale(Player* player);

FramesAnimation Player_getAnimationFrames(Player* player);

Stats Player_getStats(Player* player);

Lista* Player_getInventarioUtils(Player* player);

bool Player_getAnimationPositionAnimating(Player* player);

const char* Player_getName(Player* player);

int Player_getAnimationFramesBaseSpeed(Player* player);

Lista* Player_getInventario(Player* player);

Pilha* Player_getPilha(Player* player);

MoveSet Player_getMoveSet(Player* player);

bool Player_getLocked(Player* player);

Texture2D Player_getSprite(Player* player);

/////////////////////////////////////////////////////////////////////////////

void Player_setAction(Player* player, Decision decision);

void Player_setDisplay(Player* player, Vector2 newDisplay);

void Player_setDeltaX(Player* player, float newDelta);

void Player_setDeltaY(Player* player, float newDelta);

void Player_setAnimationFrames(Player* player, FramesAnimation frames);

void Player_setCharacter(Player* player, float point);

void Player_setAnimationFramesAnimating(Player* player, bool state);

void Player_setLocked(Player* player, bool locked);

void Player_setName(Player* player, const char* name);

void Player_setControl(Player* player, bool state);

void Player_setDefense(Player* player, bool state);

void Player_setRepelent(Player* player, int amount);

void Player_setAnimationFramesBaseSpeed(Player* player, int baseSpeed);

void Player_setAnimationFramesSpeed(Player* player, int frameSpeed);

void Player_setAnimationFramesDirection(Player* player, int direction);

void Player_setStats(Player* player, Stats stats);

void Player_setAttack(Player* player, float attack);

void Player_addGold(Player* player, int amount);

void Player_subRepelent(Player* player, int amount);

bool Player_tryRun(Player* player);

bool Player_dodged(Player* player);

/////////////////////////////////////////////////////////////////////////////

void Player_InitList();

void Player_Free();

// void freeTexture_Player(const void* item);

#endif