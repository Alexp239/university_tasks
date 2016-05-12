/*
S -> 3S | 4S | 1A | 2A | _
A -> 1A | 2A | _
*/


#include <iostream>
#include <set>

using namespace std;

set<string> ans;

void A(int n, int k, string s)
{
    if (k == n) {
        int p;
        string s1;
        for (p = 0; p < int(s.length()); p++) {
            if (s[p] == '1' || s[p] == '2') {
                break;
            }
        }
        for (int i = 0; i < p; i++) {
            s1 += s[i];
        }
        for (int i = p - 1; i >= 0; i--) {
            s1 += s[i];
        }
        for (int i = p; i < int(s.length()); i++) {
            s1 += s[i];
        }
        for (int i = int(s.length()) - 1; i >= p; i--) {
            s1 += s[i];
        }
        ans.insert(s1);
    } else {
        A(n, k + 1, s + string("1"));
        A(n, k + 1, s + string("2"));
    }
}

void S(int n, int k, string s)
{
    if (k == n) {
        int p;
        string s1;
        for (p = 0; p < int(s.length()); p++) {
            if (s[p] == '1' || s[p] == '2') {
                break;
            }
        }
        for (int i = 0; i < p; i++) {
            s1 += s[i];
        }
        for (int i = p - 1; i >= 0; i--) {
            s1 += s[i];
        }
        for (int i = p; i < int(s.length()); i++) {
            s1 += s[i];
        }
        for (int i = int(s.length()) - 1; i >= p; i--) {
            s1 += s[i];
        }
        ans.insert(s1);
    } else {
        A(n, k + 1, s + string("1"));
        A(n, k + 1, s + string("2"));
        S(n, k + 1, s + string("3"));
        S(n, k + 1, s + string("4"));
    }
}

int main() {
    int k;
    string s("");
    cin >> k;

    S(k / 2, 0, s);
    for (auto str: ans) {
        cout << str << endl;
    }
    return 0;
}
