#include "character.h"
#include <cmath>

Character::Character() {
    type = 0;
    hp = 100;
    attackCounter = 0;
}

void Character::updatePos() {
    pos.x += dir.x * speed / sqrt(dir.x * dir.x + dir.y * dir.y) + rand() / double(RAND_MAX) * 2 - 1;
    pos.y += dir.y * speed / sqrt(dir.x * dir.x + dir.y * dir.y) + rand() / double(RAND_MAX) * 2 - 1;
}


bool operator==(const Character& lhs, const Character& rhs) {
    if (lhs.pos.x == rhs.pos.x && lhs.pos.y == rhs.pos.y) {
        return true;
    } else {
        return false;
    }
}