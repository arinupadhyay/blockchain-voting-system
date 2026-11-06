#include <iostream>
#include <string>
#include <openssl/sha.h>
#include <sstream>
#include <iomanip>
using namespace std;

class DataVerifier {
private:
    string data;

public:
    DataVerifier(string d) {
        data = d;
    }

    string generateHash() {
        unsigned char hash[SHA256_DIGEST_LENGTH];

        SHA256(
            (unsigned char*)data.c_str(),
            data.length(),
            hash
        );

        stringstream ss;

        for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
            ss << hex << setw(2) << setfill('0')
               << (int)hash[i];
        }

        return ss.str();
    }

    void verifyData(string originalHash) {
        if (generateHash() == originalHash) {
            cout << "Data is Authentic!\n";
        }
        else {
            cout << "Data has been Modified!\n";
        }
    }
};

int main() {
    DataVerifier voter("Voter ID: 101");

    string savedHash = voter.generateHash();

    cout << "Generated SHA-256 Hash:\n";
    cout << savedHash << endl;

    cout << "\nVerifying Data...\n";
    voter.verifyData(savedHash);

    return 0;
}
