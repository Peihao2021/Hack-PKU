#include "map.h"

Map::Map() {
    map.resize(HEIGHT, std::vector<BlockType>(WIDTH));
}

void Map::initialize(Perlin& noise) {
    double thre1 = -200.0;
    double thre2 = 500.0;
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            double val = noise.perlinNoise(i, j);
            if (val < thre1)
                map[i][j] = BlockType::Water;
            else if (val < thre2)
                map[i][j] = BlockType::Sand;
            else
                map[i][j] = BlockType::Dirt;
        }
    }
}