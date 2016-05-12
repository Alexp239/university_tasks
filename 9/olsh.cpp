#include <iostream>
#include <vector>

using namespace std;

bool check(string s)
{
    string low;

    for (auto c: s) {
        low += char(tolower(c));
    }
    return low == s;
}

int check(vector <pair <string, string> > &gr, char start)
{
    bool s_isright = false;
    bool bad_empty = false;
    bool empty = false;
    bool isright = true;
    bool isauto = true;
    bool isautoexcept = true;
    bool isleft = true;

    for (auto x: gr)  {
        string left = x.first, right = x.second;

        if (right.find(start) != string::npos) {
            s_isright = true;
        }
        string s = right;

        if (!check(s.substr(0, s.size() - 1))) {
            isright = false;
        }

        if (!check(s.substr(1))) {
            isleft = false;
        }

        if (s.size() > 2 || (s.size() == 1 && tolower(s[0]) != s[0]) ||
        (s.size() == 2 && (s[0] == tolower(s[0])) == (s[1] == tolower(s[1])))) {
            isauto = false;

            if (left[0] != start || right.size() != 1 || tolower(right[0]) == right[0]) {
                isautoexcept = false;
            } else {
                vector <pair <string, string> > nxt;

                for (auto elem: gr) {
                    if (elem.first[0] != start) {
                        nxt.push_back(elem);
                    }
                }

                if (check(nxt, right[0]) < 100) {
                    isautoexcept = false;
                }
            }
        }

        if (right == "_" && left[0] != start) {
            bad_empty = true;
        }

        if (right == "_") {
            empty = true;
        }
    }
    isauto = isauto || (isautoexcept && !s_isright);

    if (!empty || (!bad_empty && !s_isright)) {
        if (isleft) {
            if (isauto) {
                return 311;
            } else {
                return 31;
            }
        }
        if (isright) {
            if (isauto) {
                return 321;
            } else {
                return 32;
            }
        }
        return 21;
    } else {
        return 2;
    }
}

int main()
{
    vector <pair <string, string> > gr;
    string left, right;

    while (cin >> left >> right) {
        gr.push_back(make_pair(left, right));
    }
    cout << check(gr, 'S') << '\n';
    return 0;
}
