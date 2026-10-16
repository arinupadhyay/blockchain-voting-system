
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
using namespace std;

void saveRecord(const string& filename,
                const string& record) {
    ofstream file(filename, ios::app);

    if (!file.is_open())
        throw runtime_error("Unable to open file");

    file << record << '\n';

    if (!file)
        throw runtime_error("Failed to write record");

    file.close();

    cout << "Record saved successfully.\n";
}

int main() {
    try {
        saveRecord("voters.txt", "V104 Amit 21");
    }
    catch (const exception& e) {
        cerr << "Storage error: "
             << e.what() << '\n';
        return 1;
    }

    return 0;
}
