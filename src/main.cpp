#include "noise.h"
#include "raylib.h"
#include "map.h"
#include <cstdio>

int main(void)
{
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "HackPKU");
    Texture2D tiger = LoadTexture("assets/tiger.png");
    Vector2 tiger_pos = { 800, 500 };
    Map map;
    Perlin noise(10.00, 4, 60);
    map.initialize(noise, 0.1);
    for(int i = 0; i < WIDTH; i++){
        for(int j = 0; j < HEIGHT; j++){
            printf("%d ", map.map()[i][j]);
        }
        putchar('\n');
    }
    // Image noise = Perlin::generateImage(1000, 1000);
    // Texture2D noise_tex = LoadTextureFromImage(noise);
    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        if (IsKeyDown(KEY_W)) {
            tiger_pos.y -= 5;
        }
        if (IsKeyDown(KEY_S)) {
            tiger_pos.y += 5;
        }
        if (IsKeyDown(KEY_A)) {
            tiger_pos.x -= 5;
        }
        if (IsKeyDown(KEY_D)) {
            tiger_pos.x += 5;
        }

        BeginDrawing();

        ClearBackground(WHITE);
        // DrawTexture(noise_tex, 0, 0, WHITE);
        // DrawTextureEx(tiger, tiger_pos, 0, 5.0, WHITE);
        EndDrawing();
    }

    UnloadTexture(tiger);

    CloseWindow();
    return 0;
}