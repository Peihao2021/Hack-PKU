#ifndef UTILS_H_
#define UTILS_H_

#include <list>
#include "character.h"
#include "map.h"
#include "raylib.h"

void drawMap(const Map& map);
void updateMobPos(std::list<Character>& characters, Character& player);
void drawMobs(const std::list<Character>& characters);
double getDistance(const Vector2& a, const Vector2& b);
Vector2 getBirthPos(Map& map);
void displayInfo(int exp, int mob_cnt, int difficulty, int cd);
#endif  // UTILS_H_