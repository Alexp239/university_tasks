#include <iostream>
#include <string>

using namespace std;

class BinaryNumber
{
    string numb;
public:
    BinaryNumber(const string &s) { numb = s; }
    operator string () const { return numb; }
    const BinaryNumber &operator++()
    {
        int i = numb.size() - 1;
        while (i >= 0 && numb[i] == '1') {
            i--;
        }
        if (i < 0) {
            numb.resize(numb.size() + 1);
            numb[0] = '1';
            for (i = 1; i < int(numb.size()); i++) {
                numb[i] = '0';
            }
        } else {
            numb[i] = '1';
            i++;
            while (i != int(numb.size())) {
                numb[i] = '0';
                i++;
            }
        }
        return *this;
    }
};
