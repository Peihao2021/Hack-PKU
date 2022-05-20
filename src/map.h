#ifndef MAP_H_
#define MAP_H_

#include <string>
#include <vector>
#include "noise.h"
#include "raylib.h"

enum class BlockType : int {
    Water = 0,
    Dirt = 1,
    Grass = 2,
};

const std::vector<std::string> BLOCK_PATH = {
    "assets/water.png", "assets/dirt.png", "assets/grass.png"};

const int WIDTH = 100;
const int HEIGHT = 100;

const Texture2D WATER_TEXT =
    LoadTexture(BLOCK_PATH[(int)BlockType::Water].c_str());
const Texture2D DIRT_TEXT =
    LoadTexture(BLOCK_PATH[(int)BlockType::Dirt].c_str());
const Texture2D GRASS_TEXT =
    LoadTexture(BLOCK_PATH[(int)BlockType::Grass].c_str());

class Map {
   public:
    Map();
    void initialize(Perlin& noise, double thre);

    std::vector<std::vector<BlockType>> map;
};

#endif  // MAP_H_