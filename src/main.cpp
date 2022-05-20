#include <cmath>
#include <cstdio>
#include <list>
#include "character.h"
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
    Texture2D player_text = LoadTexture("assets/player.png");
    Character player_char;            // main character
    std::list<Character> characters;  // mobs
    Map map;                          // world map
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
    int difficulty = 0;
    int diffIncreaseInterval = 600;
    int mobSpwanInterval = 240;
    size_t maxMobAcount = 200;
    long long frameCounter = 0;
    while (!WindowShouldClose()) {
        frameCounter++;
        if (frameCounter % diffIncreaseInterval == 0) {  // increase difficulty
            if (difficulty < 5) {
                difficulty++;
                printf("current difficulty: %d\n", difficulty);
                mobSpwanInterval = mobSpwanInterval >> 1;
            }
        }

        if (characters.size() < maxMobAcount &&
            frameCounter % mobSpwanInterval == 0) {  // spwan mob
            int randx = rand() % WIDTH;
            int randy = rand() % HEIGHT;
            Character tmp;
            tmp.pos = {(float)randx * 31, (float)randy * 31};
            tmp.speed = 3;
            tmp.attackInterval = 60;
            characters.push_back(tmp);
            printf("current mob number: %lld\n", characters.size());
        }

        for (auto& c : characters) { // set mob speed 
            int axis_x = c.pos.x / 31;
            int axis_y = c.pos.y / 31;
            if (axis_x >= WIDTH || axis_y >= HEIGHT || axis_x <= 0 ||
                axis_y <= 0) {
                c.speed = -c.speed;
            } else if (map.map[axis_x][axis_y] == BlockType::Water) {
                c.speed = 2;
            } else {
                c.speed = 3;
            }
        }

        updateCharacterPos(characters, player_char);  // mob move

        for (auto& cara : characters) {  // mob attack
            if (getDistance(cara.pos, player_char.pos) < 5) {
                if (cara.attackCounter == 0) {
                    cara.attackCounter = cara.attackInterval;
                    printf("hp decreased!\n");
                } else {
                    cara.attackCounter--;
                }
            }
        }

        int axis_x = player_char.pos.x / 31;
        int axis_y = player_char.pos.y / 31;
        if (axis_x >= WIDTH || axis_y >= HEIGHT || axis_x <= 0 || axis_y <= 0) {
            speed = -speed;
        } else if (map.map[axis_x][axis_y] == BlockType::Water) {
            speed = 1;
        } else {
            speed = 5;
        }
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
        player_char.skill = Skill::Null;
        if (IsKeyDown(KEY_KP_1)) {
            player_char.skill = Skill::FootBall;
        }
        if (IsKeyDown(KEY_KP_2)) {
            player_char.skill = Skill::Sonic;
        }
        if (IsKeyDown(KEY_KP_3)) {
            player_char.skill = Skill::Umbrella;
        }
        if (IsKeyDown(KEY_KP_4)) {
            player_char.skill = Skill::Fishing;
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
        drawCharacters(characters);
        DrawTextureEx(player_text, player_char.pos, 0.f, 1.f, WHITE);
        EndMode2D();

        EndDrawing();
    }

    UnloadTexture(player_text);

    CloseWindow();
    return 0;
}