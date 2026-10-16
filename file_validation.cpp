#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool fileExists(const string& filename) {
    ifstream file(filename);
    return file.good();
}

int main() {
    string filename = "voters.txt";

    if (fileExists(filename))
        cout << "Voter file exists.\n";
    else
        cout << "Voter file does not exist.\n";

    return 0;
}
