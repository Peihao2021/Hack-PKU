#include <cstdio>
#include "map.h"
#include "noise.h"
#include "raylib.h"
#include "utils.h"

int main(void) {
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "HackPKU");
    Texture2D tiger = LoadTexture("assets/tiger.png");
    Vector2 tiger_pos = {800, 500};
    Map map;
    Perlin noise(10.00, 4, 60);
    map.initialize(noise, 0.1);
    // for (int i = 0; i < WIDTH; i++) {
    //     for (int j = 0; j < HEIGHT; j++) {
    //         printf("%d ", map.map[i][j]);
    //     }
    //     putchar('\n');
    // }
    // Image noise = Perlin::generateImage(1000, 1000);
    // Texture2D noise_tex = LoadTextureFromImage(noise);
    SetTargetFPS(60);

    Camera2D camera;
    camera.target = {tiger_pos.x, tiger_pos.y};
    camera.offset = {screenWidth / 2.0f, screenHeight / 2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

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
        camera.target = {tiger_pos.x, tiger_pos.y};

        BeginMode2D(camera);
        DrawTextureEx(tiger, tiger_pos, 0.f, 1.f, WHITE);
        drawMap(map);
        EndMode2D();

        EndDrawing();
    }

    UnloadTexture(tiger);

    CloseWindow();
    return 0;
}