#include <iostream>
#include <vector>

using namespace std;

void process(vector <int> &v) {
    vector<int>::iterator it = v.begin();
    while (it != v.end()) {
        it = v.erase(it);
        if (it == v.end()) {
            break;
        }
        it++;
    }
    vector <int>::reverse_iterator it2 = v.rbegin();
    while (it2 != v.rend()) {
        cout << *it2++ << endl;
    }
}
