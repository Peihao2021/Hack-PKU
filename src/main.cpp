#include <cstdio>
#include "character.h"
#include "map.h"
#include "noise.h"
#include "raylib.h"
#include "utils.h"

Vector2 getBirthPos(Map& map) {
    srand(time(0));
    int randx, randy = 0;
    do {
        randx = rand() % HEIGHT;
        randy = rand() % WIDTH;
    } while (map.map[randx][randy] == BlockType::Water);
    return Vector2{float(randx * 31), float(randy * 31)};
}

int main(void) {
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    const int birth_x = 800;
    const int birth_y = 500;

    InitWindow(screenWidth, screenHeight, "HackPKU");
    Texture2D player_text = LoadTexture("assets/player.png");
    Character player_char;

    Map map;
    Perlin noise(20.00, 4, 100);
    map.initialize(noise);
    player_char.pos = getBirthPos(map);
    SetTargetFPS(60);

    Camera2D camera;
    camera.target = {player_char.pos.x, player_char.pos.y};
    camera.offset = {screenWidth / 2.0f, screenHeight / 2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 2.0f;

    // TODO: boundary of southeast
    int speed = 5;
    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_W)) {
            player_char.pos.y -= speed;
        }
        if (IsKeyDown(KEY_S)) {
            player_char.pos.y += speed;
        }
        if (IsKeyDown(KEY_A)) {
            player_char.pos.x -= speed;
        }
        if (IsKeyDown(KEY_D)) {
            player_char.pos.x += speed;
        }

        // printf("TIGER: %f, %f\n", player_char.pos.x, player_char.pos.y);

        if (player_char.pos.x <= birth_x / 2) {
            player_char.pos.x = birth_x / 2;
        }
        if (player_char.pos.y <= birth_y / 2) {
            player_char.pos.y = birth_y / 2;
        }

        BeginDrawing();

        ClearBackground(WHITE);
        camera.target = {player_char.pos.x, player_char.pos.y};
        if (camera.target.x < birth_x) {
            camera.target.x = birth_x;
        }
        if (camera.target.y < birth_y) {
            camera.target.y = birth_y;
        }
        camera.zoom += ((float)GetMouseWheelMove() * 0.05f);
        // if (camera.zoom < 2.) {
        //     camera.zoom = 2.;
        // }

        BeginMode2D(camera);
        drawMap(map);
        DrawTextureEx(player_text, player_char.pos, 0.f, 2.f, WHITE);
        EndMode2D();

        EndDrawing();
    }

    UnloadTexture(player_text);

    CloseWindow();
    return 0;
}