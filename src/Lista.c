#include "Lista.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct cel{
    void* item;
    struct cel* prox;
    struct cel* ant;
} Celula;

struct Lista{
    Celula* inicio;
    Celula* fim;
    int tamanho;
};

Lista* criaLista(){
    Lista* l = (Lista*)malloc(sizeof(Lista));
    l->inicio = NULL;
    l->fim = NULL;
    l->tamanho = 0;
    return l;
}

void inserirInicio(Lista* Lista, void* v){
    Celula *nova = malloc(sizeof(Celula));
    nova->item = v;

    if (Lista->inicio == NULL){ // Lista vazia
        Lista->inicio = nova;
        Lista->fim = nova;
        nova->prox = NULL;
        nova->ant = NULL;
    }
    else{
        nova->prox = Lista->inicio;
        nova->ant = NULL;
        Lista->inicio->ant = nova;
        Lista->inicio = nova;
    }

    Lista->tamanho += 1;
}

void inserirFim(Lista* Lista, void* v){
    Celula* nova = malloc(sizeof(Celula));
    nova->item = v;

    if (Lista->inicio == NULL){
        Lista->inicio = nova;
        Lista->fim = nova;
        nova->prox = NULL;
        nova->ant = NULL;
    }
    else{
        nova->prox = NULL;
        Lista->fim->prox = nova;
        nova->ant = Lista->fim;
        Lista->fim = nova;
    }

    Lista->tamanho += 1;
}

void* removerInicio(Lista* Lista){
    Celula* cel = Lista->inicio;
    void* v = cel->item;

    Lista->inicio = Lista->inicio->prox;

    if(Lista->inicio == NULL) // Lista ficará vazia
        Lista->fim = NULL;
    else
        Lista->inicio->ant = NULL;
    
    free(cel);

    Lista->tamanho -= 1;

    return v;
}

void* removerFim(Lista* Lista){
    Celula* cel = Lista->fim;
    void* v = cel->item;

    Lista->fim = Lista->fim->ant;

    free(cel);

    Lista->tamanho -= 1;

    return v;
}

void* remover(Lista* lista, bool(*f)(const void*, const void*), const void* item, bool freeIt){
    if (!lista) return NULL;

    Celula* cel = lista->inicio;
    Celula* aux = NULL;

    if(f(cel->item, item)){
        lista->tamanho -= 1;
        lista->inicio = cel->prox;
        return cel->item;
    }

    while(cel->prox != NULL){
        if(f(cel->prox->item, item)){
            lista->tamanho -= 1;
            aux = cel->prox;
            cel->prox = cel->prox->prox;
            return aux->item;
        }
        cel = cel->prox;
    }

    return NULL;
}

bool isListaVazia(Lista* lista){
    if(lista->inicio == NULL){
        return true;
    }
    return false;
}

int listaTamanho(Lista* lista){
    return lista->tamanho;
}

void imprimirLista(Lista* lista, void(*imprimir)(const void*)){
    Celula* atual = lista->inicio;

    while(atual != NULL){
        void* c = (void*)atual->item;
        imprimir(c);
        atual = atual->prox;
    }
}

void imprimirListaRel(Lista* lista, void* target, void(*imprimir)(const void*, const void*)){
    Celula* atual = lista->inicio;

    while(atual != NULL){
        void* c = (void*)atual->item;
        imprimir(c, target);
        atual = atual->prox;
    }
}

void imprimirListaRelRel(Lista* lista, void* target, void* p, void(*imprimir)(const void*, const void*, const void*)){
    Celula* atual = lista->inicio;

    while(atual != NULL){
        void* c = (void*)atual->item;
        imprimir(c, target, p);
        atual = atual->prox;
    }
}

void percorrerLista(Lista* lista, void (*f)(const void*)) {
    Celula* cel = lista->inicio;
    
    while(cel != NULL){
        f(cel->item);
        cel = cel->prox;
    }
}

void percorrerListaRel(Lista* lista, void(*f)(const void*, const void*), void* target){
    Celula* cel = lista->inicio;
    
    while(cel != NULL){
        f(cel->item, target);
        cel = cel->prox;
    }
}

bool isInLista(Lista* lista, bool(*f)(const void*, const void*), const void* valor) {
    if (!lista) return false;

    Celula* cel = lista->inicio;
    
    while(cel != NULL){
        if(f(cel->item, valor)){
            return true;
        }
        cel = cel->prox;
    }
    return false;
}

void* getItemLista(Lista* lista, int pos){
    if (!lista) return NULL;

    Celula* cel = lista->inicio;

    for(int i = 0; (i < pos) && (cel != NULL); i++){
        cel = cel->prox;
    }

    return cel->item;
}

void limparLista(Lista* lista, bool freeItems) {
    if (!lista) return;

    Celula* atual = lista->inicio;
    while (atual != NULL) {
        Celula* temp = atual;
        atual = atual->prox;
        if(freeItems) free(temp->item);
        free(temp);
    }

    lista->inicio = NULL;
    lista->fim = NULL;
    lista->tamanho = 0;
}