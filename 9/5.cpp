#include <iostream>
#include <vector>
#include <iomanip>
#include <set>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

template<class It, class T>
It my_find (It first, It last, const T& val, int &fl, int &count)
{
    count = 0;
    while (first != last) {
        if (*first >= val) {
            if (*first == val) {
                fl = 1;
            }
            return first;
        }
        ++first;
        ++count;
    }
    return last;
}


class Date {
    int day;
    int month;
    int year;
public:
    Date(int d = 0, int m = 0, int y = 0): day(d), month(m), year(y) {}

    friend ostream &operator << (ostream &o, Date &d) {
        o << d.year << '/' << setfill('0') << setw(2);
        o << d.month << '/' << setfill('0') << setw(2) << d.day;
        return o;
    }

    friend istream &operator >> (istream &i, Date &d) {
        char c;
        i >> d.year >> c >> d.month >> c >> d.day;
        return i;
    }

    friend int operator < (const Date &d1, const Date &d2) {
        if (d1.year == d2.year) {
            if (d1.month == d2.month) {
                if (d1.day == d2.day) {
                    return 0;
                } else {
                    return d1.day < d2.day;
                }
            } else {
                return d1.month < d2.month;
            }
        } else {
            return d1.year < d2.year;
        }
    }

    friend int operator ==(const Date &d1, const Date &d2) {
        return (d2.day == d1.day && d2.month == d1.month && d2.year == d1.year);
    }
};

int main() {
    set<string> names;
    set<Date> dates;
    map<pair<string, Date>, int> marks;

    string name;
    Date date;
    int mark;
    while (cin >> name >> date >> mark) {
        names.insert(name);
        dates.insert(date);
        marks[pair<string, Date>(name, date)]=mark;
    }
    cout << ". ";
    for (auto i = dates.begin(); i != dates.end(); i++) {
        Date tmp = *i;
        cout << tmp << " ";
    }
    cout << endl;
    for (auto i = names.begin(); i != names.end(); i++) {
        cout << *i << " ";
        for (auto j = dates.begin(); j != dates.end(); j++) {
            auto p = marks.find(pair<string, Date>(*i, *j));
            if (p != marks.end()) {
                cout << p->second << " ";
            } else {
                cout << ". ";
            }
        }
        cout << endl;
    }
    return 0;
}
