#ifndef _Movimentacao_h_
#define _Movimentacao_h_

#include "utils.h"
#include "Player.h"
#include "Pilha.h"
#include "Lista.h"

bool mover         (int** mapa, int tam, Player* player, Vector2 direction);
Vector2 desfazerMovimento (int** mapa, int tam, Player* player);

#endif