#include "block.h"
#include <iostream>

int main() {

    Block block(1, "0");

    std::cout << "Mining block..." << std::endl;

    block.mineBlock(2);

    std::cout << "Block mined!" << std::endl;
    std::cout << "Block Index: " << block.getIndex() << std::endl;
    std::cout << "Previous Hash: " << block.getPreviousHash() << std::endl;
    std::cout << "Hash: " << block.getHash() << std::endl;

    return 0;
}