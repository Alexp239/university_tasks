#include <iostream>

using namespace std;

struct K
{
    virtual void f(K *n)
    {
        st++;
        cout << "a" << endl;
    }
    static int st;
};

struct L: K
{
    virtual void f(L *a)
    {
        st++;
        cout << "b" << endl;
    }
};

int K::st = 2;

int main()
{
    L ob, ob2;
    K k, *p1 = &ob;
    p1->f(&ob2);
    k.st++;
    ++ob.st;
    cout << k.st << ' ' << ob.st << ' ' << K::st << endl;
    return 0;
}
