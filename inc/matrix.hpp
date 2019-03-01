#ifndef MATRIX_HPP_
#define MATRIX_HPP_


template <class U>
class Matrix {
    int rows, cols;
    std::vector< std::vector<U> > matrix;

    public:
    Matrix(){}
    // Construct from ({{x,y},{z,x}}) list
    Matrix(std::initializer_list< std::initializer_list<U> >);
    Matrix(int, int);
    //returns size
    std::pair<int, int> getSize();
    //change shape, may corrupt data
    void reshape(int, int);
    // fill with given value
    void fill(U);
    // randomize content beetwen lower & upper bound
    void randomize(U , U = 0);
    // Hadaward product of 2 matrices
    static Matrix elementwise(Matrix, Matrix);
    // transpose self
    void transpose();
    // return transposed
    Matrix T();
    // random access
    std::vector<U>& operator[] (unsigned int);
    // math operators
    Matrix operator* (float);
    Matrix operator* (int);
    Matrix operator* (Matrix);
    Matrix operator+ (Matrix);
    Matrix operator- (Matrix);

    template <class V>
    friend std::ostream& operator<< (std::ostream& os, const Matrix<V>& target);

    //map all elements with [](){} lambda function
    template<class Function>
    Matrix<U> map(Function);
};

template <class U>
Matrix<U>::Matrix(std::initializer_list< std::initializer_list<U> > content) {
    rows = content.size();
    cols = content.begin() -> size();
    matrix.resize(rows);
    auto j = content.begin();
    for (int i = 0; i < rows; ++i, ++j)
        matrix[i].assign(*j);
}

template <class U>
Matrix<U>::Matrix(int rows_, int cols_) {
    rows = rows_;
    cols = cols_;

    matrix.resize(rows);
    for (auto& row : matrix)
        row.resize(cols);
}

template <class U>
std::pair<int, int> Matrix<U>::getSize() {
    return std::pair<int, int> (rows,cols);
}

template <class U>
void Matrix<U>::reshape(int n, int m) {
    rows = n;
    cols = m;
    matrix.resize(n);
    for (auto& row : matrix)
        row.resize(m);
}

template <class U>
void Matrix<U>::fill(U value) {
    for (auto& row : matrix)
        for (auto& val : row)
            val = value;
}

template <class U>
void Matrix<U>::randomize(U upper_bound, U lower_bound) {
    for (auto& row : matrix)
        for (auto& value : row)
            value = float(rand()%1000) / 1000 * (upper_bound - lower_bound) + lower_bound;
}
template <class U>
Matrix<U> Matrix<U>::elementwise(Matrix first, Matrix second) {
    if (first.cols != second.cols || first.rows != second.rows)
        throw "SIZE_NO_MATCH";
    Matrix<U> result(first.rows, first.cols);
    for (int i = 0; i < first.rows; ++i) {
        for (int j = 0; j < first.cols; ++j) {
            result[i][j] = first[i][j] * second[i][j];
        }
    }
    return result;
}


template <class U>
void Matrix<U>::transpose() {
    Matrix result(cols, rows);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result[j][i] = (*this)[i][j];
        }
    }
    *this = result;
}

template <class U>
Matrix<U> Matrix<U>::T() {
    auto result = *this;
    result.transpose();
    return result;
}

template <class U>
std::vector<U>& Matrix<U>::operator[] (unsigned int n) {
    return matrix[n];
}

template <class U>
Matrix<U> Matrix<U>::operator* (float a) {
    Matrix result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result[i][j] = (*this)[i][j] * a;
        }
    }
    return result;
}

template <class U>
Matrix<U> Matrix<U>::operator* (int a) {
    Matrix result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result[i][j] = (*this)[i][j] * a;
        }
    }
    return result;
}

template <class U>
Matrix<U> Matrix<U>::operator* (Matrix second) {
    if (cols != second.rows)
        throw "SIZE_NO_MATCH";
    Matrix result(rows, second.cols);
    for (int i = 0; i < result.rows; ++i) {
        for (int j = 0; j < result.cols; ++j) {
            U sum{};
            for (int k = 0; k < cols; ++k) {
                sum += matrix[i][k] * second[k][j];
            }
            result[i][j] = sum;
        }
    }
    return result;
}

template <class U>
Matrix<U> Matrix<U>::operator+ (Matrix second) {
    if (rows != second.rows || cols != second.cols)
        throw "SIZE_NO_MATCH";

    Matrix result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result[i][j] = (*this)[i][j] + second[i][j];
        }
    }
    return result;
}

template <class U>
Matrix<U> Matrix<U>::operator- (Matrix second) {
    if (rows != second.rows && cols != second.cols)
        throw "SIZE_NO_MATCH";
        
    Matrix result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result[i][j] = (*this)[i][j] - second[i][j];
        }
    }
    return result;
}

template <class U>
std::ostream& operator<< (std::ostream& os, const Matrix<U>& target) {
    for (auto& row : target.matrix) {
        for (auto& value : row)
            os << value << "\t";
        os << "\n";
    }
    return os;
}

template<class U>
template<class Function>
Matrix<U> Matrix<U>::map(Function f) {
    for (auto& row : matrix) 
        for (auto& value : row)
            f(value);
    return *this;
}

using Matrixf = Matrix<float>;

#endif