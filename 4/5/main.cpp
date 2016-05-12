#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

void process(vector<int> & v1, const vector<int> & v2, int k)
{
    vector<int>::const_iterator pv2;
    vector<int>::iterator pv1;
    pv1 = v1.begin();
    pv2 = v2.begin();

    int mx = v1.size();
    while (pv2 != v2.end()) {
        if (*pv2 <= mx && *pv2 >= 1) {
            *(pv1 + *pv2 - 1) *= k;
        }
        pv2++;
    }
    ostream_iterator<int> out (cout,"\n");
    copy(v1.begin(), v1.end(), out);
};
/*
int main()
{
    int q[] = {1, 2, 3};
    int w[] = {1, 1, 1};
    vector<int> v1(q, q + 3);
    vector<int> v2(w, w + 3);
    process(v1, v2, 2);
    return 0;
}
*/
