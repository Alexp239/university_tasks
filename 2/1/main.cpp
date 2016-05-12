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
        complex_stack(int a = 0)
        {
            len = a; top = 0;
            if (a)
                st = new complex[len];
            else
                st = 0;
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
            if (!st) {
                s2.st = new complex[10];
                s2.len = 10;
            }
            else if (top == len)
            {
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
            switch(s[0])
            {
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


using namespace numbers;

int main(int argc, char **argv)
{
    complex c(argv[1]);
    double r;
    int n;
    sscanf(argv[3], "%d", &n);
    sscanf(argv[2], "%lf", &r);

    complex next, tmp, mid, val, res;
    complex prev(c.get_re() + r, c.get_im());
    double ang, re, im, ang2;
    for (int i = 1; i <= n; i++) {
        ang = M_PI * 2 * i / n;
        re = cos(ang) * r;
        im = sin(ang) * r;
        tmp = complex(re, im);
        next = tmp + c;

        ang2 = M_PI * 2 * (i - 0.5) / n;
        re = cos(ang2) * r;
        im = sin(ang2) * r;
        tmp = complex(re, im);
        mid = c + tmp;

        tmp = eval(argv + 4, mid) * (next - prev);
        val = val + tmp;
        prev = next;
    }

    char s[100];
    val.to_string(s, sizeof(s));

    cout << s << endl;;

    return 0;
}
