#include "map.h"
#include <cmath>

Map::Map() {
    map.resize(HEIGHT, std::vector<BlockType>(WIDTH));
}

void Map::initialize(Perlin& noise) {
    double thre_water = -200.0;
    double thre_sand = 500.0;
    double thre_dirt = 700.0;
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            double val = noise.perlinNoise(i, j);
            if (val < thre_water)
                map[i][j] = BlockType::Water;
            else if (val < thre_sand)
                map[i][j] = BlockType::Sand;
            else if (val < thre_dirt)
                map[i][j] = BlockType::Dirt;
            else
                map[i][j] = BlockType::Grass;
        }
    }
}

CharacterMap::CharacterMap() {}


bool inRange(int x1, int y1, int x2, int y2, double range) {
    double dist = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    return (dist <= range);
}