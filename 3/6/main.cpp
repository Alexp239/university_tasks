#include <iostream>

using namespace std;

class B {
    int x;
    int y;
public:
    B(int a, int b = 3) { x = a; y = b; }

    B& operator += (B & b)
    {
        x += b.x;
        y += b.y;
        return *this;
    }

    int get() { return x + y; }
};

