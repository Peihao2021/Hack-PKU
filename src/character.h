#ifndef CHARACTER_H_
#define CHARACTER_H_

#include <vector>
#include "raylib.h"

enum class Skill: int {
    Null = -1,
    FootBall = 0,
    Sonic = 1,
    Umbrella = 2,
    Fishing = 3,
};

class Character {
   public:
    Character();
    void updatePos();
    int hp;
    Vector2 pos;
    Vector2 dir;
    int speed;
    Skill skill;
    int attackInterval;
    int attackCounter;
    int speedOnLand;
    int speedInSea;
    int type;
};

bool operator==(const Character& lhs, const Character& rhs);

#endif  // CHARACTER_H_