#include<raylib.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

typedef struct circle
{
    int x;
    int y;
    int xv;
    int yv;

    int speed;

    int radius;
    Color color;
} circle;

void circle_init(circle* c, int x, int y, int xv, int yv,int speed,int radius, Color color){
    c->x = x;
    c->y = y;
    c->xv = xv;
    c->yv = yv;
    c->speed = speed;
    c->radius = radius;
    c->color = color;

    printf("circle x: %d y: %d xv: %d yv: %d speed: %d radius: %d\n", c->x, c->y, c->xv, c->yv, c->speed, c->radius);
}
void circle_draw(circle* c){
    DrawCircle(c->x, c->y, c->radius, c->color);
}
void circle_move(circle* c){
    c->x += c->xv;
    c->y += c->yv;

    if (c->x < 0 || c->x > 800){
        c->xv *= -1;
    }
    if (c->y < 0 || c->y > 450){
        c->yv *= -1;
    }

}
void circle_mouse(circle* c){
    int mouseX = GetMouseX();
    int mouseY = GetMouseY();

    c->x += (mouseX - c->x) * 0.1;
    c->y += (mouseY - c->y) * 0.1;
}

bool circle_col(circle* c1, circle* c2){
    int dx = c1->x - c2->x;
    int dy = c1->y - c2->y;
    int distance = sqrt(dx * dx + dy * dy);

    if (distance < c1->radius + c2->radius){
        return true;
    }
}

circle player;

const int MAX_ENEMIES = 14;
circle enemies[MAX_ENEMIES];
void init_enemies() {
    int i = -1;
    while(++i < MAX_ENEMIES){
        int p = GetRandomValue(0, 3);
        int x,y;
        
        if(p == 0){
            x = GetRandomValue(0, 800);
            y = GetRandomValue(0, 1) * 450;
        }else
        if (p == 1){
            x = GetRandomValue(0, 1) * 800;
            y = GetRandomValue(0, 450);
        }else
        if (p == 2){
            x = GetRandomValue(0, 800);
            y = 0;
        }else
        if (p == 3){
            x = 800;
            y = GetRandomValue(0, 450);
        }

        int s = GetRandomValue(1, 3);
        int r = GetRandomValue(3, 30);

        circle_init(&enemies[i], x, y, GetRandomValue(-5, 5), GetRandomValue(-5, 5), s, r, BLUE);
    }
}

void circle_powerup(circle* c, circle* p){
    c->radius += p->radius / 5;
}

void circle_disappear(circle* c){
    c->x = -100;
    c->y = -100;
    c->xv = 0;
    c->yv = 0;
}

int main(){
    const int screenWidth = 800;
    const int screenHeight = 450;

    bool start = false;
    bool gameclear = false;

    int heratime = 0;
    int cleartime = 0;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    srand(time(NULL));

    circle_init(&player, 400, 225, 0, 0,3, 15, RED);
    init_enemies();
    
    SetTargetFPS(60);

    while (!WindowShouldClose()){
        if (start){
            circle_mouse(&player);
        }
        if (!start && IsKeyPressed(KEY_SPACE)){
            init_enemies();
            start = true;
            heratime = GetTime();
        }
        BeginDrawing();
            ClearBackground(RAYWHITE);

            circle_draw(&player);
            if (gameclear){
                DrawText("Game Clear", 300, 200, 20, BLACK);
                DrawText("Congratulations!", 300, 180, 20, BLACK);
                DrawText(TextFormat("Clear Time: %d seconds", cleartime), 300, 220, 20, BLACK);
            }else
            if (start){
                int i = -1;
                int count = 0;
                while(++i < MAX_ENEMIES){
                    circle_draw(&enemies[i]);
                    circle_move(&enemies[i]);

                    if (circle_col(&player, &enemies[i])){
                        if (player.radius < enemies[i].radius){
                            start = false;
                        }else{
                            circle_disappear(&enemies[i]);
                            circle_powerup(&player, &enemies[i]);
                        }
                    }

                    if (enemies[i].x == -100 && enemies[i].y == -100){
                        count++;
                    }
                }
                if (count == MAX_ENEMIES){
                    start = false;
                    gameclear = true;
                    cleartime = GetTime() - heratime;
                }
            }else{
                DrawText("Press SPACE to start", 300, 200, 20, BLACK);
            }
        EndDrawing();
    }
    return 0;
}