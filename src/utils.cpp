
#include "utils.h"

void drawMap(const Map& map) {

    float x = 0;
    float y = 0;

    float d = WATER_TEXT.width;

    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            x = i * d;
            y = j * d;
            switch (map.map[i][j]) {
                case BlockType::Water:
                    DrawTextureEx(WATER_TEXT, {x, y}, 0.f, 1.f, WHITE);
                    break;
                case BlockType::Dirt:
                    DrawTextureEx(DIRT_TEXT, {x, y}, 0.f, 1.f, WHITE);
                    break;
                case BlockType::Grass:
                    DrawTextureEx(GRASS_TEXT, {x, y}, 0.f, 1.f, WHITE);
                    break;
                default:
                    break;
            }
        }
    }

}