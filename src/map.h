#ifndef MAP_H_
#define MAP_H_

#define WIDTH 100
#define HEIGHT 100

#include "block.h"
#include "noise.h"
#include <vector>

enum BlockType {
    Water = 0,
    Dirt = 1,
    GrassNormal = 3,
    MainCharacter = 4,
    Npc = 5,
};

class Map {
public:
    Map();

    const std::vector<std::vector<BlockType>>& map() { return map_; }
    // BlockType** map() { return map_; }
    void initialize(Perlin& noise, double thre);

private:
    std::vector<std::vector<BlockType>> map_;
    // BlockType map_[WIDTH][HEIGHT] = { Water };
};



#endif // MAP_H_