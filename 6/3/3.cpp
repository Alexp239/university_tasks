#include <iostream>
#include <math.h>
#include <string>
#include <algorithm>
#include <sstream>
#include <vector>
#include <stdio.h>

using namespace std;

class A {
    int n;
public:
    A(int a) {n = a;}
    ~A() {cout << n << endl;}
};

void f() {
    int k;
    if (cin >> k) {
        A a(k);
        try {
            f();
        } catch (int) {
            return;
        }
    } else {
        throw k;
    }
}

int main()
{
    try {
        f();
    } catch (int) {
        return 0;
    }
    return 0;
}
