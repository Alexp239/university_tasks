#include <iostream>
#include <sstream>


using namespace std;

class Result {
    int res;
public:
    Result(int n) {res = n;}
    int get_res() {return res;}
};

void Acc(int m, int n)
{
    try {
        if (m == 0) {
            throw Result(n + 1);
        } else if (m == 1) {
            throw Result(n + 2);
        } else if (m == 2) {
            throw Result(2 * n + 3);
        } else if (m > 0 && n == 0) {
            try {
                Acc(m - 1, 1);
            } catch (Result r) {
                throw;
            }
        } else {
            try {
                Acc(m, n - 1);
            } catch (Result r) {
                try {
                    Acc(m - 1, r.get_res());
                } catch (Result r) {
                    throw;
                }
            }
        }
    } catch (Result r) {
        throw;
    }
}

int main()
{
    int m, n;
    cin >> m >> n;
    try {
        Acc(m, n);
    } catch (Result r) {
        cout << r.get_res() << endl;
    }
    return 0;
}
