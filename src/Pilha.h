#ifndef _Pilha_h_
#define _Pilha_h_

#include <stdio.h>
#include <stdlib.h>

typedef struct Pilha Pilha;

Pilha* criarPilha          (           );
void   verificarPilhaVazia (Pilha*     );
int    push                (Pilha*, int);
int    pop                 (Pilha*     );
int    tamanhoPilha        (Pilha*     );
void   imprimirPilha       (Pilha*     );
void   limparPilha         (Pilha*     );

#endif