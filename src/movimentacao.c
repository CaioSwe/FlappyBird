#include "movimentacao.h"

int numPadEquivalent(Vector2 direction){
    int numpad = 0;

    if((int)direction.x == 1 && direction.y == 0) numpad = 6;
    if((int)direction.x == -1 && direction.y == 0) numpad = 4;
    if((int)direction.y == 1 && direction.x == 0) numpad = 2;
    if((int)direction.y == -1 && direction.x == 0) numpad = 8;
    
    return numpad;
}

bool mover(int** mapa, int tam, Player* player, Vector2 direction){
    if(direction.x == 0 && direction.y == 0) return true;
    
    Vector2 pos = Player_GetCoords(player);
    Pilha* s = Player_getPilha(player);

    int numpad = numPadEquivalent(direction);

    if(LOG){
        printf("\nMoving -> ");

        if(direction.x == 1) printf("rightwards");
        if(direction.x == -1) printf("leftwards");
        if(direction.y == -1) printf("upwards");
        if(direction.y == 1) printf("downwards");
    }

    int j = pos.x + direction.x;
    int i = pos.y + direction.y;

    int move = mapa[i][j];
    switch(move){
        case 2: // Caminho bloqueado por parede
            if(LOG){
                printf("\nThe path ");

                if(direction.x == 1) printf("rightwards");
                if(direction.x == -1) printf("leftwards");
                if(direction.y == -1) printf("upwards");
                if(direction.y == 1) printf("downwards");

                printf(" is blocked");
            }
            return false;
        case 0: // Caminho está livre
            mapa[i][j] = 1;
            mapa[i - (int)direction.y][j - (int)direction.x] = 0;
            
            push(s, numpad);

            break;

        case 4: // Saída da dungeon, fim do jogo
            break;

        case 5: // Pisou em uma armadilha

            mapa[ i ][j] = 1;
            mapa[i - (int)direction.y][j - (int)direction.x] = 0;
            push(s, numpad);
           
            break;
        
        case 6: // Passou por cima de um item

            mapa[ i ][j] = 1;
            mapa[i - (int)direction.y][j - (int)direction.x] = 0;
            push(s, numpad);
            
            break;

        case 7: // Encontrou um inimigo
            mapa[ i ][j] = 1;
            mapa[i - (int)direction.y][j - (int)direction.x] = 0;
            push(s, numpad);
           
            break;
    }

    if(LOG) printf("\nMoved");
    
    return true;
}

Vector2 desfazerMovimento(int** mapa, int tam, Player* player){
    system("cls");
    Pilha* s = Player_getPilha(player);

    Vector2 direction = {0, 0};

    int move = 0;
    move = pop(s);

    if(LOG) printf("\nUndoing Movement.");

    switch(move){
        case 8: direction = (Vector2){0, 1}; break;
        case 2: direction = (Vector2){0, -1}; break;
        case 4: direction = (Vector2){1, 0}; break;
        case 6: direction = (Vector2){-1, 0}; break;                
    }

    mover(mapa, tam, player, direction);
    pop(s);

    return direction;
}