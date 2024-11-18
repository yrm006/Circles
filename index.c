#include<raylib.h>

typedef struct circle
{
    int x;
    int y;
    int xv;
    int yv;

    int radius;
    Color color;
} circle;

void circle_init(circle* c, int x, int y, int xv, int yv, int radius, Color color){
    c->x = x;
    c->y = y;
    c->xv = xv;
    c->yv = yv;
    c->radius = radius;
    c->color = color;
}
void circle_draw(circle* c){
    DrawCircle(c->x, c->y, c->radius, c->color);
}
void circle_move(circle* c){
    c->x += c->xv;
    c->y += c->yv;
}

circle player;

int main(){
    const int screenWidth = 800;
    const int screenHeight = 450;

    circle_init(&player, 400, 225, 0, 0, 10, RED);

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    
    SetTargetFPS(60);

    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        circle_draw(&player);

        EndDrawing();
    }
    return 0;
}