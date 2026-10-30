#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ofstream file("votes.txt", ios::app);

    if (!file.is_open()) {
        cerr << "Error: Unable to open storage file.\n";
        return 1;
    }

    int candidateID;

    cout << "Enter candidate ID: ";

    if (!(cin >> candidateID) || candidateID <= 0) {
        cerr << "Error: Invalid candidate ID.\n";
        file.close();
        return 1;
    }

    file << "Candidate ID: " << candidateID << '\n';

    if (!file) {
        cerr << "Error: Failed to save record.\n";
        return 1;
    }

    file.close();

    cout << "Record saved successfully.\n";
    return 0;
}
