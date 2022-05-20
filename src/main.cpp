#include <cstdio>
#include "map.h"
#include "noise.h"
#include "raylib.h"
#include "utils.h"

int main(void) {
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    const int birth_x = 800;
    const int birth_y = 500;

    InitWindow(screenWidth, screenHeight, "HackPKU");
    Texture2D tiger = LoadTexture("assets/tiger.png");
    Vector2 tiger_pos = {birth_x, birth_y};
    Map map;
    Perlin noise(20.00, 4, 100);
    map.initialize(noise);
    SetTargetFPS(60);

    Camera2D camera;
    camera.target = {tiger_pos.x, tiger_pos.y};
    camera.offset = {screenWidth / 2.0f, screenHeight / 2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 2.0f;

    // TODO: boundary of southeast

    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_W)) {
            tiger_pos.y -= 3;
        }
        if (IsKeyDown(KEY_S)) {
            tiger_pos.y += 3;
        }
        if (IsKeyDown(KEY_A)) {
            tiger_pos.x -= 3;
        }
        if (IsKeyDown(KEY_D)) {
            tiger_pos.x += 3;
        }

        // printf("TIGER: %f, %f\n", tiger_pos.x, tiger_pos.y);

        if (tiger_pos.x <= birth_x / 2) {
            tiger_pos.x = birth_x / 2;
        }
        if (tiger_pos.y <= birth_y / 2) {
            tiger_pos.y = birth_y / 2;
        }

        BeginDrawing();

        ClearBackground(WHITE);
        camera.target = {tiger_pos.x, tiger_pos.y};
        if (camera.target.x < birth_x) {
            camera.target.x = birth_x;
        }
        if (camera.target.y < birth_y) {
            camera.target.y = birth_y;
        }
        camera.zoom += ((float)GetMouseWheelMove() * 0.05f);
        if (camera.zoom < 2.) {
            camera.zoom = 2.;
        }

        BeginMode2D(camera);
        drawMap(map);
        DrawTextureEx(tiger, tiger_pos, 0.f, 2.f, WHITE);
        EndMode2D();

        EndDrawing();
    }

    UnloadTexture(tiger);

    CloseWindow();
    return 0;
}