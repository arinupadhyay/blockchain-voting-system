#include <iostream>
#include <vector>
#include <map>
using namespace std;

// Abstract Base Class
class User {
protected:
    int id;
    string password;

public:
    User(int i, string p) {
        id = i;
        password = p;
    }

    virtual bool login(string p) {
        return password == p;
    }

    virtual void displayRole() = 0;
};

// Derived Class
class Voter : public User {
private:
    bool hasVoted;
    bool authenticated;

public:
    Voter(int i, string p) : User(i, p) {
        hasVoted = false;
        authenticated = false;
    }

    bool login(string p) override {
        authenticated = User::login(p);
        return authenticated;
    }

    void displayRole() override {
        cout << "Role: Voter\n";
    }

    bool canVote() {
        return authenticated && !hasVoted;
    }

    void markVoted() {
        hasVoted = true;
    }

    int getID() {
        return id;
    }
};

// Election Class
class Election {
private:
    vector<string> candidates;
    map<string, int> results;

public:
    void addCandidate(string name) {
        candidates.push_back(name);
        results[name] = 0;
    }

    void castVote(Voter &v, string candidate) {
        if (!v.canVote()) {
            cout << "Voting not allowed!\n";
            return;
        }

        if (results.find(candidate) == results.end()) {
            cout << "Invalid candidate!\n";
            return;
        }

        results[candidate]++;
        v.markVoted();

        cout << "Vote cast successfully!\n";
    }

    void showResults() {
        cout << "\nElection Results\n";

        for (auto c : candidates) {
            cout << c << ": " << results[c] << " votes\n";
        }
    }
};

int main() {

    Voter v1(101, "abc123");

    Election election;

    election.addCandidate("Rahul");
    election.addCandidate("Aman");

    if (v1.login("abc123")) {
        cout << "Login Successful!\n";
    }

    v1.displayRole();

    election.castVote(v1, "Rahul");

    // Trying to vote again
    election.castVote(v1, "Aman");

    election.showResults();

    return 0;
}
