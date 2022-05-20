#ifndef BLOCK_H_
#define BLOCK_H_

#include <string>

class Block {
   public:
    Block();
    enum BlockType {
        MainCharacter = 0,
        Npc = 1,
        Dirt = 2,
        Water = 3,
        GrassNormal = 3,
    };

    BlockType type;
    std::string asset_path;
};


#endif  // BLOCK_H_
