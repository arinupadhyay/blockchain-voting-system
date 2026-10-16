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
    map<int, string> candidates;

public:
    Election(int id, const string& name)
        : electionId(id),
          electionName(name),
          status(ElectionStatus::NOT_STARTED) {}

    bool addCandidate(int id, const string& name) {
        if (status != ElectionStatus::NOT_STARTED ||
            candidates.count(id) > 0) {
            return false;
        }

        candidates[id] = name;
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

    bool endElection() {
        if (status != ElectionStatus::ONGOING) {
            return false;
        }

        status = ElectionStatus::ENDED;
        return true;
    }

    void showElection() const {
        cout << "Election ID: " << electionId << '\n';
        cout << "Election Name: " << electionName << '\n';

        cout << "Status: ";
        switch (status) {
            case ElectionStatus::NOT_STARTED:
                cout << "NOT_STARTED";
                break;
            case ElectionStatus::ONGOING:
                cout << "ONGOING";
                break;
            case ElectionStatus::ENDED:
                cout << "ENDED";
                break;
        }

        cout << "\nCandidates:\n";
        for (const auto& candidate : candidates) {
            cout << candidate.first << " - "
                 << candidate.second << '\n';
        }
    }
};

int main() {
    Election election(101, "College Election");

    election.addCandidate(1, "Sunny");
    election.addCandidate(2, "Arin");

    if (election.startElection()) {
        cout << "Election started successfully!\n";
    }

    election.showElection();

    if (election.endElection()) {
        cout << "\nElection ended successfully!\n";
    }

    election.showElection();

    return 0;
}