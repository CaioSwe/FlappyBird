#include "ItensColeta.h"

int itemChoice(){
    int input;
    printf("\n\nWould you like to collect it?");
    printf("\n1 - Yes");
    printf("\n2 - No\n");
    scanf("%d", &input);

    return input;
}

bool coletarItem(Item* item, Player* player){
    int input = 0;
    Lista* lista = Player_getInventarioUtils(player);

    input = itemChoice();

    if(input != 1) return false;

    if(!item->isMimic){
        inserirFim(lista, item);
        return false;
    }

    system("cls");
    printf("\nBut the chest was actually a mimic!");
    
    return true;
} // return true se for um mimico

int sortearItem(bool printInfo){
    srand(time(NULL));
    int item = rand() % 3 + 1;
        
    if(!printInfo) return item;

    system("cls");
    printf("You found an item!");

    // Escolhe qual item o usuário encontrou
    switch(item){
        case 1: printf("\nIt is a Health Potion!"); break;
        case 2: printf("\nIt is a Monster's Repelent!"); break;
        case 3: printf("\nIt is a Treasure chest"); break;
        default: printf("\nInvalid value ERROR"); break;
    }

    return item;
}

void inventoryPrintStd(const void* item, const void* target){
    const Item* objeto = (const Item*)item;
    int* count = (int*)target;

    (*count) += 1;

    printf("\n%d - %s", *count, getItemName((Item*)objeto));
}

int menuInventario(){
    int opc = 0;
    printf("\nWould you like to:");
    printf("\n1 - Use an item");
    printf("\n2 - Drop an item");
    printf("\n3 - Inspect an item"); 
    printf("\n4 - Exit the inventory\n"); 
    //scanf("%d", &opc);

    return opc;
}

void abrirInventario(Player* player){
    Lista* lista = Player_getInventarioUtils(player);
    
    system("cls");
    printf("You opened your inventory!");
    
    int opc = 0;

    do{
        printf("\nYou have the following items:\n\n");
        printf("GOLD: %d", Player_getStats(player).gold);
        
        int count = 0;

        if(isListaVazia(lista)) printf("\n - Your inventory is empty... - \n");

        imprimirListaRel(lista, &count, inventoryPrintStd);

        opc = menuInventario();

        opc = 4;

        switch(opc){
            case 1: 
                //usarItem(lista);
                break;
            case 2: 
                //descartarItem(lista);
                break;
            case 3:
                //inspecionarItem(lista);
                break;
            case 4: // Fecha o inventário
                opc = 4;
                break;
            default: 
                printf("\nSelected option unavailable >:(");
                break;
        }

        //system("cls");
    }while(opc != 4);
}

// void usarItem(Lista* lista){
//     int opc;
//     system("cls");
//     printf("\nWhich item would you like to use?");
//     imprimirLista(lista, inventoryPrintStd);
//     scanf("%d", &opc);

//     Celula* item = buscarElemento(lista, opc);
//     if(item != NULL){
//         switch (getValor(item)){

//             // Health Potion
//             case 1:
//                 printf("\nHP: %.2f", getPlayerHP(p));

//                 int hp = getPlayerHP(p) + 40;
//                 if(hp <= 100) setPlayerHP(p, hp);
//                 else          setPlayerHP(p, 100);
//                 printf("\nHealth Potion used!");

//                 printf("\nHP: %.2f", getPlayerHP(p));

//                 Sleep(1500);
//                 break;

//             // Monster's Repelent
//             case 2:
//                 setPlayerRepelent(p, 10);
//                 printf("\nMonster's Repelent used!");
//                 Sleep(1500);
//                 break;
        
//             default:
//                 printf("\nInvalid choice");
//                 Sleep(1500);
//                 break;
//         }removerMeio(lista, opc);
//     }else{
//         printf("\nItem not found in inventory.");
//     }
// }

// void descartarItem(Lista* lista){
//     int opc;
//     system("cls");
//     printf("\nWhich item would you like to drop?");
//     imprimirLista(lista);
//     scanf("%d", &opc);
//     removerMeio(lista, opc);
// }

// void inspecionarItem(Lista* lista){
//     int opc;
//     system("cls");
//     printf("\nWhich item would you like to inspect?");
//     imprimirLista(lista);
//     scanf("%d", &opc);

//     Celula* item = buscarElemento(lista, opc);

//     if(item != NULL){
//         switch (getValor(item)){

//             // Health Potion
//             case 1:
//                 printf("\nThis is a Health Potion");
//                 printf("\nIt considerably heals you life energy!");
//                 Sleep(3000);
//                 break;

//             // Monster's Repelent
//             case 2:
//                 printf("\nThis is a Monster's Repelent");
//                 printf("\nIt makes it so your scent is undetectable to monsters");
//                 printf(" for a short amount of time!");
//                 Sleep(3000);
//                 break;
            
//             default:
//                 printf("\nInvalid choice");
//                 Sleep(1500);
//                 break;
//         }
//     }else printf("\nItem not found in inventory.");
// }