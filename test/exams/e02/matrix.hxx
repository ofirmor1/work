#ifndef MATRIX_HXX
#define MATRIX_HXX

#include <iostream>

namespace cpp
{

template<typename T>
Matrix<T>::Matrix(size_t a_rows, size_t a_cols)
: m_rows(a_rows)
, m_cols(a_cols)
,
{
    m_mat.resize(a_rows);
    for (size_t i = 0; i < m_mat.size(); i++)
    {
        m_mat[i] = new int[a_cols];
    }
}

template<typename T>
Matrix<T>::Matrix(const Matrix& a_source)
: m_rows(a_source.m_rows)
, m_cols(a_source.m_cols)
, m_mat(new int*[a_source.m_mat])
{
  for (size_t row = 0; row < a_source.m_rows; ++row)
  {
      for (size_t col = 0; col < a_source.m_cols; ++col)
      {
          m_mat[row][col] = a_source.m_mat[row][col];
      }
  }
}

template<typename T>
Matrix<T>::~Matrix()
{
    for (size_t i = 0; i < m_rows; ++i)
    {
        delete[] m_mat[x];
    }

    delete[] m_mat;
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix& a_source)
{
    if (&a_source == this)
    {
        return *this;
    }

    size_t newRows = a_source.getRows();
    size_t newCols = a_source.getCols();

    mat.resize(newRows);

    for (size_t i = 0; i < mat.size(); ++i) 
    {
        mat[i].resize(newCols);
    }

    for (size_t i = 0; i < newRows; ++i) 
    {
        for (size_t j = 0; j < newCols; ++j) 
        {
            mat[i][j] = a_source(i, j);
        }
    }

    m_rows = newRows;
    m_cols = newCols;

    return *this;
}


template<typename T>
int& Matrix<T>::operator()(size_t const& a_rowNum, size_t const& a_colNum)
{
    return m_mat[a_rowNum][a_colNum];
}

template<typename T>
size_t Matrix<T>::getRows() const
{
    return m_rows;
}

template<typename T>
size_t Matrix<T>::getCols() const
{
    return m_cols;
}

template<typename T>
void Matrix<T>::print() const
{
    std::cout << "Matrix: " << std::endl;
    for (size_t i = 0; i < m_rows; i++) {
        for (size_t j = 0; j < m_cols; j++) {
            std::cout << "[" << m_mat[i][j] << "] ";
        }
        std::cout << std::endl;
    }
}

bool isExist (int** a_mat,  size_t a_rows, size_t a_cols, int a_val)
{
    size_t i, j;
    for(i = 0; i < a_rows; i++) 
    {
        for(j = 0; j < a_cols; j++) 
        {
            if(a_mat[i][j] == a_val) 
            {
                return true;
            }
        }
    }

    return false;
}

}//namespace cpp

#endif /*MATRIX_HXX*/
