#ifndef CHARACTER_H_
#define CHARACTER_H_

#include <string>

class Character {
   public:
    Character(const std::string& asset_path);
    std::string asset_path;
};

#endif  // CHARACTER_H_