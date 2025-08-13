#include "TextObject.h"

static Lista* allTextObjects = NULL;

TextObject* Text_Init(const char* text){
    TextObject* txt = (TextObject*)malloc(sizeof(TextObject));
    
    strncpy(txt->text, text, MAX_STRSIZE);
    txt->color = WHITE;
    txt->fontsize = 10;
    txt->x = txt->y = 0;
    txt->collision = false;
    txt->rectangle = (Rectangle){txt->x, txt->y, MeasureText(txt->text, txt->fontsize), txt->fontsize};

    if(allTextObjects != NULL) inserirFim(allTextObjects, txt);

    return txt;
}

void Text_Set(TextObject* txt, const char* text){
    strncpy(txt->text, text, MAX_STRSIZE);
}

void Text_Pos(TextObject* txt, Vector2 pos){
    txt->x = pos.x;
    txt->y = pos.y;
}

void Text_Scale(TextObject* txt, float scaling){
    int basefontsize = 20;
    float scale_font = (float)(GetScreenWidth() * scaling) / MeasureText(txt->text, basefontsize);
    txt->fontsize = basefontsize * scale_font;
}

void Text_DrawS(TextObject* txt){
    txt->rectangle = (Rectangle){txt->x, txt->y, MeasureText(txt->text, txt->fontsize), txt->fontsize};
    DrawText(txt->text, txt->x, txt->y, txt->fontsize, txt->color);
}

void Text_DrawX(TextObject* txt, float rectX, float rectY){
    txt->rectangle = (Rectangle){rectX, rectY, txt->rectangle.width, txt->rectangle.height};
    DrawText(txt->text, txt->x, txt->y, txt->fontsize, txt->color);
}

void Text_InitList(){
    if(allTextObjects == NULL) allTextObjects = criaLista();
}

void Text_Free(){
    limparLista(allTextObjects, true);
}