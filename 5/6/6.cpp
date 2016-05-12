#include <iostream>
#include <math.h>
#include <string>
#include <algorithm>
#include <sstream>
#include <vector>
#include <stdio.h>

using namespace std;
/*
class Figure {
public:
    virtual double get_square() const {return 0;}
    virtual string to_string() const {return string{""};}
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
        return string{"Rec"};
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
        return string{"Circle"};
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
        return string{"Sq"};
    }
};
*/
bool comp(Figure *f1, Figure *f2)
{
    return (f1->get_square() < f2->get_square());
}

int main()
{
    vector<Figure *> figures;
    string cur_str;
    while (getline(cin, cur_str)) {
        istringstream iss (cur_str);
        char c;
        iss >> c;
        string inp;
        getline(iss, inp);
        Figure *tmp;
        if (c == 'R') {
            tmp = Rectangle::make(inp);
        } else if (c == 'C') {
            tmp = Circle::make(inp);
        } else if (c == 'S') {
            tmp = Square::make(inp);
        }
        figures.push_back(tmp);
    }

    stable_sort(figures.begin(), figures.end(), comp);
    for (vector<Figure *>::iterator it = figures.begin(); it != figures.end(); it++) {
        cout << (*it)->to_string() << endl;
    }
    for (vector<Figure *>::iterator it = figures.begin(); it != figures.end(); it++) {
        delete *it;
    }
}
