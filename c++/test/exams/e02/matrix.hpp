#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <stddef.h>
#include <vector>

namespace cpp
{   

template<typename T>
class Matrix
{

public:
    Matrix(size_t a_rows = 0, size_t a_cols = 0);
    
    ~Matrix();
    Matrix(const Matrix& a_source);
    Matrix& operator=(const Matrix& a_source);

    int& operator()(const size_t& a_rows, const size_t& a_cols);
    const int& operator()(const size_t& a_rows, const size_t& a_cols) const;
                                                                                                                                                                                             
    size_t getRows() const;
    size_t getCols() const;

    void print() const;

    T& operator[][](size_t a_row, size_t a_col);

private:
    size_t m_rows;
    size_t m_cols;
    std::vector<std::vector<T> > m_mat;
    
};

bool isExist (int** a_mat,  size_t a_rows, size_t a_cols, int value);

}//namespace cpp

#include "matrix.hxx"

#endif /*MATRIX_HPP*/