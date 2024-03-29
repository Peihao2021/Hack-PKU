#include <cmath>
#include <cstdio>
#include <list>
#include <string>
#include "character.h"
#include "map.h"
#include "noise.h"
#include "raylib.h"
#include "utils.h"

enum orientation { Down = 0, Left = 1, Right = 2, Up = 3 };

int main(void) {
    srand(time(0));
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    // const int birth_x = 800;
    // const int birth_y = 500;
    int marginx = screenWidth / 4;
    int marginy = screenHeight / 4;
    InitWindow(screenWidth, screenHeight, "Soccer War");
    Texture2D player_texts[12];
    for (int i = 0; i < 12; i++) {
        std::string file = "assets/player/" + std::to_string(i + 1) + ".png";
        player_texts[i] = LoadTexture(file.c_str());
    }
    Texture2D soccer_text = LoadTexture("assets/soccer.png");
    Texture2D stone_text = LoadTexture("assets/decoration/stone.png");
    Texture2D cactus_text = LoadTexture("assets/decoration/cactus.png");
    Texture2D branch_text = LoadTexture("assets/decoration/branch.png");
    Texture2D ore_text = LoadTexture("assets/ore.png");
    Texture2D gold_text = LoadTexture("assets/gold.png");
    Texture2D diamond_text = LoadTexture("assets/diamond.png");

    InitAudioDevice();
    Music bgm = LoadMusicStream("assets/bgm.mp3");
    PlayMusicStream(bgm);

    Character player_char;  // main character

    int soccer_cd = 0;
    std::list<Character> mobs;     // mobs
    std::list<Character> soccers;  // soccers
    Map map;                       // world map
    Perlin noise(20.00, 4, 100);
    map.initialize(noise);
    player_char.pos = getBirthPos(map);
    SetTargetFPS(60);

    Camera2D camera;
    camera.target = {player_char.pos.x, player_char.pos.y};
    camera.offset = {screenWidth / 2.0f, screenHeight / 2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 3.0f;

    int speed = 5;
    int exp = 0;
    int difficulty = 0;
    int diffIncreaseInterval = 800;
    int mobSpwanInterval[6] = {300, 250, 200, 150, 100, 50};
    int charaAnimationInterval = 10;
    int beingAttackedCounter = 0;
    size_t animationCounter = 0;
    size_t maxMobAcount = 200;
    size_t frameCounter = 0;

    std::list<Vector2> stones;  // generate stones
    for (int i = 0; i < 100; i++) {
        Vector2 pos = getBirthPos(map);
        stones.push_back(pos);
    }
    std::list<Vector2> cactus;  // generate cactus
    for (int i = 0; i < 50; i++) {
        Vector2 pos = getBirthPos(map);
        cactus.push_back(pos);
    }
    std::list<Vector2> branches;  // generate branches
    for (int i = 0; i < 50; i++) {
        Vector2 pos = getBirthPos(map);
        branches.push_back(pos);
    }
    std::list<Vector2> ores;  // generate ores
    for (int i = 0; i < 30; i++) {
        Vector2 pos = getBirthPos(map);
        ores.push_back(pos);
    }
    std::list<Vector2> golds;  // generate golds
    for (int i = 0; i < 20; i++) {
        Vector2 pos = getBirthPos(map);
        golds.push_back(pos);
    }
    std::list<Vector2> diamonds;  // generate diamonds
    for (int i = 0; i < 10; i++) {
        Vector2 pos = getBirthPos(map);
        diamonds.push_back(pos);
    }

    while (!WindowShouldClose()) {
        UpdateMusicStream(bgm);
        frameCounter++;
        if (frameCounter % diffIncreaseInterval == 0) {  // increase difficulty
            if (difficulty < 5) {
                difficulty++;
            }
        }
        if (mobs.size() < maxMobAcount &&
            frameCounter % mobSpwanInterval[difficulty] == 0) {  // spwan mob
            int randx = rand() % WIDTH;
            int randy = rand() % HEIGHT;
            Character tmp;
            tmp.pos = {(float)randx * 31, (float)randy * 31};
            int mobtype = rand() % 2;
            if (mobtype == 1) {
                tmp.type = 6;
                tmp.speedOnLand = 3;
                tmp.speedInSea = 2;
                tmp.attackInterval = 40;
                mobs.push_back(tmp);
            } else {
                tmp.type = rand() % 5 + 1;
                tmp.speedOnLand = 2;
                tmp.speedInSea = 5;
                tmp.attackInterval = 40;
                mobs.push_back(tmp);
            }
        }

        for (auto& c : mobs) {  // set mob speed
            int axis_x = c.pos.x / 31;
            int axis_y = c.pos.y / 31;
            if (axis_x >= WIDTH || axis_y >= HEIGHT || axis_x <= 0 ||
                axis_y <= 0) {
                c.speed = -c.speed;
            } else if (map.map[axis_x][axis_y] == BlockType::Water ||
                       map.map[axis_x][axis_y] == BlockType::Sea) {
                c.speed = c.speedInSea + rand() % 2 - 1;
            } else {
                c.speed = c.speedOnLand + rand() % 2 - 1;
            }
        }

        updateMobPos(mobs, player_char);  // mob move
        for (auto& c : mobs) {            // mob attack
            if (getDistance(c.pos, player_char.pos) < 8) {
                if (c.attackCounter == 0) {
                    c.attackCounter = c.attackInterval;
                    beingAttackedCounter = 10;
                    exp -= 10;
                } else {
                    c.attackCounter--;
                }
            }
        }

        int axis_x = player_char.pos.x / 31;
        int axis_y = player_char.pos.y / 31;
        if (axis_x >= WIDTH || axis_y >= HEIGHT || axis_x <= 0 || axis_y <= 0) {
            speed = -speed;
        } else if (map.map[axis_x][axis_y] == BlockType::Water ||
                   map.map[axis_x][axis_y] == BlockType::Sea) {
            speed = 1;
        } else {
            speed = 5;
        }
        orientation orient = Down;
        bool hasKeyPressed = 0;
        if (IsKeyDown(KEY_W)) {  // player move
            player_char.pos.y -= speed;
            orient = Up;
            hasKeyPressed = 1;
        }
        if (IsKeyDown(KEY_S)) {
            player_char.pos.y += speed;
            orient = Down;
            hasKeyPressed = 1;
        }
        if (IsKeyDown(KEY_A)) {
            player_char.pos.x -= speed;
            orient = Left;
            hasKeyPressed = 1;
        }
        if (IsKeyDown(KEY_D)) {
            player_char.pos.x += speed;
            orient = Right;
            hasKeyPressed = 1;
        }
        if (hasKeyPressed) {
            animationCounter++;
        }

        for (auto ore = ores.begin(); ore != ores.end(); ore++) {  // check ores
            if (getDistance(player_char.pos, {ore->x, ore->y}) < 25) {
                ores.erase(ore);
                ores.push_back(getBirthPos(map));
                exp += 5;
                break;
            }
        }
        for (auto gold = golds.begin(); gold != golds.end();
             gold++) {  // check ores
            if (getDistance(player_char.pos, {gold->x, gold->y}) < 25) {
                golds.erase(gold);
                golds.push_back(getBirthPos(map));
                exp += 10;
                break;
            }
        }
        for (auto diamond = diamonds.begin(); diamond != diamonds.end();
             diamond++) {  // check ores
            if (getDistance(player_char.pos, {diamond->x, diamond->y}) < 25) {
                diamonds.erase(diamond);
                diamonds.push_back(getBirthPos(map));
                exp += 20;
                break;
            }
        }

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
                soccer_cd = 80;
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
        if (camera.zoom <= 2.5f) {
            camera.zoom = 2.5f;
        }

        BeginMode2D(camera);
        drawMap(map);  // draw map
        for (auto& st : stones) {
            DrawTextureEx(stone_text, st, 0.f, 1.f, WHITE);
        }
        for (auto& cac : cactus) {
            DrawTextureEx(cactus_text, cac, 0.f, 1.f, WHITE);
        }
        for (auto& br : branches) {
            DrawTextureEx(branch_text, br, 0.f, 1.f, WHITE);
        }
        for (auto& ore : ores) {
            DrawTextureEx(ore_text, ore, 0.f, 1.f, WHITE);
        }
        for (auto& dia : diamonds) {
            DrawTextureEx(diamond_text, dia, 0.f, 0.5f, WHITE);
        }
        for (auto& gold : golds) {
            DrawTextureEx(gold_text, gold, 0.f, 0.5f, WHITE);
        }
        drawMobs(mobs);  // draw mobs
        int numberOfPic = 0;
        if (hasKeyPressed) {
            numberOfPic = (animationCounter / charaAnimationInterval) % 3;
        } else {
            numberOfPic = 0;
        }
        if (beingAttackedCounter > 0)
            beingAttackedCounter--;
        DrawTextureEx(player_texts[(int(orient)) * 3 + numberOfPic],
                      player_char.pos, 0.f, 1.f,
                      beingAttackedCounter > 0 ? RED : WHITE);  // draw player
        for (auto& soccer : soccers) {                          // draw soccers
            DrawTextureEx(soccer_text, soccer.pos, 0.f, 1.f, WHITE);
        }

        EndMode2D();
        displayInfo(exp, mobs.size(), difficulty, soccer_cd);

        EndDrawing();
    }
    for (auto& t : player_texts)
        UnloadTexture(t);

    CloseAudioDevice();
    CloseWindow();
    return 0;
}