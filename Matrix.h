#include <vector>
#include <string>
#include <iostream>

class Matrix {

    private:
    unsigned int num_row, num_col;
    std::vector<std::vector<double>> mat;
    std::vector<std::vector<double>> identity_mat;

    public:

    Matrix(unsigned int r, unsigned int c);//: num_row(r), num_col(c) {}

    void fillMatrix();
    void fillMatrix(std::vector<std::vector<double>> v2);


    int findNextPivot(unsigned int r, unsigned int c);
    void getRREF();

    Matrix multiply(Matrix mat_b);
    Matrix transpose(Matrix mat);


    void printMatrix();
};

