#include "ImageObject.h"

static Lista* allImageObjects = NULL;

ImageObject* Image_Init(const char* filename){
    ImageObject* img = (ImageObject*)malloc(sizeof(ImageObject));

    if(filename != NULL){
        img->image = LoadTexture(filename);
    }
    
    img->color = WHITE;
    img->x = 0;
    img->y = 0;
    img->rotation = 0;
    img->scale = 1.0f;
    img->flipped = false;
    img->origin = (Vector2){0,0};

    img->source = (Rectangle){0, 0, img->image.width, img->image.height};
    img->save = 0;

    img->elapsed = 0.0f;

    if(allImageObjects != NULL) inserirFim(allImageObjects, img);

    return img;
}

void Image_Scale(ImageObject* img, float minScaleX, float minScaleY){
    float xscale = (float)(GetScreenWidth() * minScaleX) / img->image.width;
    float yscale = (float)(GetScreenHeight() * minScaleY) / (img->image.height / 2);
    img->scale = fmin(yscale, xscale);
}

void Image_Resize(ImageObject* img, float width, float height){
    img->image.width = width;
    img->image.height = height;
}

void Image_Copy(ImageObject* from, ImageObject* to, bool copyImage){
    if(copyImage) to->image = from->image;
    to->color = from->color;
    to->rotation = from->rotation;
    to->scale = from->scale;
    to->x = from->x;
    to->y = from->y;

    to->source = from->source;
    to->destination = from->destination;
}

void Image_ChangeImage(ImageObject* img, Texture2D img2){
    float width = img->image.width;
    float height = img->image.height;
    img->image = img2;
    img->image.width = width;
    img->image.height = height;
}

void Image_CopyImage(ImageObject* img, ImageObject* from){
    img->image = from->image;
}

void Image_Flip(ImageObject* img){
    img->flipped = !img->flipped;
}

void Image_FlipPro(ImageObject* img){
    img->source.width *= -1;
}

void Image_FlipHPro(ImageObject* img){
    img->source.height *= -1;
}

void Image_Fit(ImageObject* img){
    float xscale = (float)(GetScreenWidth()) / img->image.width;
    float yscale = (float)(GetScreenHeight()) / (img->image.height);
    img->scale = fmax(yscale, xscale);
}

void Image_Draw(ImageObject* img){
    if(img == NULL) return;

    Rectangle originRec = (Rectangle){0,0, (float)img->image.width,(float)img->image.height};
    Rectangle destRec = (Rectangle){img->x, img->y, (float)img->image.width, (float)img->image.height};
    Vector2 origin = img->origin;
    
    if(img->flipped){
        originRec.width *= -1;
    }
    if(!(origin.x == 0 && origin.y == 0)){
        origin = (Vector2){0, img->image.height};
    }

    DrawTexturePro(img->image, originRec, destRec, origin, img->rotation, img->color);
}

void Image_DrawPro(ImageObject* img){
    if(img == NULL) return;

    DrawTexturePro(img->image, img->source, img->destination, (Vector2){0,0}, 0.0f, img->color);
}

void Image_InitList(){
    if(allImageObjects == NULL) allImageObjects = criaLista();
}

void freeTexture_ImageObject(const void* item){
    UnloadTexture(((const ImageObject*)item)->image);
} 

void Image_Free(){
    percorrerLista(allImageObjects, freeTexture_ImageObject);
    limparLista(allImageObjects, true);
}