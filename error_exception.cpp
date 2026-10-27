#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
using namespace std;

// Base exception class
class VotingException : public runtime_error {
public:
    explicit VotingException(const string& msg)
        : runtime_error(msg) {}
};

// Derived exception class
class InvalidVoterException : public VotingException {
public:
    InvalidVoterException()
        : VotingException("Invalid voter ID") {}
};

// File manager for voter records
class FileManager {
public:
    static void saveVoter(const string& id,
                          const string& name) {
        ofstream file("voters.txt", ios::app);

        if (!file)
            throw runtime_error("Unable to open file");

        file << id << " " << name << '\n';
        file.close();

        cout << "Voter record saved successfully.\n";
    }

    static void displayVoters() {
        ifstream file("voters.txt");

        if (!file)
            throw runtime_error("Unable to read file");

        string id, name;

        cout << "\nStored Voter Records:\n";
        while (file >> id >> name)
            cout << "ID: " << id
                 << ", Name: " << name << '\n';

        file.close();
    }
};

int main() {
    try {
        string id, name;

        cout << "Enter voter ID: ";
        cin >> id;

        cout << "Enter voter name (one word): ";
        cin >> name;

        if (id.empty())
            throw InvalidVoterException();

        FileManager::saveVoter(id, name);
        FileManager::displayVoters();
    }
    catch (const VotingException& e) {
        cerr << "Voting error: " << e.what() << '\n';
    }
    catch (const exception& e) {
        cerr << "System error: " << e.what() << '\n';
    }

    return 0;
}
