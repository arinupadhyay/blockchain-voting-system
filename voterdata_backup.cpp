#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool backupFile(const string& source,
                const string& destination) {
    ifstream in(source, ios::binary);

    if (!in)
        return false;

    ofstream out(destination, ios::binary);

    if (!out)
        return false;

    out << in.rdbuf();

    return in.good() == false &&
           out.good();
}

int main() {
    if (backupFile("voters.txt", "voters_backup.txt"))
        cout << "Backup created successfully.\n";
    else
        cout << "Backup failed.\n";

    return 0;
}
