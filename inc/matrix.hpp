#ifndef MATRIX_HPP_
#define MATRIX_HPP_

#include <iostream>
#include <vector>
#include <cstdlib>

template <class U>
class Matrix {
    int rows, cols;
    std::vector< std::vector<U> > matrix;

    public:
    Matrix(){}
    Matrix( std::initializer_list< std::initializer_list<U> > content ) {
        rows = content.size();
        cols = content.begin() -> size();
        matrix.resize(rows);
        auto j = content.begin();
        for ( int i = 0; i < rows; ++i, ++j )
            matrix[i].assign( *j );
    }

    Matrix( int rows_, int cols_ ) {
        rows = rows_;
        cols = cols_;

        matrix.resize( rows );
        for ( auto& row : matrix )
            row.resize( cols );
    }

    void reshape( int n, int m ) {
        rows = n;
        cols = m;
        matrix.resize(n);
        for ( auto& row : matrix )
            row.resize(m);
    }

    void fill( U value ) {
        for ( auto& row : matrix )
            for ( auto& val : row )
                val = value;
    }

    void randomize( U upper_bound, U lower_bound = 0 ) {
        for ( auto& row : matrix )
            for ( auto& value : row )
                value = float(rand()%1000) / 1000 * (upper_bound - lower_bound) + lower_bound;
    }

    void transpose() {
        Matrix result(cols, rows);
        for ( int i = 0; i < rows; ++i ) {
            for ( int j = 0; j < cols; ++j ) {
                result[j][i] = (*this)[i][j];
            }
        }
        *this = result;
    }

    Matrix T() {
        auto result = *this;
        result.transpose();
        return result;
    }

    std::vector<U>& operator[] ( unsigned int n ) {
        return matrix[n];
    }
    Matrix operator* ( float a ) {
        Matrix result(rows, cols);
        for ( int i = 0; i < rows; ++i ) {
            for ( int j = 0; j < cols; ++j ) {
                result[i][j] = (*this)[i][j] * a;
            }
        }
        return result;
    }
    Matrix operator* ( int a ) {
        Matrix result(rows, cols);
        for ( int i = 0; i < rows; ++i ) {
            for ( int j = 0; j < cols; ++j ) {
                result[i][j] = (*this)[i][j] * a;
            }
        }
        return result;
    }
    Matrix operator* ( Matrix second ) {
        if ( cols != second.rows )
            throw "SIZE_NO_MATCH";
        Matrix result( rows, second.cols );
        for ( int i = 0; i < result.rows; ++i ) {
            for ( int j = 0; j < result.cols; ++j ) {
                U sum{};
                for ( int k = 0; k < cols; ++k ) {
                    sum += matrix[i][k] * second[k][j];
                }
                result[i][j] = sum;
            }
        }
        return result;
    }
    Matrix operator+ ( Matrix second ) {
        if ( rows != second.rows && cols != second.cols )
            throw "SIZE_NO_MATCH";

        Matrix result(rows, cols);
        for ( int i = 0; i < rows; ++i ) {
            for ( int j = 0; j < cols; ++j ) {
                result[i][j] = (*this)[i][j] + second[i][j];
            }
        }
        return result;
    }
    Matrix operator- ( Matrix second ) {
        if ( rows != second.rows && cols != second.cols )
            throw "SIZE_NO_MATCH";
            
        Matrix result(rows, cols);
        for ( int i = 0; i < rows; ++i ) {
            for ( int j = 0; j < cols; ++j ) {
                result[i][j] = (*this)[i][j] - second[i][j];
            }
        }
        return result;
    }

    friend std::ostream& operator<< ( std::ostream& os, const Matrix& target ) {
        for ( auto& row : target.matrix ) {
            for ( auto& value : row )
                os << value << "\t";
            os << "\n";
        }
        return os;
    }
};

#endif
