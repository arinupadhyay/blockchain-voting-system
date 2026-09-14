
#include "Block.h"
class VoteBlock : public Block {
private:
    std::string voterIdHash;   // hashed for anonymity
    std::string candidateId;

public:
    VoteBlock(int idx, const std::string& prevHash,
               const std::string& voterHash, const std::string& candidate)
        : Block(idx, prevHash), voterIdHash(voterHash), candidateId(candidate) {}

    // Override to include vote data in the hash
    std::string calculateHash() const override {
        std::stringstream ss;
        ss << index << timestamp << previousHash << voterIdHash << candidateId << nonce;
        return HashManager::sha256(ss.str());
    }

    std::string getCandidateId() const { return candidateId; }
    std::string getVoterIdHash() const { return voterIdHash; }
};