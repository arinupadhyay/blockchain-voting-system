#include <iostream>
#include <string>
#include <functional>
using namespace std;

class Block {
public:
    int index;
    string data;
    string previousHash;
    string currentHash;

    Block(int i, string d, string prev) {
        index = i;
        data = d;
        previousHash = prev;
        currentHash = calculateHash();
    }

    string calculateHash() {
        string input = to_string(index) + data + previousHash;

        return to_string(hash<string>{}(input));
    }

    void display() {
        cout << "\nBlock Index: " << index;
        cout << "\nData: " << data;
        cout << "\nPrevious Hash: " << previousHash;
        cout << "\nCurrent Hash: " << currentHash << "\n";
    }
};

int main() {
    Block b1(0, "Genesis Block", "0");

    Block b2(1, "Vote: Rahul", b1.currentHash);

    Block b3(2, "Vote: Aman", b2.currentHash);

    b1.display();
    b2.display();
    b3.display();

    return 0;
}