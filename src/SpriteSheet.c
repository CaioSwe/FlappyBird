#include "SpriteSheet.h"

static Lista* allSpriteSheets = NULL;

typedef struct Animation{
    PositionAnimation* position;
    ScaleAnimation* scale;
    FramesAnimation frames;
} Animation;

typedef struct SpriteSheet{
    Texture2D spriteSheet;
    Animation* anim;

    Rectangle source;
    Rectangle destination;

    Vector2 display;
    Vector2 delta;
} SpriteSheet;

SpriteSheet* SpriteSheet_Init(const char* path, FramesAnimation framesAnimation){
    SpriteSheet* spriteSheet = (SpriteSheet*)malloc(sizeof(SpriteSheet));

    spriteSheet->anim = (Animation*)malloc(sizeof(Animation));
    spriteSheet->anim->position = (PositionAnimation*)malloc(sizeof(PositionAnimation));
    spriteSheet->anim->scale = (ScaleAnimation*)malloc(sizeof(ScaleAnimation));
    
    if(path != NULL) spriteSheet->spriteSheet = LoadTexture(path);
    
    spriteSheet->anim->position->function = linearFunction;
    spriteSheet->anim->frames = framesAnimation;

    spriteSheet->source = (Rectangle){0, 0, spriteSheet->spriteSheet.width, spriteSheet->spriteSheet.height};
    spriteSheet->destination = (Rectangle){0, 0, 0, 0};
    spriteSheet->display = (Vector2){0, 0};
    spriteSheet->delta = (Vector2){0, 0};

    if(allSpriteSheets != NULL) inserirFim(allSpriteSheets, spriteSheet);

    return spriteSheet;
}

SpriteSheet* SpriteSheet_Copy(SpriteSheet* source){
    SpriteSheet* spriteSheet = SpriteSheet_Init(NULL, source->anim->frames);
    
    SpriteSheet_SetTexture(spriteSheet, source->spriteSheet);
    spriteSheet->source = source->source;
    spriteSheet->destination = source->destination;
    spriteSheet->display = source->display;
    spriteSheet->delta = source->delta;

    return spriteSheet;
}

Texture2D SpriteSheet_GetTexture(SpriteSheet* spriteSheet){
    return spriteSheet->spriteSheet;
}

void SpriteSheet_SetTexture(SpriteSheet* spriteSheet, Texture2D texture){
    spriteSheet->spriteSheet = texture;
    spriteSheet->source = (Rectangle){0, 0, spriteSheet->spriteSheet.width, spriteSheet->spriteSheet.height};
}

Turn SpriteSheet_UpdateSprite(SpriteSheet* spriteSheet, bool reverse, bool loop){
    Turn animState = {false, false, false, false};
    
    spriteSheet->anim->frames.framesCounter++;

    if ((spriteSheet->anim->frames.framesCounter >= (60/spriteSheet->anim->frames.framesSpeed)) && spriteSheet->anim->frames.animating){
        
        spriteSheet->anim->frames.framesCounter = 0;
        spriteSheet->anim->frames.currentFrame += spriteSheet->anim->frames.animationDirection;

        if(reverse){
            if (spriteSheet->anim->frames.currentFrame > spriteSheet->anim->frames.amountOfFrames - 1){
                spriteSheet->anim->frames.animationDirection = -1;
                spriteSheet->anim->frames.currentFrame = spriteSheet->anim->frames.amountOfFrames - 2;
            }
            if (spriteSheet->anim->frames.currentFrame < 0){
                spriteSheet->anim->frames.animationDirection = 1;
                spriteSheet->anim->frames.currentFrame = 1;
            }
        }
        else{
            if(spriteSheet->anim->frames.currentFrame > spriteSheet->anim->frames.amountOfFrames - 1){
                animState.animationEnd = true;
                spriteSheet->anim->frames.currentFrame = spriteSheet->anim->frames.amountOfFrames - 1;

                if(loop){
                    spriteSheet->anim->frames.currentFrame = 0;
                }
            }
        }

        if (spriteSheet->anim->frames.currentFrame != 0) spriteSheet->anim->frames.padding += spriteSheet->anim->frames.framesPadding * spriteSheet->anim->frames.animationDirection;
        else spriteSheet->anim->frames.padding = 0.0f;

        spriteSheet->display.x = (float)spriteSheet->anim->frames.currentFrame*spriteSheet->delta.x + spriteSheet->anim->frames.padding;
    }


    if(!spriteSheet->anim->frames.animating){
        spriteSheet->anim->frames.framesCounter = 0;
        spriteSheet->anim->frames.currentFrame = 0;
        spriteSheet->display.x = (float)spriteSheet->anim->frames.currentFrame*spriteSheet->delta.x;
    }

    spriteSheet->source.x = spriteSheet->display.x;
    spriteSheet->source.y = spriteSheet->display.y;

    animState.animating = spriteSheet->anim->frames.animating;
    return animState;
}

void SpriteSheet_Draw(SpriteSheet* spriteSheet){
    DrawTexturePro(spriteSheet->spriteSheet, spriteSheet->source, spriteSheet->destination, (Vector2){0,0}, 0.0f, WHITE);
}

void SpriteSheet_SetDisplay(SpriteSheet* spriteSheet, Vector2 display){
    spriteSheet->display = display;
}

void SpriteSheet_SetDelta(SpriteSheet* spriteSheet, Vector2 delta){
    spriteSheet->delta = delta;
}

void SpriteSheet_SetAnimationFrames(SpriteSheet* spriteSheet, FramesAnimation framesAnimation){
    spriteSheet->anim->frames = framesAnimation;
}

void SpriteSheet_SetSourceRec(SpriteSheet* spriteSheet, Rectangle source){
    spriteSheet->source = source;
}

void SpriteSheet_SetDestRec(SpriteSheet* spriteSheet, Rectangle dest){
    spriteSheet->destination = dest;
}

void SpriteSheet_setAnimationFramesAnimating(SpriteSheet* spriteSheet, bool state){
    spriteSheet->anim->frames.animating = state;
}

///////////////////////////////////////////////

Vector2 SpriteSheet_GetDisplay(SpriteSheet* spriteSheet){
    return spriteSheet->display;
}

Vector2 SpriteSheet_GetDelta(SpriteSheet* spriteSheet){
    return spriteSheet->delta;
}

FramesAnimation SpriteSheet_GetAnimationFrames(SpriteSheet* spriteSheet){
    return spriteSheet->anim->frames;
}

Rectangle SpriteSheet_GetSourceRec(SpriteSheet* spriteSheet){
    return spriteSheet->source;
}

Rectangle SpriteSheet_GetDestRec(SpriteSheet* spriteSheet){
    return spriteSheet->destination;
}

void SpriteSheet_InitList(){
    if(allSpriteSheets == NULL) allSpriteSheets = criaLista();
}

void freeTexture_SpriteSheet(const void* item){
    UnloadTexture(((const SpriteSheet*)item)->spriteSheet);
}

void SpriteSheet_Free(){
    percorrerLista(allSpriteSheets, freeTexture_SpriteSheet);
    limparLista(allSpriteSheets, true);
}