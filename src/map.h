#ifndef MAP_H_
#define MAP_H_

#include <string>
#include <vector>
#include "character.h"
#include "noise.h"
#include "raylib.h"

enum class BlockType : int {
    Water = 0,
    Sea = 1,
    Grass = 2,
    Sand = 3,
};

const std::vector<std::string> BLOCK_PATH = {
    "assets/front_sea.png", "assets/water.png", "assets/grass.png",
    "assets/sand.png"};

const int WIDTH = 100;
const int HEIGHT = 100;

class Map {
   public:
    Map();
    void initialize(Perlin& noise);

    std::vector<std::vector<BlockType>> map;
};

#endif  // MAP_H_