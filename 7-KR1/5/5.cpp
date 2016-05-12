#include <iostream>
#include <map>

using namespace std;

int main()
{
    string s;
    int k;
    map <string, int> sum;
    map <string, int> cnt;

    sum.clear();
    cnt.clear();
    while (cin >> s >> k) {
        sum[s] += k;
        cnt[s] += 1;
    }

    for (map <string, int>::iterator it = sum.begin(); it != sum.end(); it++) {
        cout << it -> first << ' ' << (double) sum[it -> first] / cnt[it -> first] << endl;
    }
    return 0;
}
