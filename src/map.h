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
    Dirt = 2,
    Sand = 3,
};

const std::vector<std::string> BLOCK_PATH = {
    "assets/front_sea.png", "assets/water.png", "assets/dirt.png",
    "assets/sand.png"};

const int WIDTH = 300;
const int HEIGHT = 300;

class Map {
   public:
    Map();
    void initialize(Perlin& noise);

    std::vector<std::vector<BlockType>> map;
};

#endif  // MAP_H_