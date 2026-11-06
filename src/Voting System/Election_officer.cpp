#include <iostream>
#include <vector>
using namespace std;

// Abstract Base Class
class Person {
protected:
    string name;
    int id;

public:
    Person(string n, int i) {
        name = n;
        id = i;
    }

    virtual void display() = 0;
};

// Voter Class
class Voter : public Person {
private:
    bool voted;

public:
    Voter(string n, int i) : Person(n, i) {
        voted = false;
    }

    void castVote() {
        if (!voted) {
            voted = true;
            cout << name << " voted successfully!\n";
        }
        else {
            cout << name << " has already voted!\n";
        }
    }

    void display() override {
        cout << "Voter: " << name
             << " | ID: " << id << endl;
    }
};

// Election Officer Class
class Officer : public Person {
public:
    Officer(string n, int i) : Person(n, i) {}

    void display() override {
        cout << "Officer: " << name
             << " | ID: " << id << endl;
    }

    void manageElection() {
        cout << "Officer is managing the election.\n";
    }
};

int main() {

    Voter v1("Rahul", 101);
    Officer o1("Amit", 201);

    Person* p;

    p = &v1;
    p->display();

    p = &o1;
    p->display();

    o1.manageElection();

    v1.castVote();
    v1.castVote();

    return 0;
}
