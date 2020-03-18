#include <vector>
#include <string>
#include <iostream>

class Matrix {

    private:
    size_t num_row, num_col;
    std::vector<std::vector<double>> mat;
    std::vector<std::vector<double>> identity_mat;
    int parity_ref = 0;

    public:

    Matrix(size_t r, size_t c);//: num_row(r), num_col(c) {}

    void fillMatrix();
    void fillMatrix(const std::vector<std::vector<double>> &v2);


    int findNextPivot(const std::vector<std::vector<double>> &v2, size_t r, size_t c);
    Matrix getREF(bool reduced);

    Matrix multiply(const Matrix &mat_b);
    Matrix transpose(const Matrix &mat);

    double getDeterminant();

    void printMatrix();
};

