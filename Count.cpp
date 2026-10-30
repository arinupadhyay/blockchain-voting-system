
#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream file("votes.txt");

    if (!file) {
        cout << "Error: Votes file not found!";
        return 1;
    }

    string vote;
    int candidateA = 0;
    int candidateB = 0;

    while (getline(file, vote)) {
        if (vote == "Candidate 1")
            candidateA++;
        else if (vote == "Candidate 2")
            candidateB++;
    }

    file.close();

    cout << "\n===== Voting Results =====" << endl;
    cout << "Candidate A: " << candidateA << endl;
    cout << "Candidate B: " << candidateB << endl;

    if (candidateA > candidateB)
        cout << "Winner: Candidate A";
    else if (candidateB > candidateA)
        cout << "Winner: Candidate B";
    else
        cout << "Result: Tie";

    return 0;
}
