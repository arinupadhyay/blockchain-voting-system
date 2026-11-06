#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "VoteBlock.h"
#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>

class Blockchain {
private:
    struct LoadTag {};                        // used by loadFromFile only

    std::vector<std::unique_ptr<VoteBlock>> chain;
    std::set<std::string> registeredVoters;   // hashed voter IDs
    std::set<std::string> votedVoters;        // hashed voter IDs who already voted
    std::vector<std::string> candidates;
    int difficulty;
    std::string salt;
    bool votingOpen;

    Blockchain(const std::string& salt, LoadTag);
    static bool validCandidateName(const std::string& name);

public:
    // Throws std::invalid_argument for an empty list or names containing '|' / newlines.
    Blockchain(const std::vector<std::string>& candidateList,
               int difficulty = 3, const std::string& salt = "change-me");

    std::string hashVoter(const std::string& voterId) const;

    // Voters
    bool registerVoter(const std::string& voterId);          // false if already registered
    bool isRegistered(const std::string& voterId) const;
    bool hasVoted(const std::string& voterId) const;

    // Voting
    bool castVote(const std::string& voterId, const std::string& candidate,
                  std::string& error);                       // mines one block per vote
    void closeVoting() { votingOpen = false; }
    bool isVotingOpen() const { return votingOpen; }

    // Results & audit
    std::map<std::string, int> tally() const;
    std::vector<std::string> winners() const;                // several names = tie, empty = no votes
    bool isChainValid() const;
    bool containsHash(const std::string& blockHash) const;   // vote receipt check
    size_t size() const { return chain.size(); }
    size_t totalVotes() const { return chain.size() - 1; }
    const std::vector<std::string>& getCandidates() const { return candidates; }
    VoteBlock& blockAt(size_t i) { return *chain[i]; }       // for tamper tests
    void print() const;

    // Persistence
    bool saveToFile(const std::string& path) const;
    static std::unique_ptr<Blockchain> loadFromFile(const std::string& path,
                                                    const std::string& salt,
                                                    std::string& error);
};

#endif
