#include <iostream>
#include <vector>
#include <list>

using namespace std;

void process(const vector<int> & v, list <int> & lst, unsigned step)
{
    vector<int>::const_iterator pv;
    list<int>::iterator pl;

    pv = v.begin();
    pl = lst.begin();

    while ((pl != lst.end()) && (pv < v.end())) {
        *pl++ = *pv;
        pv += step;
    }

    pl = lst.end();
    if (lst.end() == lst.begin())
        return;
    pl--;
    while (pl != lst.begin()) {
        cout << *pl << ' ';
        pl--;
    }
    cout << *pl << endl;
}

