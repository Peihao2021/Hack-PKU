#include "map.h"
#include <cmath>

Map::Map() {
    map.resize(HEIGHT, std::vector<BlockType>(WIDTH));
}

void Map::initialize(Perlin& noise) {
    double thre = -100.0;
    double thre1 = -700.0;
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            double val = noise.perlinNoise(i, j);
            if (val < thre1)
                map[i][j] = BlockType::Sea;
            else if(val < thre)
                map[i][j] = BlockType::Water;
            else
                map[i][j] = BlockType::Sand;
        }
    }
}

bool inRange(int x1, int y1, int x2, int y2, double range) {
    double dist = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    return (dist <= range);
}