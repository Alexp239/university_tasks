#include <iostream>
#include <math.h>
#include <string>

using namespace std;
/*
class Figure {
public:
    virtual double get_square() const { return 0; }
    virtual ~Figure(){}
};
*/
class Rectangle: public Figure {
    double x;
    double y;
public:
    double get_square() const { return x * y; }
    static Rectangle *make(const string &str) {
        Rectangle *rec = new Rectangle;
        const char *s = str.c_str();
        sscanf(s, "%lf %lf", &rec->x, &rec->y);
        return rec;
    }
};

class Circle: public Figure {
    double r;
public:
    double get_square() const { return M_PI * r * r; }
    static Circle *make(const string &str) {
        Circle *rec = new Circle;
        const char *s = str.c_str();
        sscanf(s, "%lf", &rec->r);
        return rec;
    }
};

class Square: public Figure {
    double x;
public:
    double get_square() const { return x * x; }
    static Square *make(const string &str) {
        Square *rec = new Square;
        const char *s = str.c_str();
        sscanf(s, "%lf", &rec->x);
        return rec;
    }
};
