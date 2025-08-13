#ifndef _SpriteSheet_h_
#define _SpriteSheet_h_

#include "ImageObject.h"
#include "Delimiters.h"
#include "Animation.h"
#include "Lista.h"

typedef struct Animation Animation;

typedef struct SpriteSheet SpriteSheet;

SpriteSheet* SpriteSheet_Init(const char* path, FramesAnimation framesAnimation);

SpriteSheet* SpriteSheet_Copy(SpriteSheet* source);

Texture2D SpriteSheet_GetTexture(SpriteSheet* spriteSheet);

void SpriteSheet_SetTexture(SpriteSheet* spriteSheet, Texture2D texture);

Turn SpriteSheet_UpdateSprite(SpriteSheet* spriteSheet, bool reverse, bool loop);

void SpriteSheet_SetDisplay(SpriteSheet* spriteSheet, Vector2 display);

void SpriteSheet_SetDelta(SpriteSheet* spriteSheet, Vector2 delta);

void SpriteSheet_SetAnimationFrames(SpriteSheet* spriteSheet, FramesAnimation framesAnimation);

void SpriteSheet_SetSourceRec(SpriteSheet* spriteSheet, Rectangle source);

void SpriteSheet_SetDestRec(SpriteSheet* spriteSheet, Rectangle dest);

void SpriteSheet_setAnimationFramesAnimating(SpriteSheet* spriteSheet, bool state);

void SpriteSheet_Draw(SpriteSheet* spriteSheet);

///////////////////////////////////////////////

Vector2 SpriteSheet_GetDisplay(SpriteSheet* spriteSheet);

Vector2 SpriteSheet_GetDelta(SpriteSheet* spriteSheet);

FramesAnimation SpriteSheet_GetAnimationFrames(SpriteSheet* spriteSheet);

Rectangle SpriteSheet_GetSourceRec(SpriteSheet* spriteSheet);

Rectangle SpriteSheet_GetDestRec(SpriteSheet* spriteSheet);

///////////////////////////////////////////////

void SpriteSheet_InitList();

void SpriteSheet_Free();

// void freeTexture_SpriteSheet(const void* item);

#endif