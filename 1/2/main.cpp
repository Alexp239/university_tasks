#include <iostream>

using namespace std;

class Sum {
    int a, b;
public:
    Sum(int p, int q) { a = p; b = q; }
    int get() { return a + b; }
};

