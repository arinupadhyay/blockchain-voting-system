#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void readRecords(const string& filename) {
    ifstream file(filename);

    if (!file.is_open())
        throw runtime_error("Unable to open voter file");

    string line;

    while (getline(file, line)) {
        if (!line.empty())
            cout << line << '\n';
    }

    if (file.bad())
        throw runtime_error("Error while reading voter file");
}

int main() {
    try {
        readRecords("voters.txt");
    }
    catch (const exception& e) {
        cerr << "Storage error: " << e.what() << '\n';
    }

    return 0;
}
