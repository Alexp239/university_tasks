#include <iostream>

using namespace std;

class C{
    int a;
public:
    C(int x = 0) { a = x; }
    C(const C &x) { a = x.a; }

    int get()
    {
        return 2 * a;
    }

    C operator +(const C &b)
    {
        return C(2 * a + 2 * b.a);
    }
};
