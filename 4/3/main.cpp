#include <iostream>

using namespace std;

template <class T>

typename T::value_type process(const T &a)
{
    typename T::value_type s = typename T::value_type();
    typename T::const_iterator p = a.end();
    if (!a.size()) {
        return s;
    } else if (a.size() == 1) {
        p--;
        return *p;
    } else if (a.size() == 2) {
        p--;
        s = *p;
        p--;
        s += *p;
        return s;
    } else {
        p = a.end();
        p--;
        s = *p;
        p--;
        s += *p;
        p--;
        s += *p;
        return s;
    }
}
/*
int main()
{

    return 0;
}
*/
