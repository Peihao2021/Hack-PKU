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
    // const int birth_x = 800;
    // const int birth_y = 500;
    int marginx = screenWidth / 4;
    int marginy = screenHeight / 4;
    InitWindow(screenWidth, screenHeight, "HackPKU");
    Texture2D player_text = LoadTexture("assets/player.png");
    Texture2D soccer_text = LoadTexture("assets/soccer.png");
    Character player_char;  // main character

    int soccer_cd = 0;
    std::list<Character> mobs;     // mobs
    std::list<Character> soccers;  // soccers
    Map map;                       // world map
    Perlin noise(20.00, 4, 100);
    map.initialize(noise);
    do {
        player_char.pos = getBirthPos(map);
    } while (player_char.pos.x > marginx && player_char.pos.y > marginy &&
             player_char.pos.x < WIDTH * 31 - marginx &&
             player_char.pos.y < HEIGHT * 31 - marginy);
    SetTargetFPS(60);

    Camera2D camera;
    camera.target = {player_char.pos.x, player_char.pos.y};
    camera.offset = {screenWidth / 2.0f, screenHeight / 2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 2.0f;

    // TODO: boundary of southeast
    int speed = 5;
    int exp = 0;
    int difficulty = 0;
    int diffIncreaseInterval = 800;
    int mobSpwanInterval[6] = {300, 250, 200, 150, 100, 50};
    size_t maxMobAcount = 200;
    long long frameCounter = 0;
    while (!WindowShouldClose()) {
        frameCounter++;
        if (frameCounter % diffIncreaseInterval == 0) {  // increase difficulty
            if (difficulty < 5) {
                difficulty++;
                printf("current difficulty: %d\n", difficulty);
            }
        }
        if (mobs.size() < maxMobAcount &&
            frameCounter % mobSpwanInterval[difficulty] == 0) {  // spwan mob
            int randx = rand() % WIDTH;
            int randy = rand() % HEIGHT;
            Character tmp;
            tmp.pos = {(float)randx * 31, (float)randy * 31};
            tmp.speed = 3;
            tmp.attackInterval = 60;
            mobs.push_back(tmp);
            printf("current mob number: %lld\n", mobs.size());
        }

        for (auto& c : mobs) {  // set mob speed
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

        updateMobPos(mobs, player_char);  // mob move

        for (auto& c : mobs) {  // mob attack
            if (getDistance(c.pos, player_char.pos) < 5) {
                if (c.attackCounter == 0) {
                    c.attackCounter = c.attackInterval;
                    exp -= 1;
                } else {
                    c.attackCounter--;
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
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            if (soccer_cd == 0) {
                Character tmp;
                tmp.pos = player_char.pos;
                tmp.dir = {GetMouseX() - camera.offset.x,
                           GetMouseY() - camera.offset.y};
                tmp.attackCounter = 0;
                tmp.speed = 6;
                soccers.push_back(tmp);
                soccer_cd = 10;
            }
        }

        auto iter = soccers.begin();
        while (iter != soccers.end()) {
            bool collision = false;
            auto i = mobs.begin();
            while (i != mobs.end()) {
                if (getDistance(i->pos, iter->pos) <= 30) {
                    i = mobs.erase(i);
                    exp += 2;
                    collision = true;
                } else {
                    i++;
                }
            }
            if (collision || iter->attackCounter >= 240) {
                iter = soccers.erase(iter);
            } else {
                iter++;
            }
        }

        for (auto& soccer : soccers) {
            soccer.updatePos();
            soccer.attackCounter += 1;
        }
        if (soccer_cd > 0) {
            soccer_cd -= 1;
        }

        if (player_char.pos.x <= marginx) {
            player_char.pos.x = marginx;
        }
        if (player_char.pos.y <= marginy) {
            player_char.pos.y = marginy;
        }
        if (player_char.pos.x >= WIDTH * 31 - marginx) {
            player_char.pos.x = WIDTH * 31 - marginx;
        }
        if (player_char.pos.y >= HEIGHT * 31 - marginy) {
            player_char.pos.y = HEIGHT * 31 - marginy;
        }
        BeginDrawing();

        ClearBackground(BLACK);
        camera.target = {player_char.pos.x, player_char.pos.y};

        camera.zoom += ((float)GetMouseWheelMove() * 0.05f);

        BeginMode2D(camera);
        drawMap(map);
        drawMobs(mobs);
        DrawTextureEx(player_text, player_char.pos, 0.f, 1.f, WHITE);
        for (auto& soccer : soccers) {
            DrawTextureEx(soccer_text, soccer.pos, 0.f, 0.3f, WHITE);
        }

        EndMode2D();
        displayInfo(exp, mobs.size(), difficulty);

        EndDrawing();
    }

    UnloadTexture(player_text);

    CloseWindow();
    return 0;
}