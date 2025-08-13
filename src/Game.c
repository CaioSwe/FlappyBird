#include "Game.h"

void LoadingDraw(TextObject* loading){
    BeginDrawing();
        ClearBackground(BLACK);
        Text_DrawS(loading);
    EndDrawing();
        
    WaitTime((double)rand()/(double)RAND_MAX);
}

void LoadingScreen(){
    srand(time(NULL));
    
    TextObject* loading = Text_Init("Loading");

    Text_Scale(loading, 0.2f);
    loading->y = GetScreenHeight() - loading->fontsize - loading->fontsize*1/2;
    loading->x = loading->fontsize*1/2;

    double chance = 0;

    do{
        LoadingDraw(loading);
        Text_Set(loading, TextFormat("%s.", loading));
        chance -= 0.05f;
    }while((double)rand()/(double)RAND_MAX < chance);

    free(loading);
}

void BlackIn(int *opacity){
    if (*opacity > 0){
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), (Color){0,0,0,*opacity});
        *opacity = (*opacity < 3) ? 0 : *opacity - 3;
    }
}

void Blackout(){
    int j = 0;
    while(j < 255){
        BeginDrawing();
            DrawRectangle(0,0,GetScreenWidth(), GetScreenHeight(), (Color) {0,0,0,j});
        EndDrawing();
        j += 9;
    }
}


void changeScreen(int (*screen)()){
    Blackout();
    LoadingScreen();

    screen();
}

void changeScreenItem(int (*screen)(Player*), Player* item){
    Blackout();
    LoadingScreen();

    screen(item);
}