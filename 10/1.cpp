#include <iostream>

using namespace std;

void f(int len, int cur, char *s)
{
    if (cur == len) {
        for (int i = 0; i < len; i++) {
            cout << s[i];
        }
        cout << endl;
        return;
    }
    if (cur == 0 || s[cur - 1] == '3' || s[cur - 1] == '4') {
        s[cur] = '1';
        f(len, cur + 1, s);
        s[cur] = '2';
        f(len, cur + 1, s);
        s[cur] = '3';
        f(len, cur + 1, s);
        s[cur] = '4';
        f(len, cur + 1, s);
    } else {
        s[cur] = '1';
        f(len, cur + 1, s);
        s[cur] = '2';
        f(len, cur + 1, s);
    }
}

int main()
{
    int k;
    cin >> k;
    char *s = new char[k];
    for (int i = 0; i < k; i++) {
        s[i] = '3';
    }
    f(k, 0, s);
    delete s;
    return 0;
}
