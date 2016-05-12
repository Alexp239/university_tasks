#include <iostream>
#include <map>
#include <algorithm>
#include <set>
#include <sstream>

using namespace std;

int nonterm(char c)
{
    return (c >= 'A' && c <= 'Z');
}

int main()
{
    map<char, set<string>> gram;
    map<char, int> is_null;
    set<char> nonterms;
    map<char, set<char>> first, follow;

    string s;
    while (getline(cin, s)) {
        char c;
        istringstream iss(s);
        s = "";
        iss >> c;
        iss >> s;
        nonterms.insert(c);
        gram[c].insert(s);
        if (s == "") {
            is_null[c] = 1;
        } else {
            is_null[c] = 0;
        }
    }

    /* NULLABLE */
    int is_changed = 1;
    while (is_changed) {
        is_changed = 0;
        for (auto p: nonterms) {
            if (!is_null[p]) {
                for (auto right: gram[p]) {
                    int null = 1;
                    for (auto i: right) {
                        if (!nonterm(i) || !is_null[i]) {
                            null = 0;
                            break;
                        }
                    }
                    if (null) {
                        is_null[p] = 1;
                        is_changed = 1;
                    }
                }
            }
        }
    }

    /* FIRST */
    for (auto p: nonterms) {
        for (auto right: gram[p]) {
            for (auto i: right) {
                first[p].insert(i);
                if (nonterm(i)) {
                    if (!is_null[i]) {
                        break;
                    }
                } else {
                    break;
                }
            }
        }
    }

    is_changed = 1;
    while (is_changed) {
        is_changed = 0;
        for (auto p: nonterms) {
            set<char> tmp = first[p];
            for (auto i: first[p]) {
                if (nonterm(i)) {
                    for (auto j: first[i]) {
                        if (!first[p].count(j)) {
                            tmp.insert(j);
                            is_changed = 1;
                        }
                    }
                }
            }
            first[p] = tmp;
        }
    }

    for (auto p: nonterms) {
        for (auto i: first[p]) {
            if (nonterm(i)) {
                first[p].erase(i);
            }
        }
    }

    /* FOLLOW */

    for (auto p: nonterms) {
        for (auto right: gram[p]) {
            for (unsigned i = 1; i < right.length(); i++) {
                if (nonterm(right[i - 1])) {
                    follow[right[i - 1]].insert(right[i]);
                }
            }
        }
    }

    is_changed = 1;
    while (is_changed) {
        is_changed = 0;
        for (auto p: nonterms) {
            set<char> tmp = follow[p];
            for (auto i: follow[p]) {
                if (nonterm(i)) {
                    for (auto j: first[i]) {
                        if (!follow[p].count(j)) {
                            is_changed = 1;
                            tmp.insert(j);
                        }
                    }
                }
            }
            follow[p] = tmp;
        }
        for (auto p: nonterms) {
            set<char> tmp = follow[p];
            for (auto i: follow[p]) {
                if (nonterm(i)) {
                    if (is_null[i]) {
                        for (auto j: follow[i]) {
                            if (!follow[p].count(j)) {
                                is_changed = 1;
                                tmp.insert(j);
                            }
                        }
                    }
                }
            }
            follow[p] = tmp;
        }
        map<char, set<char>> follow_tmp = follow;
        for (auto p: nonterms) {
            for (auto right: gram[p]) {
                if (right.length() > 0 && nonterm(right[right.length() - 1])) {
                    for (auto j: follow[p]) {
                        if (!follow[right[right.length() - 1]].count(j)) {
                            is_changed= 1;
                            follow_tmp[right[right.length() - 1]].insert(j);
                        }
                    }
                }
            }
        }
        follow = follow_tmp;
    }

    for (auto p: nonterms) {
        for (auto i: follow[p]) {
            if (nonterm(i)) {
                follow[p].erase(i);
            }
        }
    }

    for (auto p: nonterms) {
        cout << p << " " << is_null[p] << endl;
    }

    for (auto p: nonterms) {
        cout << p << " ";
        for (auto i: first[p]) {
            cout << i;
        }
        cout << endl;
    }
    for (auto p: nonterms) {
        cout << p << " ";
        for (auto i: follow[p]) {
            cout << i;
        }
        cout << endl;
    }
    return 0;
}
