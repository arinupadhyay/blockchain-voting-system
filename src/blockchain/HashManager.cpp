#include "HashManager.h"
#include <sstream>
#include <iomanip>
#include <functional>

std::string HashManager::sha256(const std::string& input)
{
    std::hash<std::string> hasher;

    unsigned long long h1 = hasher(input);
    unsigned long long h2 = hasher(input + "1");
    unsigned long long h3 = hasher(input + "2");
    unsigned long long h4 = hasher(input + "3");

    std::stringstream ss;

    ss << std::hex
       << std::setw(16) << std::setfill('0') << h1
       << std::setw(16) << std::setfill('0') << h2
       << std::setw(16) << std::setfill('0') << h3
       << std::setw(16) << std::setfill('0') << h4;

    return ss.str();
}