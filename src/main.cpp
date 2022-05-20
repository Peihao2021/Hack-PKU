#include "raylib.h"

int main(void) {
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "HackPKU");

    Texture2D tiger = LoadTexture("assets/tiger.png");
    Vector2 tiger_pos = { 800, 500 };


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


        DrawTextureEx(tiger, tiger_pos, 0, 5.0, WHITE);

        EndDrawing();
    }

    UnloadTexture(tiger);

    CloseWindow();
    return 0;
}