#include <iostream>
#include <string>
#include <map>
using namespace std;

class VoterSystem {
private:
    map<int, string> voters;

public:
    void registerVoter(int id, string password) {
        if (voters.find(id) != voters.end()) {
            cout << "Voter already registered!\n";
            return;
        }

        voters[id] = password;
        cout << "Registration successful!\n";
    }

    void login(int id, string password) {
        if (voters.find(id) != voters.end() &&
            voters[id] == password) {
            cout << "Login successful!\n";
        } else {
            cout << "Invalid ID or password!\n";
        }
    }
};

int main() {
    VoterSystem system;

    system.registerVoter(101, "abc123");
    system.login(101, "abc123");
    system.login(102, "xyz123");

    return 0;
}
