#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

struct VoterRecord {
    string id;
    string name;
    int age;
};

void validateRecord(const VoterRecord& voter) {
    if (voter.id.empty())
        throw invalid_argument("Voter ID cannot be empty");

    if (voter.name.empty())
        throw invalid_argument("Voter name cannot be empty");

    if (voter.age < 18 || voter.age > 120)
        throw out_of_range("Invalid voter age");
}

int main() {
    VoterRecord voter = {"V101", "Rahul", 20};

    try {
        validateRecord(voter);
        cout << "Voter record is valid.\n";
    }
    catch (const exception& e) {
        cerr << "Validation error: " << e.what() << '\n';
    }

    return 0;
}
