#ifndef UTILS_H_
#define UTILS_H_

#include <list>
#include "character.h"
#include "map.h"
#include "raylib.h"

void drawMap(const Map& map);
void updateCharacterPos(std::list<Character>& characters, Character& player);
void drawCharacters(const std::list<Character>& characters);
double getDistance(const Vector2& a, const Vector2& b);
Vector2 getBirthPos(Map& map);
#endif  // UTILS_H_