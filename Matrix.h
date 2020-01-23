#include <vector>
#include <string>
#include <iostream>

class Matrix {

    private:
    unsigned num_row, num_col;
    std::vector<std::vector<double>> mat;
    std::vector<std::vector<double>> identity_mat;

    public:

    Matrix(int r, int c);//: num_row(r), num_col(c) {}

    void fillMatrix();
    void fillMatrix(std::vector<std::vector<double>> v2);


    int findNextPivot(int r, int c);
    void getRREF();


    void printMatrix();
};

