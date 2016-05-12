#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
    string s;
    while (cin >> s) {
        while (1) {
            string s1 = s;
            reverse(s1.begin(), s1.end());
            if (s == s1) {
                cout << s << endl;
                break;
            } else {
                s.resize(s.size() - 1);
            }
        }
    }
    return 0;
}
