#include <iostream>
#include <sstream>


using namespace std;

int main()
{
    int m, n, r1, c1, r2, c2;
    cin >> m >> n;
    while (cin >> r1 >> c1 >> r2 >> c2) {
        int ans_x, ans_y;
        ans_x = min(max(r1, r2) - min(r1, r2), -max(r1, r2) + min(r1, r2) + n);
        ans_y = min(max(c1, c2) - min(c1, c2), -max(c1, c2) + min(c1, c2) + m);
        cout << ans_x + ans_y << endl;
    }
    return 0;
}
