#include <iostream>
#include <math.h>
#include <string>
#include <algorithm>
#include <sstream>
#include <vector>

using namespace std;

class Figure {
public:
    virtual double get_square() const { return 0; }
    virtual ~Figure(){}
};

class Rectangle: public Figure {
    double x;
    double y;
public:
    double get_square() const { return x * y; }
    static Rectangle *make(const string str) {
        Rectangle *rec = new Rectangle;
        const char *s = str.c_str();
        sscanf(s, "%lf %lf", &rec->x, &rec->y);
        return rec;
    }
    string to_string() const {
        return "R " + std::to_string(x) + " " + std::to_string(y);
    }
};

class Circle: public Figure {
    double r;
public:
    double get_square() const { return M_PI * r * r; }
    static Circle *make(const string str) {
        Circle *rec = new Circle;
        const char *s = str.c_str();
        sscanf(s, "%lf", &rec->r);
        return rec;
    }
    string to_string() const {
        return "C " + std::to_string(r);
    }
};

class Square: public Figure {
    double x;
public:
    double get_square() const { return x * x; }
    static Square *make(const string str) {
        Square *rec = new Square;
        const char *s = str.c_str();
        sscanf(s, "%lf", &rec->x);
        return rec;
    }
    string to_string() const {
        return "S " + std::to_string(x);
    }
};

bool comp(Figure f1, Figure f2)
{
    return (f1.get_square() < f2.get_square());
}

int main()
{
    vector<Figure> figures;
    string cur_str;
    while (getline(cin, cur_str)) {
        istringstream iss (cur_str);
        char c;
        iss >> c;
        if (c == 'R') {
            cout << iss.str() << endl;
        }
    }
    //stable_sort(figures.begin(), figures.end(), comp);
}
