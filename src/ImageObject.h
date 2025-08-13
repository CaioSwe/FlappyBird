#ifndef _ImageObject_h_
#define _ImageObject_h_

#include "Utils.h"
#include "Delimiters.h"
#include "Lista.h"

typedef struct ImageObject {
    int id;
    Texture2D image;
    Color color;
    float x, y;
    float scale, rotation;

    bool flipped;
    Vector2 origin;

    Rectangle source;
    Rectangle destination;

    float save;

    float elapsed;
} ImageObject;

ImageObject* Image_Init(const char* filename);

void Image_Scale(ImageObject* img, float minScaleX, float minScaleY);

void Image_Resize(ImageObject* img, float width, float height);

void Image_Copy(ImageObject* from, ImageObject* to, bool copyImage);

void Image_ChangeImage(ImageObject* img, Texture2D img2);

void Image_Flip(ImageObject* img);

void Image_FlipPro(ImageObject* img);

void Image_FlipHPro(ImageObject* img);

void Image_Fit(ImageObject* img);

void Image_Draw(ImageObject* img);

void Image_DrawPro(ImageObject* img);

void Image_CopyImage(ImageObject* img, ImageObject* from);

void Image_InitList();

void Image_Free();

// void freeTexture_ImageObject(const void* item);

#endif