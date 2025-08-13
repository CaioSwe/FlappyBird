#include "Arvore.h"

Arvore* criaFolha(bool (*funcao)(const void*), void* target){
    Arvore* arvore = (Arvore*)malloc(sizeof(Arvore));
    arvore->esq = NULL;
    arvore->dir = NULL;
    arvore->funcao = funcao;
    arvore->target = target;

    return arvore;
}

void inserirEsqArvore(Arvore* raiz, bool (*funcao)(const void*), void* target){
    raiz->esq = criaFolha(funcao, target);
}

void inserirDirArvore(Arvore* raiz, bool (*funcao)(const void*), void* target){
    raiz->dir = criaFolha(funcao, target);
}

void percorrerArvore(Arvore* raiz){
    if(raiz == NULL) return;

    if(raiz->esq == NULL && raiz->dir == NULL){
        raiz->funcao(raiz->target);
        return;
    }

    if(raiz->funcao(raiz->target)) percorrerArvore(raiz->esq);
    else  percorrerArvore(raiz->dir);
}