#include "Blockchain.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>

namespace {
std::vector<std::string> splitOn(const std::string& s, char delim) {
    std::vector<std::string> parts;
    std::string cur;
    for (char c : s) {
        if (c == delim) { parts.push_back(cur); cur.clear(); }
        else cur += c;
    }
    parts.push_back(cur);
    return parts;
}
}

bool Blockchain::validCandidateName(const std::string& name) {
    return !name.empty() && name.find_first_of("|\r\n") == std::string::npos;
}

Blockchain::Blockchain(const std::vector<std::string>& candidateList,
                       int diff, const std::string& s)
    : candidates(candidateList), difficulty(diff), salt(s), votingOpen(true) {
    if (candidates.empty()) throw std::invalid_argument("At least one candidate is required");
    for (const auto& c : candidates)
        if (!validCandidateName(c)) throw std::invalid_argument("Invalid candidate name: " + c);
    if (difficulty < 1 || difficulty > 8) throw std::invalid_argument("Difficulty must be 1-8");

    auto genesis = std::make_unique<VoteBlock>(0, "0", "GENESIS", "GENESIS");
    genesis->mineBlock(difficulty);
    chain.push_back(std::move(genesis));
}

Blockchain::Blockchain(const std::string& s, LoadTag)
    : difficulty(3), salt(s), votingOpen(true) {}

std::string Blockchain::hashVoter(const std::string& voterId) const {
    return HashManager::sha256(salt + voterId);
}

bool Blockchain::registerVoter(const std::string& voterId) {
    if (voterId.empty()) return false;
    return registeredVoters.insert(hashVoter(voterId)).second;
}

bool Blockchain::isRegistered(const std::string& voterId) const {
    return registeredVoters.count(hashVoter(voterId)) > 0;
}

bool Blockchain::hasVoted(const std::string& voterId) const {
    return votedVoters.count(hashVoter(voterId)) > 0;
}

bool Blockchain::castVote(const std::string& voterId, const std::string& candidate,
                          std::string& error) {
    if (!votingOpen) { error = "Voting is closed"; return false; }
    if (std::find(candidates.begin(), candidates.end(), candidate) == candidates.end()) {
        error = "Unknown candidate"; return false;
    }
    const std::string vh = hashVoter(voterId);
    if (!registeredVoters.count(vh)) { error = "Voter not registered"; return false; }
    if (votedVoters.count(vh))       { error = "Voter has already voted"; return false; }

    auto block = std::make_unique<VoteBlock>(static_cast<int>(chain.size()),
                                             chain.back()->getHash(), vh, candidate);
    block->mineBlock(difficulty);
    chain.push_back(std::move(block));
    votedVoters.insert(vh);
    return true;
}

std::map<std::string, int> Blockchain::tally() const {
    std::map<std::string, int> counts;
    for (const auto& c : candidates) counts[c] = 0;
    for (size_t i = 1; i < chain.size(); ++i) ++counts[chain[i]->getCandidateId()];
    return counts;
}

std::vector<std::string> Blockchain::winners() const {
    const auto counts = tally();
    int best = 0;
    for (const auto& [name, n] : counts) best = std::max(best, n);
    std::vector<std::string> result;
    if (best == 0) return result;
    for (const auto& [name, n] : counts)
        if (n == best) result.push_back(name);
    return result;
}

bool Blockchain::isChainValid() const {
    if (chain.empty() || chain[0]->getPreviousHash() != "0") return false;
    const std::string target(difficulty, '0');
    std::set<std::string> seen;
    for (size_t i = 0; i < chain.size(); ++i) {
        const VoteBlock& b = *chain[i];
        if (b.getIndex() != static_cast<int>(i)) return false;
        if (b.getHash() != b.calculateHash()) return false;
        if (b.getHash().compare(0, difficulty, target) != 0) return false;
        if (i == 0) continue;
        if (b.getPreviousHash() != chain[i - 1]->getHash()) return false;
        if (!seen.insert(b.getVoterIdHash()).second) return false;            // duplicate voter
        if (!registeredVoters.count(b.getVoterIdHash())) return false;        // unregistered voter
        if (std::find(candidates.begin(), candidates.end(), b.getCandidateId())
            == candidates.end()) return false;                                // unknown candidate
    }
    return true;
}

