#ifndef _Inventario_h_
#define _Inventario_h_

#include "utils.h"
#include "Lista.h"
#include "Pilha.h"
#include "Player.h"
#include "Items.h"

int sortearItem(bool printInfo);

int menuInventario();

bool coletarItem(Item* item, Player* player);

void abrirInventario(Player* player);

void usarItem(Player* player);

void descartarItem(Lista* lista);

void inspecionarItem(Lista* lista);

#endif