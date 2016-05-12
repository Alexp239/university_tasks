#include <iostream>
#include <vector>

using namespace std;

void process(const vector<int> & v1, vector<int> & v2)
{
    vector<int>::const_iterator pv1;
    vector<int>::iterator pv2, pv2_end;
    pv1 = v1.begin();
    pv2 = v2.begin();
    pv2_end = v2.end();
    int n = min(v1.size(), v2.size());
    int i = 0;
    while (i < n) {
        if (*(pv1 + i) > *(pv2 + i)) {
            v2.push_back(*(pv1 + i));
            pv2 = v2.begin();
        }
        i++;
    }
    pv2 = v2.begin();
    n = v2.size();
    i = 0;
    while (i < n) {
        cout << *(pv2 + i) << endl;
        i++;
    }
}
/*
int main()
{
    int q[] = {1, 2, 3};
    int w[] = {4, 5, 3};
    vector<int> v1(q, q + 3);
    vector<int> v2(w, w + 3);
    process(v2, v1);
    return 0;
}*/
