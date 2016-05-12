#include <cstring>
#include <cstdio>
#include <algorithm>

namespace numbers
{
    class complex
    {
        double re, im;
public:
        // constructors
        complex(double re = 0.0, double im = 0.0): re(re), im(im) {}
        explicit complex(const char *s)
        {
            sscanf(s, "(%lf,%lf)", &re, &im);
        }
        // getters
        double get_re(void) const { return re; }
        double get_im(void) const { return im; }
        // abs
        double abs2(void) const { return re * re + im * im; }
        double abs(void) const { return sqrt(abs2()); }
        // to string
        size_t to_string(char *buf, size_t size) const
        {
            /*
            * Returns the number of characters written
            * as reported by snprintf
            */
            return snprintf(buf, size, "(%.10g,%.10g)", re, im);
        }
        friend complex operator - (const complex &self);
        friend complex operator ~ (const complex &self);
        friend complex operator + (const complex &self, const complex &other);
        friend complex operator - (const complex &self, const complex &other);
        friend complex operator * (const complex &self, const complex &other);
        friend complex operator / (const complex &self, double other);
        friend complex operator / (const complex &self, const complex &other);
    };
    // operators
    complex operator - (const complex &self)
    {
        return complex{-self.re, -self.im};
    }
    complex operator ~ (const complex &self)
    {
        return complex{self.re, -self.im};
    }
    complex operator + (const complex &self, const complex &other)
    {
        return complex{self.re + other.re, self.im + other.im};
    }
    complex operator - (const complex &self, const complex &other)
    {
        return complex{self.re - other.re, self.im - other.im};
    }
    complex operator * (const complex &self, const complex &other)
    {
        return complex
            {
                self.re * other.re - self.im * other.im,
                self.re * other.im + self.im * other.re
            };
    }
    complex operator / (const complex &self, double other)
    {
        // may be better precision-wise
        return complex{self.re / other, self.im / other};
    }
    complex operator / (const complex &self, const complex &other)
    {
        // dear complier, please optimize that for me, will you?
        return self * ~other / other.abs2();
    }


    class complex_stack
    {
        size_t avail_size = 0, used_size = 0;
        complex *data = nullptr;

        complex_stack(size_t avail_size, size_t used_size, const complex *data):
            avail_size(avail_size),
            used_size(used_size),
            data(new complex[avail_size])
        {
            if (data && used_size) {
                memcpy(this->data, data, used_size * sizeof(complex));
            }
        }

        // resizing utilities
        constexpr static int coeff = 2;
        static size_t inc_size(size_t avail_size, size_t used_size)
        {
            return used_size > avail_size ?
                std::max(avail_size * coeff, used_size)
                : avail_size;
        }
        static size_t dec_size(size_t avail_size, size_t used_size)
        {
            return avail_size > used_size * coeff ? avail_size / coeff : avail_size;
        }
public:
        // constructors
        // default
        complex_stack(void) {}
        // copy constructor
        complex_stack(const complex_stack &other):
            complex_stack(other.avail_size, other.used_size, other.data)
        {}
        // move constructor
        complex_stack(complex_stack &&other) { swap(other); }
        // assignment
        complex_stack & operator = (const complex_stack &other)
        {
            complex_stack tmp{other};
            swap(tmp);
            return *this;
        }
        complex_stack & operator = (complex_stack &&other)
        {
            swap(other);
            return *this;
        }
        // destructor
        ~complex_stack() { delete[] data; }

        // const methods & operators
        size_t size(void) const
        {
            return used_size;
        }
        complex operator [] (size_t ind) const
        {
            return data[ind];
        }
        complex & operator [] (size_t ind)
        {
            return data[ind];
        }
        complex operator + (void) const
        {
            return data[used_size - 1];
        }
        void swap(complex_stack &other)
        {
            std::swap(used_size, other.used_size);
            std::swap(avail_size, other.avail_size);
            std::swap(data, other.data);
        }
        // operators
        friend complex_stack operator << (const complex_stack &self, complex c);
        friend complex_stack operator << (complex_stack &&self, complex c);
        friend complex_stack operator ~ (const complex_stack &self);
        friend complex_stack operator ~ (complex_stack &&self);
    };
    // operators
    complex_stack operator << (const complex_stack &self, complex c)
    {
        size_t newsize = complex_stack::inc_size(self.avail_size, self.used_size + 1);
        complex_stack res{newsize, self.used_size, self.data};
        res.data[res.used_size++] = c;
        return res;
    }
    complex_stack operator << (complex_stack &&self, complex c)
    {
        size_t newsize = complex_stack::inc_size(self.avail_size, self.used_size + 1);
        if (newsize != self.avail_size) {
            return ((complex_stack &) self) << c;
        }
        complex_stack res{self};
        res.data[res.used_size++] = c;
        return res;
    }
    complex_stack operator ~ (const complex_stack &self)
    {
        size_t newsize = complex_stack::dec_size(self.avail_size, self.used_size - 1);
        complex_stack res{newsize, self.used_size - 1, self.data};
        return res;
    }
    complex_stack operator ~ (complex_stack &&self)
    {
        size_t newsize = complex_stack::inc_size(self.avail_size, self.used_size + 1);
        if (newsize != self.avail_size) {
            return ~(complex_stack &) self;
        }
        complex_stack res{self};
        res.used_size--;
        return res;
    }

    complex eval(const char * const *commands, const complex &z)
    {
        complex_stack stack{};
        const char *cmd;
        size_t i;
        for (i = 0, cmd = commands[i]; cmd; cmd = commands[++i]) {
            int argscnt = 0;
            switch (cmd[0]) {
            case '+':
            case '-':
            case '*':
            case '/':
                argscnt = 2;
                break;
            case ';':
            case '~':
            case '#':
                argscnt = 1;
                break;
            default:
                argscnt = 0;
            }
            complex z1, z2;
            if (argscnt == 2) {
                z2 = +stack;
                stack = ~stack;
            }
            if (argscnt >= 1) {
                z1 = +stack;
                stack = ~stack;
            }
            switch (cmd[0]) {
            case '(':
                {
                    complex c{cmd};
                    stack = stack << c;
                }
                break;
            case 'z':
                stack = stack << z;
                break;
            case '+':
                stack = stack << (z1 + z2);
                break;
            case '-':
                stack = stack << (z1 - z2);
                break;
            case '*':
                stack = stack << (z1 * z2);
                break;
            case '/':
                stack = stack << (z1 / z2);
                break;
            case '!':
                stack = stack << +stack;
                break;
            case ';':
                break;
            case '~':
                stack = stack << ~z1;
                break;
            case '#':
                stack = stack << -z1;
                break;
            default:
                /* shouldn't be here
                * argscnt == 0
                * so we'll just ignore this command
                */
                ;
            }
        }
        return +stack;
    }
}

#include <iostream>
using namespace std;
using namespace numbers;

complex
point(double alpha, const complex C, double R)
{
    complex res{cos(alpha), sin(alpha)};
    return res * R + C;
}

int main(int argc, char *argv[])
{
    complex C{argv[1]};
    double R = atof(argv[2]);
    unsigned int N = atoi(argv[3]);
    complex res = 0;
    const double arc = 2 * M_PI / N;
    for (unsigned int i = 0; i < N; i++) {
        complex z1 = point(arc * i, C, R);
        complex z2 = point(arc * (i + 1), C, R);
        complex z15 = point(arc * (i + 0.5), C, R);
        res = res + eval(&argv[4], z15) * (z2 - z1);
    }
    char output[128]; // hopefully that'll be enough
    res.to_string(output, sizeof(output));
    cout << output << endl;
    return 0;
}
