#pragma region "Structs"

#include "ImageObject.h"
#include "Button.h"
#include "Gif.h"
#include "TextObject.h"
#include "Input.h"
#include "Player.h"
#include "TileSet.h"
#include "Game.h"
#include "SpriteSheet.h"

#include "movimentacao.h"
#include "ItensColeta.h"

#include "Pilha.h"
#include "Lista.h"
#include "Arvore.h"

#include "Mapa.h"

#pragma endregion "Structs"

bool collided = false;

typedef struct Bird{
    Rectangle body;
    Vector2 speed;
    float fallRate;
    float rotation;

    float jumpForce;
}Bird;

Bird* birdInit(Rectangle body, Vector2 speed, float fallRate, float jumpForce){
    Bird* bird = (Bird*)malloc(sizeof(Bird));

    bird->body = body;
    bird->speed = speed;
    bird->fallRate = fallRate;
    bird->rotation = 0;

    bird->jumpForce = jumpForce;
    
    return bird;
}

void birdUpdate(Bird* bird, float deltaTime){
    bird->speed.y += bird->fallRate;
    
    bird->body.x += bird->speed.x * deltaTime;
    bird->body.y += bird->speed.y * deltaTime;

    //bird->rotation = bird->speed.y;
}

void birdJump(Bird* bird){
    bird->speed.y = -bird->jumpForce;
}

void birdDraw(Bird* bird){
    DrawRectanglePro(bird->body, (Vector2){0, 0}, bird->rotation, WHITE);
}

typedef struct Obstacle{
    Rectangle upperWall;
    Rectangle bottomWall;

    float horizontalSpeed;
} Obstacle;

Obstacle* obstacleInit(Vector2 wallPlacement, Vector2 gap, float speed){
    Obstacle* obstacle = (Obstacle*)malloc(sizeof(Obstacle));

    obstacle->upperWall.x = wallPlacement.x;
    obstacle->bottomWall.x = wallPlacement.x;

    obstacle->upperWall.y = 0;
    obstacle->bottomWall.y = gap.y + gap.x;

    obstacle->upperWall.height = gap.y;
    obstacle->bottomWall.height = GetScreenHeight();

    obstacle->upperWall.width = wallPlacement.y;
    obstacle->bottomWall.width = wallPlacement.y;

    obstacle->horizontalSpeed = speed;

    return obstacle;
}

void obstacleUpdate(Obstacle* obstacle){
    obstacle->upperWall.x -= obstacle->horizontalSpeed;
    obstacle->bottomWall.x -= obstacle->horizontalSpeed;
}

void updateObstaclesVoid(const void* item, const void* additional){
    obstacleUpdate((Obstacle*)item);

    bool upperCollision = CheckCollisionRecs(*(Rectangle*)additional, ((Obstacle*)item)->upperWall);
    bool bottomCollision = CheckCollisionRecs(*(Rectangle*)additional, ((Obstacle*)item)->bottomWall);

    if(upperCollision || bottomCollision){
        collided = true;
    }
}

float getGapSize(Obstacle* obstacle){
    return obstacle->bottomWall.y - obstacle->upperWall.height;
}

void obstacleChangeGapPlacement(Obstacle* obstacle, float newPlacement){
    obstacle->bottomWall.y = newPlacement + getGapSize(obstacle);
    obstacle->upperWall.height = newPlacement;
}

void obstacleDraw(Obstacle* obstacle){
    DrawRectangleRec(obstacle->bottomWall, RED);
    DrawRectangleRec(obstacle->upperWall, RED);
}

void obstacleDrawVoid(const void* item){
    obstacleDraw((Obstacle*)item);
}

Obstacle* copyObstacle(Obstacle* obstacle){
    Obstacle* newObstacle = (Obstacle*)malloc(sizeof(Obstacle));

    newObstacle->upperWall = obstacle->upperWall;
    newObstacle->bottomWall = obstacle->bottomWall;
    newObstacle->horizontalSpeed = obstacle->horizontalSpeed;

    return newObstacle;
}

int main(){
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Teste");
    SetTargetFPS(60);

    _chdir(GetApplicationDirectory());

    srand(time(NULL));

    int score = 0;

    Rectangle birdBody = {GetScreenWidth()/2 - 100, GetScreenHeight()/2 - 50, 20, 8};

    Bird* bird = birdInit(birdBody, (Vector2){0, 0}, 9.0f, 300.0f);

    Obstacle* obstacleBase = obstacleInit((Vector2){GetScreenWidth(), bird->body.width * 1.8f}, (Vector2){bird->body.height * 12, 0}, 2.0f);

    Lista* allObstacles = criaLista();

    while(!WindowShouldClose()){
        float deltaTime = GetFrameTime();

        birdUpdate(bird, deltaTime);

        if(IsKeyPressed(KEY_SPACE)) birdJump(bird);

        if(Wait(4.0f)){
            Obstacle* newObstacle = copyObstacle(obstacleBase);

            obstacleChangeGapPlacement(newObstacle, (float)((rand() % 100) / 100.0f) * ((GetScreenHeight() - getGapSize(newObstacle))));
            inserirFim(allObstacles, newObstacle);
        }

        percorrerListaRel(allObstacles, updateObstaclesVoid, &bird->body);

        if(collided){
            printf("\nDied :(\n");
            collided = false;
        }

        BeginDrawing();
            ClearBackground(BLACK);
            birdDraw(bird);
            imprimirLista(allObstacles, obstacleDrawVoid);
        EndDrawing();
    }

    return 0;
}