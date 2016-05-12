#include <iostream>

using namespace std;

int main()
{
    string left, right;
    int neuk = 1;
    int ks = 1;
    int fl = 0;
    int s = 0;
    int right_s = 0;
    int s_free = 0;
    while (cin >> left >> right) {
        fl = 1;
        int term = 0;
        for (unsigned i = 0; i < left.length(); i++) {
            if (left[i] >= 'A' && left[i] <= 'Z') {
                term = 1;
            }
        }
        for (unsigned i = 0; i < right.length(); i++) {
            if (right[i] == 'S') {
                right_s = 1;
            }
        }
        if (!term) {
            fl = 0;
            break;
        }
        if (left.length() == 1 && left[0] == 'S') {
            s = 1;
        }
        if (left.length() > right.length()) {
            neuk = 0;
        }
        if (right.length() == 1 && right[0] == '_') {
            if (left.length() > 1 || left[0] != 'S') {
                neuk = 0;
            } else if (left.length() == 1 && left[0] == 'S') {
                s_free = 1;
            }
        }
        if (left.length() > 1) {
            ks = 0;
        }
    }
    if (s_free && right_s) {
        neuk = 0;
    }
    if(!fl || !s) {
        cout << -1 << endl;
    } else if (ks && !neuk) {
        cout << 2 << endl;
    } else if (ks && neuk) {
        cout << 23 << endl;
    } else {
        cout << 10 << endl;
    }
    return 0;
}
