#include <iostream>
#include <fstream>
#include <limits>

using namespace std;

int main()
{
    ifstream fin("tests/008.dat");
    int a, b, c, d;
    fin >> a;
    cout << a << endl;
    //fin >> a >> b >> c >> d;
    //cout << a << " " << b << " " << c << " " << d << endl;
    /*int INT_MIN = std::numeric_limits<int>::lowest();
    int INT_MAX = std::numeric_limits<int>::max();
    cout << INT_MIN << " " << INT_MAX << endl;*/
    fin.close();
    return 0;
}
