#ifndef MAP_H_
#define MAP_H_

#include <string>
#include <vector>
#include "character.h"
#include "noise.h"
#include "raylib.h"

enum class BlockType : int {
    Water = 0,
    Dirt = 1,
    Grass = 2,
    Sand = 3,
};

const std::vector<std::string> BLOCK_PATH = {
    "assets/water.png", "assets/dirt.png", "assets/grass.png",
    "assets/sand.png"};

const int WIDTH = 300;
const int HEIGHT = 300;

class Map {
   public:
    Map();
    void initialize(Perlin& noise);

    std::vector<std::vector<BlockType>> map;
};

class CharacterMap {
   public:
    CharacterMap();

    bool inRange(int x1, int y1, int x2, int y2, double range);

    std::vector<std::vector<Character>> map;
};

#endif  // MAP_H_