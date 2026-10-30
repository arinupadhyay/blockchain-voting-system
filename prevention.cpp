#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

class VotingSystem {
private:
    vector<string> candidates;
    map<int, bool> voters;
    map<string, int> votes;

public:
    void addCandidate(string name) {
        candidates.push_back(name);
        votes[name] = 0;
    }

    void castVote(int voterID, string candidate) {
        if (voters[voterID]) {
            cout << "Error: You have already voted!\n";
            return;
        }

        if (votes.find(candidate) == votes.end()) {
            cout << "Invalid candidate!\n";
            return;
        }

        votes[candidate]++;
        voters[voterID] = true;

        cout << "Vote cast successfully!\n";
    }

    void showResults() {
        cout << "\n--- Election Results ---\n";

        for (auto candidate : candidates) {
            cout << candidate << ": "
                 << votes[candidate] << " votes\n";
        }
    }
};

int main() {
    VotingSystem election;

    election.addCandidate("Rahul");
    election.addCandidate("Aman");

    election.castVote(101, "Rahul");
    election.castVote(102, "Aman");
    election.castVote(101, "Aman");

    election.showResults();

    return 0;
}