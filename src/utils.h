#ifndef UTILS_H_
#define UTILS_H_

#include "map.h"
#include "character.h"
#include "raylib.h"
#include <list>

void drawMap(const Map& map);
void updateCharacterPos(std::list<Character>& characters, Character& player);
void drawCharacters(const std::list<Character>& characters);
double getDistance(const Vector2& a, const Vector2& b);
Vector2 getBirthPos(Map& map);
#endif  // UTILS_H_