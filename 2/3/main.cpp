#include <iostream>
#include <math.h>
#include <string.h>
#include <stdio.h>

using namespace std;

namespace numbers {
    class complex {
        double re;
        double im;
    public:
        complex(double a = 0.0, double b = 0.0) { re = a; im = b; }
        explicit complex(const char *s) { sscanf(s, "(%lf,%lf)", &re, &im); }
        double get_re() const { return re; }
        double get_im() const { return im; }
        double abs2() const { return re * re + im * im; }
        double abs() const { return sqrt(re * re + im * im); }

        void to_string(char *buf, size_t size) const {
            snprintf(buf, size, "(%.10g,%.10g)", re, im);
        }

        friend complex operator + (const complex & a, const complex & b);
        friend complex operator - (const complex & a, const complex & b);
        friend complex operator * (const complex & a, const complex & b);
        friend complex operator / (const complex & a, const complex & b);

        friend complex operator ~(const complex & a) { return complex(a.re, -a.im); }
        friend complex operator -(const complex & a) { return complex(-a.re, -a.im); }
    };

    complex operator + (const complex & a, const complex & b)
    {
        return complex(a.re + b.re, a.im + b.im);
    }

    complex operator - (const complex & a, const complex & b)
    {
        return complex(a.re - b.re, a.im - b.im);
    }

    complex operator * (const complex & a, const complex & b)
    {
        return complex(a.re * b.re - a.im * b.im, a.re * b.im + a.im * b.re);
    }

    complex operator / (const complex & a, const complex & b)
    {
        double sq = b.re * b.re + b.im * b.im;
        return complex((a.re * b.re + a.im * b.im) / sq, (b.re * a.im - b.im * a.re) / sq);
    }


    class complex_stack {
        size_t len;
        size_t top;
        complex *st;
    public:
        complex_stack(int a = 1)
        {
            len = a; top = 0;
            st = new complex[len];
        }

        complex_stack(const complex_stack & s)
        {
            len = s.len;
            top = s.top;
            st = new complex[len];
            memcpy(st, s.st, len * sizeof(*st));
        }

        ~complex_stack() { delete []st; }

        size_t size() const { return top; }

        complex &operator [](int a) const { return st[a]; }

        complex_stack & operator = (const complex_stack & s)
        {
            delete []st;
            len = s.len;
            top = s.top;
            st = new complex[len];
            memcpy(st, s.st, s.len * sizeof(*st));
            return *this;
        }

        complex operator +() const
        {
            return st[top - 1];
        }

        complex_stack operator ~ () const
        {
            complex_stack s2 = *this;
            s2.top--;
            return s2;
        }

        complex_stack operator << (const complex & num) const
        {
            complex_stack s2;
            if (top == len)
            {
                delete []s2.st;
                complex *st2 = new complex[len * 2];
                s2.st = st2;
                s2.len = 2 * len;
                s2.top = top;
                memcpy(s2.st, st, len * sizeof(*st));
            } else {
                s2 = *this;
            }
            s2.st[s2.top++] = num;
            return s2;
        }
    };


    complex eval(char **args, const complex &z)
    {
        int i = 0;
        complex_stack numb_st;
        while (args[i]) {
            char *s = args[i++];
            complex res, a, b;
            switch(s[0]) {
                case '(':
                    numb_st = numb_st << complex(s);
                    break;
                case 'z':
                    numb_st = numb_st << complex(z);
                    break;
                case '+':
                    b = +numb_st;
                    numb_st = ~numb_st;
                    a = +numb_st;
                    numb_st = ~numb_st;
                    res = a + b;
                    numb_st = numb_st << res;
                    break;
                case '-':
                    b = +numb_st;
                    numb_st = ~numb_st;
                    a = +numb_st;
                    numb_st = ~numb_st;
                    res = a - b;
                    numb_st = numb_st << res;
                    break;
                case '*':
                    b = +numb_st;
                    numb_st = ~numb_st;
                    a = +numb_st;
                    numb_st = ~numb_st;
                    res = a * b;
                    numb_st = numb_st << res;
                    break;
                case '/':
                     b = +numb_st;
                    numb_st = ~numb_st;
                    a = +numb_st;
                    numb_st = ~numb_st;
                    res = a / b;
                    numb_st = numb_st << res;
                    break;
                case '!':
                    a = +numb_st;
                    numb_st = numb_st << a;
                    break;
                case ';':
                    numb_st = ~numb_st;
                    break;
                case '~':
                    a = +numb_st;
                    numb_st = ~numb_st;
                    a = ~a;
                    numb_st = numb_st << a;
                    break;
                case '#':
                    a = +numb_st;
                    numb_st = ~numb_st;
                    a = -a;
                    numb_st = numb_st << a;
                    break;
            }
        }

        return +numb_st;
    }
}
/*
using namespace numbers;

int main()
{
    char s1[] = "(2, 3)";
    char s2[] = "z";
    char s3[] = "+";
    char s4[] = "(1, 3)";
    char s5[] = "~";
    char s6[] = "-";
    char s7[] = "(0, 0)";
    char s8[] = "+";
    char *s[9];
    s[0] = s1; s[1] = s2; s[2] = s3; s[3] = s4; s[4] = s5; s[5] = s6; s[6] = s7; s[7] = s8; s[8] = 0;
    complex z(1, 2);
    complex a = eval(s, z);
    cout << a.get_re() << ' ' << a.get_im() << endl;
    return 0;
}*/
