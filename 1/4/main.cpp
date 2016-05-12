#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main()
{
    double a, sm1 = 0, sm2 = 0;

    int cnt = 0;
    while (cin >> a) {
        cnt++;
        sm1 += a;
        sm2 += a * a;
    }
    double avg1 = sm1 / cnt;
    double avg2 = sm2 / cnt;
    cout << fixed << setprecision(10) << avg1 << ' ' << sqrt(avg2 - avg1 * avg1) << endl;

    return 0;
}
