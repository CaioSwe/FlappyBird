#include "Input.h"

static Lista* allInputs = NULL;

Input* Input_Init(){
    Input* input = (Input*)malloc(sizeof(Input));

    input->length = 0;
    input->fontsize = 20;
    input->x = input->y = 0;
    input->error = false;
    input->text[0] = '\0';
    input->blip = false;
    input->lastUpdate = 0;

    if(allInputs != NULL) inserirFim(allInputs, input);

    return input;
}

void Input_Add(Input *input, int character){
    if (input->length < MAX_STRSIZE - 1){
        input->text[input->length] = (char)character;
        input->length++;
        input->text[input->length] = '\0';
    }
}

void Input_Delete(Input *input){
    if (input->length > 0){
        input->length--;
        input->text[input->length] = '\0';
    }
}

void Input_Clear(Input *input){
    input->length = 0;
    input->text[0] = '\0';
}

void Input_Editable(Input *input, bool turn){
    if (turn){
        int key = GetCharPressed();
        while (key > 0){
            if ((key == 32) || (key >= 65 && key <= 90) || (key >= 97 && key <= 122)){
                if(Input_CheckMaxLength(input, input->maxLength)){
                    Input_Add(input, key);
                    input->error = false;
                }
            }
            key = GetCharPressed();
        }
    }
    if (IsKeyPressed(KEY_BACKSPACE)){
        Input_Delete(input);
        input->error = false;
    }
}

bool Input_CheckMinLength(Input *input, int minLength){
    if (input->length < minLength){
        Input_RaiseError(input, TextFormat("%d ou mais caracteres.", minLength), RED);
        return false;
    }
    return true;
}

bool Input_CheckMaxLength(Input *input, int maxLength){
    if (input->length > maxLength){
        Input_RaiseError(input, TextFormat("%d ou menos caracters.", maxLength), RED);
        return false;
    }
    return true;
}

void Input_RaiseError(Input *input, const char* msgErro, Color errorColor){
    input->error = true;
    input->errorColor = errorColor;
    snprintf(input->errorText, sizeof(input->errorText), msgErro);
    input->fontsizeErrorText = input->fontsize * 0.6;
    input->xErrorText = input->x + MeasureText(input->text, input->fontsize) / 2 - MeasureText(input->errorText, input->fontsizeErrorText) / 2;
}

void Input_Draw(Input *input){
    DrawText(input->text, input->x, input->y, input->fontsize, WHITE);
    
    if (input->error){
        DrawText(input->errorText, input->xErrorText, input->y + input->fontsize *1.6f, input->fontsizeErrorText, input->errorColor);
    }
}

void Input_DrawBox(Input *input){
    //DrawRectangle(input->x * 0.98f, input->y, MeasureText(input->text, input->fontsize) + input->x * 0.04f, input->fontsize, (Color){100,100,100,50});
    if (input->blip){
        int blip_x = input->x + (MeasureText(input->text, input->fontsize));
        if (input->length == 0){
            blip_x = input->x - (MeasureText("a", input->fontsize))/2;
        }
        DrawRectangle(blip_x, input->y + input->fontsize, MeasureText("e", input->fontsize), 5, WHITE);
    }
}

void Input_InitList(){
    if(allInputs == NULL) allInputs = criaLista();
}

void Input_Free(){
    limparLista(allInputs, true);
}