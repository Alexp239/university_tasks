#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>

using namespace std;

template <class T, class Comp = less< typename T::value_type> >
void selection_sort( T first, T last, Comp comp = Comp() )
{
    if (first != last) {
        while (first != last - 1) {
            T min_it = first;
            for (T i = first + 1; i != last; i++) {
                if (comp(*i, *min_it)) {
                    swap(*i, *min_it);
                }
            }
            first++;
        }
    }
}
