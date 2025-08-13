#ifndef _Gif_h_
#define _Gif_h_

#include "Utils.h"
#include "Delimiters.h"
#include "Lista.h"

typedef struct  Gif {
    Lista* image;
    Color color;
    float x, y;
    float scale, rotation;
    int numFrames;
    int currentFrame;
    float frameTime, timer;
} Gif;

Gif* Gif_Init(const char* path, const char* ext, int numFrames);

void Gif_Scale(Gif* gif, float scaling);

void Gif_Update(Gif* gif);

void Gif_Draw(Gif* gif);

void Gif_InitList();

void Gif_Free();

#endif