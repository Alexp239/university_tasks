#include <iostream>

using namespace std;

int nonterm(char c) {
    return (c >= 'A' && c <= 'Z');
}

int main()
{
    string left, right;
    int neuk = 1;
    int right_avt = 1;
    int left_avt = 1;
    int right_reg = 1;
    int left_reg = 1;
    int right_s = 0;
    int s_free = 0;
    int s_nonterm = 0;

    while (cin >> left >> right) {

        for (unsigned i = 0; i < right.length(); i++) {
            if (right[i] == 'S') {
                right_s = 1;
            }
        }

        if (right.length() == 1 && right[0] == '_') {
            if (left[0] != 'S') {
                neuk = 0;
                left_avt = 0;
                right_avt = 0;
            } else {
                s_free = 1;
            }
        }
        if (right.length() > 1) {
            int count_nonterm = 0;
            int count_term = 0;
            for (unsigned i = 0; i < right.length(); i++) {
                if (nonterm(right[i])) {
                    count_nonterm++;
                } else {
                    count_term++;
                }
            }
            if (count_nonterm > 1) {
                right_reg = 0;
                right_avt = 0;
                left_reg = 0;
                left_avt = 0;
            }
            if (count_term != 1) {
                right_avt = 0;
                left_avt = 0;
            }
            for (unsigned i = 0; i < right.length(); i++) {
                if (nonterm(right[i])) {
                    if (i == 0) {
                        right_reg = 0;
                        right_avt = 0;
                    } else if (i == right.length() - 1) {
                        left_avt = 0;
                        left_reg = 0;
                    } else {
                        right_reg = 0;
                        right_avt = 0;
                        left_reg = 0;
                        left_avt = 0;
                    }
                }
            }
        } else if (nonterm(right[0])) {
            if (left[0] == 'S') {
                s_nonterm = 1;
            } else {
                left_avt = 0;
                right_avt = 0;
            }
        }
    }
    if (s_free && right_s) {
        neuk = 0;
        left_avt = 0;
        right_avt = 0;
    }
    if (s_nonterm && right_s) {
        left_avt = 0;
        right_avt = 0;
    }
    if (!left_reg && !right_reg && neuk) {
        cout << 21 << endl;
    } else if (left_reg && !left_avt) {
        cout << 31 << endl;
    } else if (right_reg && !right_avt) {
        cout << 32 << endl;
    } else if (left_avt) {
        cout << 311 << endl;
    } else if (right_avt) {
        cout << 321 << endl;
    } else {
        cout << 2 << endl;
    }
    return 0;
}
