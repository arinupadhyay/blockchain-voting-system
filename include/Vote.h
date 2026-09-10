#ifndef VOTE_H
#define VOTE_H

#include <string>
#include <iostream>
#include <chrono>
#include <ctime>

using namespace std;

class Vote {
private:
    string voterID;
    string candidateID;
    string timestamp;

    // Helper method to automatically fetch current system timestamp
    string generateTimestamp();

public:
    // 1. Constructors
    Vote();
    Vote(const string& vId, const string& cId);

    // 2. Const Getters
    string getVoterID() const;
    string getCandidateID() const;
    string getTimestamp() const;

    // 3. Serialization Helper (Converts vote data to a single string for hashing)
    std::string serialize() const;

    // 4. Operator Overloads
    bool operator==(const Vote& other) const;
    friend ostream& operator<<(ostream& os, const Vote& vote);
};

#endif // VOTE_H
