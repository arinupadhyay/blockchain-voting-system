// HashManager.h
#include <string>
#include <sstream>
#include <iomanip>
// If your team allows external libs, use OpenSSL's SHA256.
// Otherwise here's a simple SHA-256 implementation stub interface:
class HashManager {
public:
    static std::string sha256(const std::string& input);
};