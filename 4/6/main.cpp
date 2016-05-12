#include <iostream>

using namespace std;

template <typename T>
void myreverse(T p_begin, T p_end)
{
    T p_tmp = p_begin;
    int count = 0;
    while (p_tmp++ != p_end) {
        count++;
    }
    p_end--;
    for (int i = 0; i < count / 2; i++) {
        swap(*p_begin++, *p_end--);
    }
}
