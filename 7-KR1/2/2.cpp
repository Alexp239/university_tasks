#include <iostream>
#include <stdexcept>
#include <string>
#include <cerrno>
#include <algorithm>
#include <limits>
#include <sstream>

class Range {
    int low;
    int high;

    int range_error(long long a) const {
        if (a < std::numeric_limits<int>::lowest()) {
            return 1;
        }
        if  (a > std::numeric_limits<int>::max()) {
            return 1;
        }
        return 0;
    }

public:

    Range(int a = 0, int b = 0) {
        if (a > b) {
            throw std::invalid_argument("low > high");
        }

        low = a;
        high = b;
    }

    explicit Range(const std::string &str) {
        std::istringstream iss (str);
        int a, b;
        char c1, c2, c3;
        std::string str_end;
        iss >> c1;
        iss >> a;
        if (!bool(iss)) {
            throw std::invalid_argument("input error");
        }
        iss >> c2;
        iss >> b;
        if (!bool(iss)) {
            throw std::invalid_argument("input error");
        }
        iss >> c3;
        iss >> str_end;
        if (c1 != '(' || c2 != ',' || c3 != ')' || str_end != "") {
            throw std::invalid_argument("input error");
        }
        if (errno == ERANGE || a > b) {
            throw std::invalid_argument("low > high or range_error");
        }

        low = a;
        high = b;
    }

    std::string to_string() const {
        std::string ans("(");
        ans += std::to_string(low);
        ans += ",";
        ans += std::to_string(high);
        ans += ")";
        return ans;
    }

    int get_low() const {
        return low;
    }
    int get_high() const {
        return high;
    }

    friend Range operator + (const Range &a, const Range &b) {
        long long left = static_cast<long long>(a.low) + b.low;
        long long right = static_cast<long long>(a.high) + b.high;
        if (a.range_error(left) || a.range_error(right)) {
            throw std::range_error("Range_error");
        }
        return Range(left, right);
    }

    friend Range operator - (const Range &a, const Range &b) {
        long long left = static_cast<long long>(a.low) - b.high;
        long long right = static_cast<long long>(a.high) - b.low;
        if (a.range_error(left) || a.range_error(right)) {
            throw std::range_error("Range_error");
        }
        return Range(left, right);
    }

    friend Range operator * (const Range &a, const Range &b) {
        long long res1 = static_cast<long long>(a.low) * b.low;
        long long res2 = static_cast<long long>(a.low) * b.high;
        long long res3 = static_cast<long long>(a.high) * b.low;
        long long res4 = static_cast<long long>(a.high) * b.high;

        if (a.range_error(res1) || a.range_error(res2)) {
            throw std::range_error("Range_error");
        }
        if (a.range_error(res3) || a.range_error(res4)) {
            throw std::range_error("Range_error");
        }

        int left = std::min(a.low * b.low, a.low * b.high);
        left = std::min(left, std::min(a.high * b.low, a.high * b.high));
        int right = std::max(a.low * b.low, a.low * b.high);
        right = std::max(right, std::max(a.high * b.low, a.high * b.high));

        return Range(left, right);
    }

    Range operator -() const {
        long long left = -static_cast<long long>(high);
        long long right = -static_cast<long long>(low);

        if (this->range_error(left) || this->range_error(right)) {
            throw std::range_error("Range_error");
        }
        return Range(-high, -low);
    }
};
/*
int main()
{
    Range a(-1, 1), b(-2, 3);
    Range c("(0,0) ");
    std::cout << c.to_string() << std::endl;
    return 0;
}
*/
