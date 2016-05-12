#include <iostream>
#include <vector>

using namespace std;

int term(char c)
{
    return (c >= 'A' && c <= 'Z');
}

int main()
{
    string left, right;
    int nonterm[26];
    for (int i = 0; i < 26; i++) {
        nonterm[i] = 0;
    }
    nonterm['S' - 'A'] = 1;
    int fl = 0;
    vector<pair<string, string>> gram;
    while (cin >> left >> right) {
        if (left[0] == 'S') {
            for (unsigned i = 0; i < right.size(); i++) {
                if (term(right[i])) {
                    if (!nonterm[right[i] - 'A']) {
                        fl = 1;
                        nonterm[right[i] - 'A'] = 1;
                    }
                }
            }
        }
        gram.push_back(pair<string, string>(left, right));
    }

    while (fl) {
        fl = 0;
        for (auto p = gram.begin(); p != gram.end(); p++) {
            if (nonterm[p->first[0] - 'A']) {
                for (unsigned i = 0; i < p->second.size(); i++) {
                    if (term(p->second[i])) {
                        if (!nonterm[p->second[i] - 'A']) {
                            fl = 1;
                            nonterm[p->second[i] - 'A'] = 1;
                        }
                    }
                }
            }
        }
    }

    for (auto p = gram.begin(); p != gram.end(); p++) {
        if (nonterm[p->first[0] - 'A']) {
            cout << p->first << " " << p->second << endl;
        }
    }
    return 0;
}
