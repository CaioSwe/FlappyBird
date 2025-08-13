#ifndef _Arvore_h_
#define _Arvore_h_

#include "utils.h"

typedef struct Arvore{
    struct Arvore* esq;
    struct Arvore* dir;
    bool (*funcao)(const void*);
    void* target;
} Arvore;

Arvore* criaFolha(bool (*funcao)(const void*), void* target);

void inserirEsqArvore(Arvore* raiz, bool (*funcao)(const void*), void* target);

void inserirDirArvore(Arvore* raiz, bool (*funcao)(const void*), void* target);

void percorrerArvore(Arvore* raiz);

#endif