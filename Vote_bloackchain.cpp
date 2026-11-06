
#include <iostream>
#include <vector>
#include <string>
#include <functional>
using namespace std;

class Block {
public:
    int index;
    string candidate;
    string previousHash;
    string hash;

    Block(int idx, string vote, string prev) {
        index = idx;
        candidate = vote;
        previousHash = prev;
        hash = calculateHash();
    }

    string calculateHash() {
        string data = to_string(index) + candidate + previousHash;
        return to_string(hash<string>{}(data));
    }
};

class Blockchain {
private:
    vector<Block> chain;

public:
    Blockchain() {
        chain.push_back(Block(0, "Genesis Block", "0"));
    }

    void addVote(string candidate) {
        string previous = chain.back().hash;

        Block newBlock(
            chain.size(),
            candidate,
            previous
        );

        chain.push_back(newBlock);

        cout << "Vote recorded successfully!\n";
    }

    void displayVotes() {
        for (const auto& block : chain) {
            cout << "\nBlock: " << block.index;
            cout << "\nCandidate: " << block.candidate;
            cout << "\nPrevious Hash: " << block.previousHash;
            cout << "\nCurrent Hash: " << block.hash;
            cout << "\n----------------------\n";
        }
    }

    bool verifyChain() {
        for (int i = 1; i < chain.size(); i++) {

            if (chain[i].hash != chain[i].calculateHash())
                return false;

            if (chain[i].previousHash != chain[i - 1].hash)
                return false;
        }

        return true;
    }
};

int main() {
    Blockchain votingSystem;

    votingSystem.addVote("Candidate A");
    votingSystem.addVote("Candidate B");
    votingSystem.addVote("Candidate A");

    cout << "\n--- BLOCKCHAIN LEDGER ---\n";
    votingSystem.displayVotes();

    cout << "\nBlockchain Status: ";

    if (votingSystem.verifyChain())
        cout << "VALID\n";
    else
        cout << "TAMPERED\n";

    return 0;
}
