#ifndef _Button_h_
#define _Button_h_

#include "Utils.h"
#include "Delimiters.h"
#include "ImageObject.h"
#include "Lista.h"

typedef struct ImageObject ImageObject;

typedef struct Pattern{
    Color baseColor;
    Color borderColor;
    Color hoverColor;
    Color borderHoverColor;
    Color backgroundColor;
} Pattern;

typedef struct ActivePattern{
    Color base;
    Color border;
    Color background;
} ActivePattern;

typedef struct Button{
    float x, y;
    float width, height;
    float scale_text;
    char text[MAX_STRSIZE];
    int fontsize;
    int borda;

    bool active;

    ImageObject* icon;
    Vector2 padding;

    double xRatio;
    double yRatio;

    Pattern colors;
    ActivePattern activeColor;
} Button;

Button* Button_Init(const char* txt);

void Button_SetText(Button* btn, const char* text);

void Button_LoadIcon(Button* btn, ImageObject* img, bool centralize);

void Button_SetPattern(Button* btn, Pattern colors);

Pattern Button_GetPattern(Button* btn);

ActivePattern Button_GetActivePattern(Button* btn);

void Button_Deactivate(Button* btn);

void Button_Activate(Button* btn);

void Button_SwitchActive(Button* btn);

void Button_Scale(Button* btn, float scale);

void Button_FitSizeToText(Button* btn, int fontsize, Vector2 padding);

void Button_Pos(Button* btn, Vector2 pos);

void LinkButtonColors(Button* btn1, Button* btn2, int opacity, Color textColor);

bool Button_Hovering(Button* btn, Vector2 cursorPos);

bool Button_IsPressed(Button* btn, Vector2 cursorPos);

void Button_Draw(Button* btn);

void Button_DrawIcon(Button* btn);

void Button_InitList();

void Button_Free();

#endif