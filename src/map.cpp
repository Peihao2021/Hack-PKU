#include "map.h"

Map::Map() {
    map_.resize(HEIGHT, std::vector<BlockType>(WIDTH));

}

void Map::initialize(Perlin& noise, double thre){
    for(int i = 0; i < WIDTH; i++){
        for(int j = 0; j < HEIGHT; j++){
            map_[i][j] = noise.perlinNoise(i, j) > thre ? Dirt : Water;
        }
    }
}