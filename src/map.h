#ifndef MAP_H_
#define MAP_H_

#include "block.h"

#include <vector>

class Map {
   public:
    Map();

    const std::vector<std::vector<Block*>>& map() { return map_; }

   private:
    std::vector<std::vector<Block*>> map_;
    
};

#endif  // MAP_H_