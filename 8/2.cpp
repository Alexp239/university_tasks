#include <iostream>
#include <string>

using namespace std;

int main()
{
    string s;
    while (cin >> s) {
        int fl = 0, ans = 1;
        for (unsigned i = 0; i < s.length(); i++) {
            if (s[i] == '3' || s[i] == '4') {
                if (fl) {
                    ans = 0;
                    break;
                }
            } else if (s[i] == '1' || s[i] == '2') {
                fl = 1;
            } else {
                ans = 0;
                break;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