bool Blockchain::containsHash(const std::string& blockHash) const {
    return std::any_of(chain.begin() + 1, chain.end(),
        [&](const std::unique_ptr<VoteBlock>& b) { return b->getHash() == blockHash; });
}

void Blockchain::print() const {
    for (const auto& b : chain)
        std::cout << "Block " << b->getIndex() << " | candidate=" << b->getCandidateId()
                  << " | nonce=" << b->getNonce() << "\n  hash=" << b->getHash()
                  << "\n  prev=" << b->getPreviousHash() << "\n";
}

// ---------------- persistence ----------------
// File format (plain text):
//   VOTECHAIN 1 / difficulty N / open 0|1 / candidate NAME ... / voter HASH ...
//   block index|prevHash|voterHash|candidate|timestamp|nonce|hash
bool Blockchain::saveToFile(const std::string& path) const {
    const std::string tmp = path + ".tmp";
    {
        std::ofstream out(tmp, std::ios::trunc);
        if (!out) return false;
        out << "VOTECHAIN 1\n"
            << "difficulty " << difficulty << "\n"
            << "open " << (votingOpen ? 1 : 0) << "\n";
        for (const auto& c : candidates) out << "candidate " << c << "\n";
        for (const auto& v : registeredVoters) out << "voter " << v << "\n";
        for (const auto& b : chain)
            out << "block " << b->getIndex() << '|' << b->getPreviousHash() << '|'
                << b->getVoterIdHash() << '|' << b->getCandidateId() << '|'
                << b->getTimestamp() << '|' << b->getNonce() << '|' << b->getHash() << "\n";
        out.flush();
        if (!out) return false;
    }
    std::error_code ec;
    std::filesystem::rename(tmp, path, ec);   // write-then-rename: no half-written file
    return !ec;
}

std::unique_ptr<Blockchain> Blockchain::loadFromFile(const std::string& path,
                                                     const std::string& salt,
                                                     std::string& error) {
    std::ifstream in(path);
    if (!in) { error = "Cannot open " + path; return nullptr; }

    std::string line;
    if (!std::getline(in, line) || line.rfind("VOTECHAIN 1", 0) != 0) {
        error = "Not a valid vote chain file";
        return nullptr;
    }

    std::unique_ptr<Blockchain> bc(new Blockchain(salt, LoadTag{}));
    try {
        while (std::getline(in, line)) {
            if (!line.empty() && line.back() == '\r') line.pop_back();
            if (line.empty()) continue;
            if (line.rfind("difficulty ", 0) == 0)      bc->difficulty = std::stoi(line.substr(11));
            else if (line.rfind("open ", 0) == 0)       bc->votingOpen = (line.substr(5) == "1");
            else if (line.rfind("candidate ", 0) == 0)  bc->candidates.push_back(line.substr(10));
            else if (line.rfind("voter ", 0) == 0)      bc->registeredVoters.insert(line.substr(6));
            else if (line.rfind("block ", 0) == 0) {
                auto f = splitOn(line.substr(6), '|');
                if (f.size() != 7) { error = "Malformed block record"; return nullptr; }
                bc->chain.push_back(std::make_unique<VoteBlock>(
                    std::stoi(f[0]), f[1], f[2], f[3], f[4], std::stoi(f[5]), f[6]));
            } else {
                error = "Unrecognised line in file";
                return nullptr;
            }
        }
    } catch (const std::exception&) {
        error = "File contains an invalid number";
        return nullptr;
    }

    if (bc->difficulty < 1 || bc->difficulty > 8) { error = "Invalid difficulty"; return nullptr; }
    if (bc->candidates.empty() || bc->chain.empty()) { error = "File is incomplete"; return nullptr; }
    if (!bc->isChainValid()) { error = "Chain failed validation - the file has been tampered with"; return nullptr; }

    for (size_t i = 1; i < bc->chain.size(); ++i)
        bc->votedVoters.insert(bc->chain[i]->getVoterIdHash());
    return bc;
}
