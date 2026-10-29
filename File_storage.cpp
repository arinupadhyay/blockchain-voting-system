#include <iostream>
#include <fstream>
using namespace std;

int main() {
    int candidate;

    cout << "===== Voting System =====" << endl;
    cout << "1. Candidate A" << endl;
    cout << "2. Candidate B" << endl;
    cout << "Enter your vote: ";

    if (!(cin >> candidate)) {
        cout << "Error: Invalid input!" << endl;
        return 1;
    }

    if (candidate != 1 && candidate != 2) {
        cout << "Error: Invalid candidate!" << endl;
        return 1;
    }

    ofstream file("votes.txt", ios::app);

    if (!file) {
        cout << "Error: Unable to open file!" << endl;
        return 1;
    }

    file << "Candidate " << candidate << endl;
    file.close();

    cout << "Vote saved successfully!" << endl;

    return 0;
}
