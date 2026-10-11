#include <iostream>
#include <fstream>
using namespace std;

struct Voter {
    int id;
    int age;
};

int main() {
    Voter v1 = {101, 20};

    // Serialize: write data to binary file
    ofstream out("voter.dat", ios::binary);

    if (!out) {
        cerr << "File creation failed.\n";
        return 1;
    }

    out.write(reinterpret_cast<const char*>(&v1),
              sizeof(v1));
    out.close();

    // Deserialize: read data from binary file
    Voter v2{};

    ifstream in("voter.dat", ios::binary);

    if (!in) {
        cerr << "File reading failed.\n";
        return 1;
    }

    in.read(reinterpret_cast<char*>(&v2),
            sizeof(v2));
    in.close();

    cout << "Voter ID: " << v2.id << '\n';
    cout << "Voter Age: " << v2.age << '\n';

    return 0;
}
