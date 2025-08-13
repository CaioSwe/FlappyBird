#include "Gif.h"

static Lista* allGifs = NULL;

Gif* Gif_Init(const char* path, const char* ext, int numFrames){
    Gif* gif = (Gif*)malloc(sizeof(Gif));
    
    gif->numFrames = numFrames;

    gif->image = criaLista();

    for (int i = 0; i < numFrames; i++){
        char filename[64];
        sprintf(filename, "%sframe%d%s", path, i, ext);
        Texture2D texture = LoadTexture(filename);
        inserirFim(gif->image, &texture);
    }
    gif->color = WHITE;
    gif->x = gif->y = 0;
    gif->currentFrame = 0;
    gif->frameTime = 0.2f;
    gif->timer = 0;
    gif->rotation = 0;

    if(allGifs != NULL) inserirFim(allGifs, gif);

    return gif;
}

void Gif_Scale(Gif* gif, float scaling){
    Texture2D* firstFrame = (Texture2D*)getItemLista(gif->image, 0);

    if(firstFrame == NULL) return;

    float yscale = (float)(GetScreenHeight() * scaling) / firstFrame->height;
    float xscale = (float)(GetScreenWidth() * scaling) / firstFrame->width;
    gif->scale = fmax(xscale, yscale);
}

void Gif_Update(Gif* gif){
    gif->timer += GetFrameTime();
    if (gif->timer >= gif->frameTime){
        gif->timer = 0;
        gif->currentFrame = (gif->currentFrame + 1) % gif->numFrames;
    }
}

void Gif_Draw(Gif* gif){
    Texture2D* frame = (Texture2D*)getItemLista(gif->image, gif->currentFrame);

    if(frame == NULL) return;

    DrawTextureEx(*frame, (Vector2){gif->x, gif->y}, gif->rotation, gif->scale, gif->color);
}

void Gif_InitList(){
    if(allGifs == NULL) allGifs = criaLista();
}

void FreeTexture_Gif(const void* item){
    UnloadTexture(*(const Texture2D*)item);
}

void TexturesArray_Free(const void* array){
    percorrerLista(((const Gif*)array)->image, FreeTexture_Gif);
    limparLista(((const Gif*)array)->image, true);
}

void Gif_Free(){
    percorrerLista(allGifs, TexturesArray_Free);
    limparLista(allGifs, true);
}