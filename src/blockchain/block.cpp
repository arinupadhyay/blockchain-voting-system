// Block.h
#include <string>
#include <ctime>
#include "HashManager.cpp"
class Block {
protected:
    int index;
    std::string timestamp;
    std::string previousHash;
    std::string hash;
    int nonce;

    std::string getCurrentTimestamp() const {
        time_t now = time(nullptr);
        return std::to_string(now);
    }

public:
    Block(int idx, const std::string& prevHash)
        : index(idx), previousHash(prevHash), nonce(0) {
        timestamp = getCurrentTimestamp();
    }

    virtual ~Block() = default;

    virtual std::string calculateHash() const {
        std::stringstream ss;
        ss << index << timestamp << previousHash << nonce;
        return HashManager::sha256(ss.str());
    }

    void mineBlock(int difficulty) {
        std::string target(difficulty, '0');
        do {
            nonce++;
            hash = calculateHash();
        } while (hash.substr(0, difficulty) != target);
    }

    std::string getHash() const { return hash; }
    std::string getPreviousHash() const { return previousHash; }
    int getIndex() const { return index; }
};