#include <iostream>
using namespace std;

// Function to display the current election status
void displayStatus(int status) {

    if (status == 0) {
        cout << "Election Status : NOT STARTED" << endl;
    }
    else if (status == 1) {
        cout << "Election Status : ONGOING" << endl;
    }
    else if (status == 2) {
        cout << "Election Status : ENDED" << endl;
    }
    else {
        cout << "Election Status : INVALID" << endl;
    }
}

int main() {

    string electionID = "E001";
    string electionName = "Student Council Election 2026";

    // 0 = NOT_STARTED
    // 1 = ONGOING
    // 2 = ENDED
    int status = 0;

    cout << "========================================" << endl;
    cout << "        ELECTION MANAGEMENT SYSTEM      " << endl;
    cout << "========================================" << endl;

    cout << endl;

    cout << "Election ID   : " << electionID << endl;
    cout << "Election Name : " << electionName << endl;

    cout << endl;

    displayStatus(status);

    cout << endl;

    // Start the election
    if (status == 0) {
        cout << "Starting election..." << endl;
        status = 1;
    }

    displayStatus(status);

    cout << endl;

    // End the election
    if (status == 1) {
        cout << "Ending election..." << endl;
        status = 2;
    }

    displayStatus(status);

    cout << endl;

    cout << "========================================" << endl;
    cout << "          Election Process Complete     " << endl;
    cout << "========================================" << endl;

    return 0;
}