#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

void logError(const string& message) {
    ofstream file("error.log", ios::app);

    if (!file)
        throw runtime_error("Cannot open error log");

    time_t now = time(nullptr);

    file << ctime(&now)
         << "Error: " << message << '\n';

    file.close();
}

int main() {
    try {
        logError("Voter record could not be processed.");
        cout << "Error logged successfully.\n";
    }
    catch (const exception& e) {
        cerr << e.what() << '\n';
        return 1;
    }

    return 0;
}
