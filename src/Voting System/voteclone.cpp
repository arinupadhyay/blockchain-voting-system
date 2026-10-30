
#include <iostream>
#include <string>
#include <map>
using namespace std;

enum class ElectionStatus {
    NOT_STARTED,
    ONGOING,
    ENDED
};

class Election {
private:
    int electionId;
    string electionName;
    ElectionStatus status;

    // Candidate ID -> Candidate name
    map<int, string> candidates;

    // Candidate ID -> Number of votes
    map<int, int> voteCounts;

public:
    Election(int id, string name)
        : electionId(id),
          electionName(name),
          status(ElectionStatus::NOT_STARTED) {}

    bool addCandidate(int id, string name) {
        if (status != ElectionStatus::NOT_STARTED ||
            candidates.count(id) > 0) {
            return false;
        }

        candidates[id] = name;
        voteCounts[id] = 0;
        return true;
    }

    bool startElection() {
        if (status != ElectionStatus::NOT_STARTED ||
            candidates.empty()) {
            return false;
        }

        status = ElectionStatus::ONGOING;
        return true;
    }

    bool recordVote(int candidateId) {
        if (status != ElectionStatus::ONGOING ||
            candidates.count(candidateId) == 0) {
            return false;
        }

        voteCounts[candidateId]++;
        return true;
    }

    bool endElection() {
        if (status != ElectionStatus::ONGOING) {
            return false;
        }

        status = ElectionStatus::ENDED;
        return true;
    }

    ElectionStatus getStatus() const {
        return status;
    }

    void showResults() const {
        if (status != ElectionStatus::ENDED) {
            cout << "Results are not available yet.\n";
            return;
        }

        cout << "\nElection Results: "
             << electionName << "\n";

        for (const auto& candidate : candidates) {
            cout << candidate.first << ". "
                 << candidate.second
                 << " - Votes: "
                 << voteCounts.at(candidate.first)
                 << "\n";
        }
    }
};

int main() {
    Election election(101, "College Election");

    election.addCandidate(1, "Rahul");
    election.addCandidate(2, "Aman");

    if (election.startElection()) {
        cout << "Election started!\n";
    }

    election.recordVote(1);
    election.recordVote(2);
    election.recordVote(1);

    if (election.endElection()) {
        cout << "Election ended!\n";
    }

    election.showResults();

    return 0;
}
