#include <iostream>
#include <algorithm>
#include <vector>
#include <list>

using namespace std;

void process(const vector<int> &v2, list<int> &lst)
{
    vector<int> v = v2;
    sort(v.begin(), v.end());
    vector<int>::iterator last = unique(v.begin(), v.end());
    v.erase(last, v.end());
    vector<int>::iterator pv = v.begin();
    while ((pv != v.end()) && (*pv < 1)) {
        pv++;
    }
    pv = v.erase(v.begin(), pv);
    while ((pv != v.end()) && (*pv <= (int)lst.size())){
        pv++;
    }

    pv = v.erase(pv, v.end());

    list<int>::iterator pl = lst.begin();
    int prev = 0;

    pv = v.begin();
    while (pv != v.end()) {
        for (int i = 0; i < *pv - prev - 1; i++){
            pl++;
        }
        pl = lst.erase(pl);
        prev = *pv++;
    }
}
/*
int main()
{
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int b[] = {1, 5, 10, 1, 1000, 10};
    vector<int> v2(b, b + 6);
    list<int> l(a, a + 10);
    process(v2, l);
    list<int>::iterator p = l.begin();
    while (p != l.end()) {
        cout << *p << ' ';
        p++;
    }
    cout << endl;
    return 0;
}*/
