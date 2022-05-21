
#include "utils.h"
#include <iostream>
#include <sstream>

void drawMap(const Map& map) {
    static Texture2D WATER_TEXT =
        LoadTexture(BLOCK_PATH[(int)BlockType::Water].c_str());
    static Texture2D SEA_TEXT =
        LoadTexture(BLOCK_PATH[(int)BlockType::Sea].c_str());
    static Texture2D GRASS_TEXT =
        LoadTexture(BLOCK_PATH[(int)BlockType::Grass].c_str());
    static Texture2D SAND_TEXT =
        LoadTexture(BLOCK_PATH[(int)BlockType::Sand].c_str());

    float x = 0;
    float y = 0;

    float d = 31;

    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            x = i * d;
            y = j * d;
            switch (map.map[i][j]) {
                case BlockType::Water:
                    DrawTextureEx(WATER_TEXT, {x, y}, 0.f, 1.f, WHITE);
                    break;
                case BlockType::Sea:
                    DrawTextureEx(SEA_TEXT, {x, y}, 0.f, 1.f, WHITE);
                    break;
                case BlockType::Grass:
                    DrawTextureEx(GRASS_TEXT, {x, y}, 0.f, 1.f, WHITE);
                    break;
                case BlockType::Sand:
                    DrawTextureEx(SAND_TEXT, {x, y}, 0.f, 1.f, WHITE);
                    break;
                default:
                    break;
            }
        }
    }
}

void updateMobPos(std::list<Character>& mobs, Character& player) {
    for (auto& c : mobs) {
        c.dir = {player.pos.x - c.pos.x, player.pos.y - c.pos.y};
        c.updatePos();
    }
}

void drawMobs(const std::list<Character>& mobs) {
    static Texture2D MOB_TEXT = LoadTexture("assets/tiger.png");
    for (auto& c : mobs) {
        // std::cout << "ok" << std::endl;
        DrawTextureEx(MOB_TEXT, c.pos, 0.f, 1.f, WHITE);
    }
}

double getDistance(const Vector2& a, const Vector2& b) {
    return sqrt(((a.x - b.x) * (a.x - b.x)) + ((a.y - b.y) * (a.y - b.y)));
}

Vector2 getBirthPos(Map& map) {
    srand(time(0));
    int randx, randy = 0;
    do {
        randx = rand() % WIDTH;
        randy = rand() % HEIGHT;
    } while (map.map[randx][randy] == BlockType::Water || map.map[randx][randy] == BlockType::Sea);
    return Vector2{float(randx * 31), float(randy * 31)};
}

void displayInfo(int exp, int mob_cnt, int difficulty) {
    std::stringstream buffer;
    buffer << "| Your Exp: " << exp << " | Mob number: " << mob_cnt
           << " | Difficulty: " << difficulty << " |";
    DrawRectangle(10, 10, 1300, 80, GRAY);
    DrawText(buffer.str().c_str(), 25, 25, 50, WHITE);
}