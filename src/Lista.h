#ifndef _Lista_
#define _Lista_

#include "Button.h"
#include "Delimiters.h"

typedef struct Lista Lista;
typedef struct cel cel;

Lista* criaLista();

void inserirInicio(Lista*, void*);

void inserirMeio(Lista*, void*, void*);

void inserirFim(Lista*, void*);

void* removerInicio(Lista*);

void* removerMeio(Lista*, void*);

void* removerFim(Lista*);

void* remover(Lista*, bool(*f)(const void*, const void*), const void*, bool);

bool isListaVazia(Lista*);

int listaTamanho(Lista*);

void imprimirLista(Lista*, void(*imprimir)(const void*));

void imprimirListaRel(Lista*, void*, void(*imprimir)(const void*, const void*));

void imprimirListaRelRel(Lista*, void*, void*, void(*imprimir)(const void*, const void*, const void*));

void percorrerLista(Lista*, void(*f)(const void*));

void percorrerListaRel(Lista*, void(*f)(const void*, const void*), void*);

bool isInLista(Lista*, bool(*f)(const void*, const void*), const void*);

void* getItemLista(Lista*, int);

void limparLista(Lista*, bool);

#endif