#include <iostream>
#include <map>
#include <algorithm>
#include <set>

using namespace std;

int main()
{
    map<string, map<char, set<string>>> nfa;
    auto nfa_p = nfa.begin();
    string first, second;
    string let_s;
    char let;
    cin >> first;
    while (first != "END") {
        cin >> let_s >> second;
        if ((let_s) == "eps") {
            let = ' ';
        } else {
            let = let_s[0];
        }
        if ((nfa_p = nfa.find(first)) != nfa.end()) {
            nfa_p->second[let].insert(second);
        } else {
            map<char, set<string>> tmp_m;
            set<string> tmp_s;
            tmp_s.insert(second);
            tmp_m[let] = tmp_s;
            nfa[first] = tmp_m;
        }
        cin >> first;
    }
    set<string> last;
    string s;
    cin >> s;
    while (s != "END") {
        last.insert(s);
        cin >> s;
    }
    set<string> cur_cond, next_cond;
    string cond;
    cin >> cond;
    next_cond.insert(cond);
    string word;
    cin >> word;

    unsigned pos = 0;
    int new_cond;
    while (pos != word.length()) {
        new_cond = 1;
        cur_cond.clear();
        while (new_cond) {
            new_cond = 0;
            for (auto p : next_cond) {
                if (nfa[p].count(' ')) {
                    for (auto eps_cond : nfa[p][' ']) {
                        if (!next_cond.count(eps_cond)) {
                            new_cond = 1;
                            cur_cond.insert(eps_cond);
                        }
                    }
                }
            }
            for (auto p : cur_cond) {
                next_cond.insert(p);
            }
            cur_cond.clear();
        }
        for (auto p : next_cond) {
            cur_cond.insert(p);
        }
        next_cond.clear();

        int fl = 0;
        for (auto p : cur_cond) {
            if (nfa[p].count(word[pos])) {
                fl = 1;
                for (auto con : nfa[p][word[pos]]) {
                    next_cond.insert(con);
                }
            }
        }
        if (fl) {
            pos++;
        } else {
            cout << 0 << endl;
            cout << pos << endl;
            return 0;
        }
    }
    new_cond = 1;
    cur_cond.clear();
    while (new_cond) {
        new_cond = 0;
        for (auto p : next_cond) {
            if (nfa[p].count(' ')) {
                for (auto eps_cond : nfa[p][' ']) {
                    if (!next_cond.count(eps_cond)) {
                        new_cond = 1;
                        cur_cond.insert(eps_cond);
                    }
                }
            }
        }
        for (auto p : cur_cond) {
            next_cond.insert(p);
        }
        cur_cond.clear();
    }
    for (auto p : next_cond) {
        cur_cond.insert(p);
    }

    int fl = 0;

    for (auto p : cur_cond) {
        if (last.count(p)) {
            fl = 1;
        }
    }
    cout << fl << endl;
    cout << pos << endl;
    return 0;
}
