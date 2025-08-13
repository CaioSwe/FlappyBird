#ifndef _TextObject_h_
#define _TextObject_h_

#include "Utils.h"
#include "Delimiters.h"
#include "Lista.h"

typedef struct TextObject{
    char text[MAX_STRSIZE];
    Color color;
    int fontsize;
    float x, y;
    bool collision;
    Rectangle rectangle;
} TextObject;

TextObject* Text_Init(const char* text);

void Text_Set(TextObject* txt, const char* text);

void Text_Pos(TextObject* txt, Vector2 pos);

void Text_Scale(TextObject* txt, float scaling);

void Text_DrawS(TextObject* txt);

void Text_DrawX(TextObject* txt, float rectX, float rectY);

void Text_InitList();

void Text_Free();

#endif