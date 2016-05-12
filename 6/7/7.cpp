#include <iostream>

using namespace std;

template <typename value_type>
class Coord {
public:
    value_type row;
    value_type col;
    Coord(value_type a = value_type(), value_type b = value_type()) {
        row = a;
        col = b;
    }
};

template <class T>
T dist(Coord<T> field, Coord<T> first, Coord<T> second)
{
    T ans_x = min(abs(first.row - second.row), -abs(first.row - second.row) + field.row);
    T ans_y = min(abs(first.col - second.col), -abs(first.col - second.col) + field.col);
    return max(ans_x, ans_y);
}

/*
int main()
{
    Coord<int> fd(2, 3), f(0, 0), s(1, 2);
    dist<int>(fd, f, s);
    return 0;
}
*/
