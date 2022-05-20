#ifndef CHARACTER_H_
#define CHARACTER_H_

#include <vector>
#include "raylib.h"

enum class Skill: int {
    FootBall = 0,
    Sonic = 1,
    Umbrella = 2,
};

class Character {
   public:
    Character();
    int hp;
    int hunger;
    int exp;
    int mp;
    Vector2 pos;
};

#endif  // CHARACTER_H_