#include <iostream>
#include <string>
#include <functional>
using namespace std;

class Voter {
private:
    int voterID;
    string name;
    string password;

public:
    Voter(int id, string n, string p) {
        voterID = id;
        name = n;
        password = p;
    }

    size_t generateHash() {
        string data = to_string(voterID) + name + password;

        hash<string> hashFunction;

        return hashFunction(data);
    }

    void displayDetails() {
        cout << "\nVoter Details\n";
        cout << "ID: " << voterID << endl;
        cout << "Name: " << name << endl;
        cout << "Generated Hash: " << generateHash() << endl;
    }

    bool verifyHash(size_t oldHash) {
        return generateHash() == oldHash;
    }
};

int main() {
    Voter v1(101, "Rahul", "abc123");

    v1.displayDetails();

    size_t savedHash = v1.generateHash();

    cout << "\nVerifying Voter Data...\n";

    if (v1.verifyHash(savedHash)) {
        cout << "Voter Data Verified Successfully!";
    }
    else {
        cout << "Voter Data Verification Failed!";
    }

    return 0;
}
