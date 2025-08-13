#ifndef _Input_h_
#define _Input_h_

#include "Utils.h"
#include "Lista.h"
#include "Delimiters.h"

typedef struct{
    int x;
    int y;
    int length;
    int fontsize;
    char text[MAX_STRSIZE];
    int maxLength;

    bool blip;
    int lastUpdate;

    bool error;
    char errorText[MAX_STRSIZE];
    int xErrorText;
    int fontsizeErrorText;
    Color errorColor;
} Input;

Input* Input_Init();

void Input_Add(Input *input, int character);

void Input_Delete(Input *input);

void Input_Clear(Input *input);

void Input_Editable(Input *input, bool turn);

bool Input_CheckMinLength(Input *input, int minLength);

bool Input_CheckMaxLength(Input *input, int maxLength);

void Input_RaiseError(Input *input, const char* msgErro, Color errorColor);

void Input_Draw(Input *input);

void Input_DrawBox(Input *input);

void Input_InitList();

void Input_Free();

#endif