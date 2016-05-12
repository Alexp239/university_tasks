/*
S -> aAd
A -> aAd | bBc
B -> bBc | _
*/


#include <iostream>

using namespace std;

int k;

void B(int len)
{
    if (len == k / 2) {
        return;
    } else {
        cout << 'b';
        B(len + 1);
        cout << 'c';
    }
}

void print_d(int len) {
    if (len != 0) {
        cout << 'd';
        print_d(len - 1);
    }
}

void print_a(int len) {
    if (len != 0) {
        cout << 'a';
        print_a(len - 1);
    }
}

void A(int len)
{
    if (len == k / 2) {
        print_d(len);
        cout << endl;
    } else if (len != k / 2 - 1){
        cout << 'a';
        A(len + 1);

        print_a(len);
        cout << 'b';
        B(len + 1);
        cout << 'c';
        print_d(len);
        cout << endl;
    } else {
        cout << "bc";
        print_d(len);
        cout << endl;
    }
}

void S(int len)
{
    cout << 'a';
    A(len + 1);
}

int main()
{
    cin >> k;

    if (k < 4 || k % 2 != 0) {
        return 0;
    }

    S(0);

    return 0;
}
