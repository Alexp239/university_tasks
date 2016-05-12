#include <iostream>
#include <map>
#include <algorithm>
#include <set>

using namespace std;

int main()
{
    map<string, map<char, string>> dfa;
    auto dfa_p = dfa.begin();
    string first, second;
    char let;
    cin >> first;
    while (first != "END") {
        cin >> let >> second;
        if ((dfa_p = dfa.find(first)) != dfa.end()) {
            dfa_p->second[let] = second;
        } else {
            map<char, string> tmp;
            tmp[let] = second;
            dfa[first] = tmp;
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
    string cond;
    cin >> cond;
    string word;
    cin >> word;

    unsigned pos = 0;
    while (pos != word.length()) {
        if (dfa[cond].find(word[pos]) != dfa[cond].end()) {
            cond = dfa[cond][word[pos]];
            pos++;
        } else {
            cout << 0 << endl;
            cout << pos << endl;
            cout << cond << endl;
            return 0;
        }
    }
    if (last.find(cond) != last.end()) {
        cout << 1 << endl;
    } else {
        cout << 0 << endl;
    }
    cout << pos << endl;
    cout << cond << endl;
    return 0;
}
