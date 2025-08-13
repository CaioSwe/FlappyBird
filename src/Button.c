#include "Button.h"

static Lista* allButtons = NULL;

static bool hoveringButton = false;

Button* Button_Init(const char* txt){
    Button* btn = (Button*)malloc(sizeof(Button));

    btn->x = 0;
    btn->y = 0;

    btn->width = 50;
    btn->height = 50;
    
    btn->scale_text = 1.0f;
    btn->fontsize = 30;
    btn->borda = 3;

    btn->padding = (Vector2){0,0};
    btn->icon = NULL;
    btn->active = true;

    strncpy(btn->text, txt, MAX_STRSIZE);

    btn->colors = (Pattern){WHITE, BLACK, WHITE, BLACK, (Color){0, 0, 0, 150}};
    btn->activeColor = (ActivePattern){WHITE, BLACK, BLACK};

    if(allButtons != NULL) inserirFim(allButtons, btn);

    return btn;
}

void Button_SetText(Button* btn, const char* text){
    strncpy(btn->text, text, MAX_STRSIZE);
}

void Button_LoadIcon(Button* btn, ImageObject* img, bool centralize){
    btn->icon = Image_Init(NULL);
    Image_Copy(img, btn->icon, true);

    btn->icon->destination.width = btn->height*0.7;
    btn->icon->destination.height = btn->height*0.7;

    if(centralize) btn->x -= ((btn->icon->destination.width / 2) * 1.2f);
    btn->width += btn->icon->destination.width * 1.5f;

    btn->icon->destination.x = btn->x + (btn->width * 1/7 - btn->icon->destination.width/2);
    btn->icon->destination.y = btn->y + (btn->height/2 - btn->icon->destination.height/2);
}

void Button_SetPattern(Button* btn, Pattern colors){
    btn->colors = colors;
    btn->activeColor = (ActivePattern){colors.baseColor, colors.borderColor, colors.backgroundColor};
}

Pattern Button_GetPattern(Button* btn){
    return btn->colors;
}

ActivePattern Button_GetActivePattern(Button* btn){
    return btn->activeColor;
}

void Button_Deactivate(Button* btn){
    btn->active = false;
}

void Button_Activate(Button* btn){
    btn->active = true;
}

void Button_SwitchActive(Button* btn){
    btn->active = !btn->active;
}

void Button_Scale(Button* btn, float scale){
    btn->width *= scale;
    btn->height *= scale;
    btn->borda *= scale;
}

void Button_FitSizeToText(Button* btn, int fontsize, Vector2 padding){
    btn->width = MeasureText(btn->text, fontsize) * 1.1f;
    btn->height = fontsize;
    btn->fontsize = fontsize;
    btn->borda = btn->height * 0.1f;

    btn->padding = padding;
}

void Button_Pos(Button* btn, Vector2 pos){
    btn->x = pos.x;
    btn->y = pos.y;

    if(btn->icon != NULL){
        btn->icon->destination.x = btn->x + (btn->width * 1/7 - btn->icon->destination.width/2);
    btn->icon->destination.y = btn->y + (btn->height/2 - btn->icon->destination.height/2);
    }
}

void LinkButtonColors(Button* btn1, Button* btn2, int opacity, Color textColor){
    ActivePattern active = Button_GetActivePattern(btn2);
    Color activeBorder = darkenColor(active.border, 0.7f);

    Color opActive = (Color){activeBorder.r, activeBorder.g, activeBorder.b, opacity};

    Button_SetPattern(btn1, (Pattern){(Color){textColor.r - activeBorder.r, textColor.g - activeBorder.g, textColor.b - activeBorder.b, opacity}, (Color){0, 0, 0, 0}, BLACK, BLACK, opActive});
}

bool Button_Hovering(Button* btn, Vector2 cursorPos){
    Rectangle rect = {btn->x, btn->y, btn->width, btn->height};

    return (CheckCollisionPointRec(cursorPos, rect));
}

bool Button_IsPressed(Button* btn, Vector2 cursorPos){
    if(btn->active) hoveringButton = Button_Hovering(btn, cursorPos);
    else hoveringButton = false;
    
    return hoveringButton && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

void Button_Draw(Button* btn){
    Rectangle rect = {btn->x - btn->padding.x/2, btn->y - btn->padding.y/2, btn->width + btn->padding.x, btn->height + btn->padding.y};
    Vector2 mousePos = GetMousePosition();

    DrawRectangleRec(rect, btn->colors.backgroundColor);

    if (!Button_Hovering(btn, mousePos) || !btn->active){
        btn->activeColor = (ActivePattern){btn->colors.baseColor, btn->colors.borderColor, btn->colors.backgroundColor};
        DrawRectangleLinesEx(rect, btn->borda, btn->colors.borderColor);
        DrawText(btn->text, btn->x + btn->width / 2 - MeasureText(btn->text, btn->fontsize) / 2, btn->y + btn->height / 2 - btn->fontsize / 2, btn->fontsize, btn->colors.baseColor);
    } else{
        btn->activeColor = (ActivePattern){btn->colors.hoverColor, btn->colors.borderHoverColor, btn->colors.backgroundColor};
        DrawRectangleRec(rect, btn->colors.borderHoverColor);
        DrawText(btn->text, btn->x + btn->width / 2 - MeasureText(btn->text, btn->fontsize) / 2, btn->y + btn->height / 2 - btn->fontsize / 2, btn->fontsize, btn->colors.hoverColor);
    }
}

void Button_DrawIcon(Button* btn){
    Rectangle rect = {btn->x - btn->padding.x/2, btn->y - btn->padding.y, btn->width + btn->padding.x, btn->height + btn->padding.y};
    Vector2 mousePos = GetMousePosition();

    DrawRectangleRec(rect, btn->colors.backgroundColor);

    if (!Button_Hovering(btn, mousePos) || !btn->active){
        btn->activeColor = (ActivePattern){btn->colors.baseColor, btn->colors.borderColor, btn->colors.backgroundColor};
        DrawRectangleLinesEx(rect, btn->borda, btn->colors.borderColor);
        DrawText(btn->text, btn->x + btn->width * 3/5 - MeasureText(btn->text, btn->fontsize) / 2, btn->y + btn->height / 2 - btn->fontsize / 2, btn->fontsize, btn->colors.baseColor);
        btn->icon->color = btn->colors.baseColor;
    } else{
        btn->activeColor = (ActivePattern){btn->colors.hoverColor, btn->colors.borderHoverColor, btn->colors.backgroundColor};
        DrawRectangleRec(rect, btn->colors.borderHoverColor);
        DrawText(btn->text, btn->x + btn->width * 3/5 - MeasureText(btn->text, btn->fontsize) / 2, btn->y + btn->height / 2 - btn->fontsize / 2, btn->fontsize, btn->colors.hoverColor);
        btn->icon->color = btn->colors.hoverColor;
    }
    Image_DrawPro(btn->icon);
}

void Button_InitList(){
    if(allButtons == NULL) allButtons = criaLista();
}

void Button_Free() {
    limparLista(allButtons, true);
}