#include <iostream>
#include <stdexcept>


template <class T>
class Matrix {
    int rows;
    int cols;
    T **m;
public:
    static const int ROWS_MAX = 16384;
    static const int COLS_MAX = 16384;
    static const long long MEM_MAX = 1073741824;

    Matrix(int r, int c, T def = T()) {
        if (r > ROWS_MAX || c > COLS_MAX || r < 1 || c < 1) {
            throw std::invalid_argument("Invalid input");
        }
        if (static_cast<long long>(r) * c * sizeof(T) > MEM_MAX) {
            throw std::invalid_argument("Too many data");
        }
        rows = r;
        cols = c;
        m = new T*[r];
        for (int i = 0; i < r; i++) {
            m[i] = new T[c];
        }
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                m[i][j] = def;
            }
        }
    }

    Matrix(const Matrix<T> &a) {
        rows = a.rows;
        cols = a.cols;
        m = new T*[rows];
        for (int i = 0; i < rows; i++) {
            m[i] = new T[cols];
        }
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                m[i][j] = a.m[i][j];
            }
        }
    }

    void swap(Matrix &a) throw() {
        std::swap(rows, a.rows);
        std::swap(cols, a.cols);
        std::swap(m, a.m);
    }

    Matrix &operator =(const Matrix &a)
    {
        Matrix tmp(a);
        this -> swap(tmp);
        return *this;
    }


    int get_rows() const {
        return rows;
    }

    int get_cols() const {
        return cols;
    }

    const T &at(int row, int col) const {
        if (row < 0 || row >= rows) {
            throw std::range_error("Range_error");
        }
        if (col < 0 || col >= cols) {
            throw std::range_error("Range_error");
        }
        return m[row][col];
    }

    T& at(int row, int col) {
        if (row < 0 || row >= rows) {
            throw std::range_error("Range_error");
        }
        if (col < 0 || col >= cols) {
            throw std::range_error("Range_error");
        }
        return m[row][col];
    }

    ~Matrix() {
        for (int i = 0; i < rows; i++) {
            delete []m[i];
        }
        delete []m;
    }
};
/*
int main()
{
    try{
        Matrix<int> a(2, 2, 5);
        Matrix<int> b(a);
        int& c = a.at(0, 0);
        c = 4;
        std::cout << a.at(0, 0);
        a = b;
    } catch (const std::invalid_argument& ia) {
        std::cout << ia.what() << std::endl;
    } catch (const std::range_error& re) {
        std::cout << re.what() << std::endl;
    } catch (...) {
        std::cout << "###" << std::endl;
    }
    return 0;
}
*/
