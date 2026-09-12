#ifndef HASHMANAGER_H
#define HASHMANAGER_H

#include <string>

class HashManager {
public:
    static std::string sha256(const std::string& input);
};

#endif