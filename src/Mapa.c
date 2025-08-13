#include "mapa.h"
#include "ImageObject.h"

// Códigos:
// 0 -> Espaço em branco
// 1 -> Jogador
// 2 -> Paredes
// 3 -> Bordas
// 4 -> Saída
// 5 -> Traps
// 6 -> Items
// 7 -> Inimigos

void criarMapa(int*** mapa, int tam){
    srand(time(NULL));

    *mapa = (int**)malloc(tam*sizeof(int*));

    int i_chance = rand() % (tam-2)+1;
    
    //*mapa = (int**)malloc(tam*sizeof(int*));
    if(mapa == NULL){ printf("\nERROR: Insuficient Memory!"); exit(1); }

    for(int i = 0; i < tam; i++){
        (*mapa)[i] = (int*)malloc(tam*sizeof(int));
        if((*mapa) == NULL){ printf("\nERROR: Insuficient Memory!"); exit(1); }

        for(int j = 0; j < tam; j++){
            if     (i == 1 && j == 1){(*mapa)[i][j] = 1; } // Representa o jogador
            else if(i == i_chance && j == tam-1)                   {(*mapa)[i][j] = 4; } // A saída da dungeon
            else if(i == 0 || i == tam-1 || j == 0 || j == tam-1)  {(*mapa)[i][j] = 2; } // As bordas da dungeon 
            else                                                   {(*mapa)[i][j] = 0; } // Espaçoes em branco
        }
    }
    
    // Preenche a dungeon com paredes
    (*mapa)[1][3] = 2;
    (*mapa)[2][3] = 2;
    (*mapa)[1][4] = 2;
    (*mapa)[2][4] = 2;
    (*mapa)[3][4] = 2;
    (*mapa)[4][4] = 2;
    (*mapa)[5][4] = 2;
    (*mapa)[6][4] = 2;
    (*mapa)[7][4] = 2;
    (*mapa)[1][5] = 2;
    (*mapa)[2][5] = 2;

    (*mapa)[10][7] = 2;
    (*mapa)[10][6] = 2;
    (*mapa)[10][5] = 2;
    (*mapa)[10][4] = 2;
    (*mapa)[10][3] = 2;
    (*mapa)[10][2] = 2;
    
    (*mapa)[5][1] = 2;
    (*mapa)[6][1] = 2;
    (*mapa)[7][1] = 2;
    (*mapa)[8][1] = 2;
    
    (*mapa)[3][8] = 2;
    (*mapa)[4][7] = 2;
    (*mapa)[4][8] = 2;
    (*mapa)[2][8] = 2;
    (*mapa)[2][9] = 2;
    (*mapa)[3][9] = 2;

    (*mapa)[9][6]  = 2;
    (*mapa)[10][7] = 2;
    (*mapa)[9] [7] = 2;
    (*mapa)[8] [7] = 2;
    (*mapa)[7] [7] = 2;
    (*mapa)[8] [8] = 2;
    (*mapa)[9] [8] = 2;
    (*mapa)[7] [8] = 2;
    (*mapa)[10][8] = 2;
    (*mapa)[10][8] = 2;
    (*mapa)[10][9] = 2;

    //if(LOG) printf("\nMap created!\n");
}

void populaMapa(int** mapa, int tam){
    srand(time(NULL));
    int chance;

    // Atribui a chance de uma das casas ser o seguinte evento
    int trap    = 8;  // 8% = ~5 casas
    int enemies = 15; // 15% = ~10 casas
    int items   = 12; // 12% = ~7  casas

    for(int i = 0; i < tam; i++){
        for(int j = 0; j < tam; j++){
            if(mapa[i][j] == 0){
                chance = rand() % 100;
                if(chance < trap){
                    mapa[i][j] = 5;
                }
                else if(chance < items){
                    mapa[i][j] = 6;
                }
                else if(chance < enemies){
                    mapa[i][j] = 7;
                }
            }
        }        
    }
}

void printMapa(int** mapa, int tam){
    printf("\n");

    for(int i = 0; i < tam; i++){
        for(int j = 0; j < tam; j++){
            switch (mapa[i][j]){
                case 0: printf("   "); break;
                case 1: printf(" @ "); break;
                case 2: printf(" # "); break;
                case 3: printf(" # "); break;
                case 4: printf(" O "); break;
                case 5: printf(" X "); break;
                case 6: printf(" * "); break;
                case 7: printf(" ! "); break;
                default: printf("   "); break;
            }
        }
        printf("\n");
    }
    printf("\n");
}

void limparMapa(int** mapa, int tam){
    for(int i = 0; i < tam; i++){
        free(mapa[i]);
    }
    free(mapa);
    
    if(LOG) printf("\nMap cleared!\n");
}