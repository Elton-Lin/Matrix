#include <vector>
#include <string>
#include <iostream>

class Matrix {

    private:
    size_t num_row, num_col;
    std::vector<std::vector<double>> mat;
    std::vector<std::vector<double>> identity_mat;

    public:

    Matrix(size_t r, size_t c);//: num_row(r), num_col(c) {}

    void fillMatrix();
    void fillMatrix(const std::vector<std::vector<double>> &v2);


    int findNextPivot(size_t r, size_t c);
    void getRREF();

    Matrix multiply(const Matrix &mat_b);
    Matrix transpose(const Matrix &mat);


    void printMatrix();
};

