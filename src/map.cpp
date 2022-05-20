#include "map.h"

Map::Map() {
    map.resize(HEIGHT, std::vector<BlockType>(WIDTH));
}

void Map::initialize(Perlin& noise, double thre) {
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            map[i][j] = noise.perlinNoise(i, j) > thre ? BlockType::Water
                                                       : BlockType::Dirt;
        }
    }
}