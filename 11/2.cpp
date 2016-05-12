#include <iostream>

using namespace std;
/*
S -> 1A0
A -> 1A0 | 0B1
B -> 0B1 | _
*/

char c;

int gc() {
    cin >> c;
    if (cin.fail()) {
        return 0;
    }
    return 1;
}

void B()
{
    if (c == '0') {
        gc();
        cout << '1';
        B();
        cout << '0';
        gc();
    }
}

void A()
{
    if (c == '1') {
        gc();
        A();
        cout << '0';
        gc();
    } else if (c == '0') {
        gc();
        cout << '1';
        B();
        cout << '0';
        gc();
    }
}

void S()
{
    if (c == '1') {
        gc();
        A();
        cout << '0' << endl;
    }
}

int main() {
    while (gc()) {
        S();
    }
    return 0;
}
