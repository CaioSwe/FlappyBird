#include "pilha.h"

typedef struct cel{
    int         val;
    struct cel* prox;
}Celula;

typedef struct Pilha{
    Celula* topo;
    int     tamanho;
}Pilha;

//Implementação das funções da Pilha
Pilha* criarPilha(){
    Pilha* p = (Pilha*)malloc(sizeof(Pilha));
    p->topo    = NULL;
    p->tamanho = 0;

    return p;
}

void verificarPilhaVazia(Pilha* p){
    if(p->tamanho < 1){ printf("\nA Pilha ESTA vazia");     }
    else              { printf("\nA Pilha NAO esta vazia"); }
}

int push(Pilha* p, int v){
    Celula* nova = (Celula*)malloc(sizeof(Celula));

    nova->prox  = p->topo;
    p->topo     = nova;
    nova->val   = v;
    p->tamanho += 1;

    return 0;
}

int pop(Pilha* p){
    if(p->tamanho < 1) return 0;

    int v = p->topo->val;
    
    Celula* cel_topo = p->topo;
    p->topo          = cel_topo->prox;
    p->tamanho      -= 1;
    free(cel_topo);

    return v;
}

int tamanhoPilha(Pilha* p){
    return p->tamanho;
}

void imprimirPilha(Pilha* p){
    if(p->tamanho < 1) { printf("\nPILHA VAZIA.\n"); }
    else{
        Celula* temp = p->topo;

        printf("\n\nPILHA:\n");
        while(temp != NULL){
            printf("[%d]\n", temp->val);
            temp = temp->prox;
        }
    }    
}

void limparPilha(Pilha* s){
    Celula*   del = s->topo;
    Celula* atual = NULL;
    
    while(del != NULL){
        atual = del;
        del   = del->prox;
        free(atual);
    }free(del);
}