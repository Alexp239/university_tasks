#include <iostream>
#include <string>
#include "iomanip"

using namespace std;

int main()
{
    string s;
    char c;
    cin.unsetf(ios::skipws);
    while (cin >> c) {
        s += c;
    }
    if (!s.length()) {
        return 0;
    }
    int count = 1;
    c = s[0];
    for (unsigned int i = 1; i < s.length(); i++) {
        if (s[i] == s[i - 1]) {
            count++;
        } else {
            if (c == '#') {
                cout << '#' << c << hex << count << '#';
            } else if (count <= 4) {
                for (int j = 0; j < count; j++) {
                    cout << c;
                }
            } else {
                cout << '#' << c << hex << count << '#';
            }
            c = s[i];
            count = 1;
        }
    }
    if (count > 0) {
        if (c == '#') {
            cout << '#' << c << hex << count << '#';
        } else if (count <= 4) {
            for (int j = 0; j < count; j++) {
                cout << c;
            }
        } else {
            cout << '#' << c << hex << count << '#';
        }
    }

    return 0;
}
