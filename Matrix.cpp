#include "Matrix.h"
#include <sstream>
#include <limits>

using namespace std;

Matrix::Matrix(size_t r, size_t c): num_row(r), num_col(c) {

    mat.resize(num_row);
    for(auto &v: mat) {
        v.resize(num_col);
    }

    identity_mat.resize(num_row);
    size_t diag = 0;

    // create the identity matrix for later use
    // only works for square mat i think...
    for(auto &v: identity_mat) {
        v.resize(num_col);
        v[diag++] = 1;
    }
}

void Matrix::fillMatrix(const vector<vector<double>> &v2) {
    mat = v2; // v2 is a ref, but copied by assign op
}

// User input handling is fairly robust
void Matrix::fillMatrix() {

    cout << "Enter each row, separarte elements with space, then press enter" << endl;
    for(size_t r = 0; r < num_row; ++r) {
        
        cout << "row " << r + 1 << ": ";

        string row, col;
        getline(cin, row);
        stringstream ss(row);
        size_t c = 0;
        while(ss >> col) {
            if(c > num_col) break; // safer than access out of bound
            mat[r][c++] = stod(col);
        }

        if(c != num_col) { // abort when size don't match
            cerr << "column size does not match." << endl;
            exit(0);  
        }

    }

}

// find the next potential pivot in the current column
int Matrix::findNextPivot(const vector<vector<double>> &v2, size_t start_row, size_t col) {
    // go down each rows, return -1 if reached end (zero-col)
    for(size_t i = start_row; i < num_row; ++i) {
        if(v2[i][col] != 0) return int(i);
    }
    return -1;
}


// Perform Gausian elimination to obtain <Reduced> Row Echelon Form
// For REF, an upper diagonalized matrix is formed (lower left all zeros)
// REF is only used for determinant for now
// O(n^3), there is a faster method using eigenvalues (but I need to learn it first...)
Matrix Matrix::getREF(bool reduced) {

    Matrix new_mat(this->num_row, this->num_col);
    new_mat.fillMatrix(this->mat);
    auto &ref_mat = new_mat.mat;

    size_t col = 0; // pivot col
    // row operations
    for(size_t row = 0; row < num_row; ++row) {

        if(ref_mat[row][col] == 0) { // entry is 0
            
            int pivot_row = findNextPivot(ref_mat, row, col);
            if(pivot_row != -1) {
                swap(ref_mat[row], ref_mat[unsigned(pivot_row)]);
                ++parity_ref;
            }
            else {
                bool zero_row = true;
                // search next column (back to current row and go right)
                for(size_t i = col; i < num_col; ++i) {
                    if(ref_mat[row][i] != 0) {
                        // found non-zero -> make it pivot
                        col = i;
                        zero_row = false;
                        break;
                    }
                } // for

                // all-zero row - so just skip to next row
                if(zero_row) continue;
            }
        } // if 

        size_t start_row = 0; // for row ops
        if(reduced) {
            double pivot = ref_mat[row][col];
            // divide entire row by the pivot to obtain pivot = 1 
            // (division causes precision error?)
            for(double &elem: ref_mat[row]) {
                elem /= pivot;
            }
        }
        else {
            start_row = row + 1; // only need diagonal triangle 0s (left)
        }

        // eliminate the elements for other rows to obtain pivot column
        for(size_t other_row = start_row; other_row < num_row; ++other_row) {
            if(other_row != row) {

                double pivot = ref_mat[row][col]; // is simply 1 in reduced mode
                double divisor = ref_mat[other_row][col] / pivot;
                for(size_t c = 0; c < num_col; ++c) {
                    ref_mat[other_row][c] -= (divisor * ref_mat[row][c]);
                }
            }
        }
        ++col; // proceed to next potnetial pivot column
    } // for row

    return new_mat;
}



double Matrix::getDeterminant() {

    if(this->num_row != this->num_col) {
        cerr << "does not support determinant for non-square matrix, returing 0" << endl;
        return 0;
    }

    Matrix ref = this->getREF(false);
    double det = 1;
    size_t diag = 0;

    for(auto &v2: ref.mat) {
        det *= v2[diag++];
    }
    det *= (parity_ref % 2) ? -1 : 1;  // odd: -1, even: +1
    cout << "parity: " << parity_ref << endl;
    return det;

}



// Given matrices A, B, return product matrix C.
// A.multiply(B) gives A * B = C
Matrix Matrix::multiply(const Matrix &mat_b) {
    if(this->num_col!=mat_b.num_row){
        cerr << "Multiplication not defined, matrix dimention error\n";
        exit(0);
    }
    Matrix cMat(this->num_row,mat_b.num_col);
    for(size_t col = 0; col < cMat.num_col;col++){
        for(size_t row = 0; row< cMat.num_row;row++){
            double temp = 0;
            for(size_t mid = 0; mid< mat_b.num_row ; mid++){
                temp += this->mat[row][mid] * mat_b.mat[mid][col];
            }
            cMat.mat[row][col] = temp;
        }
    }
    return cMat;
}



// Transpose the matrix
Matrix Matrix::transpose(const Matrix &mat) {

    return Matrix(mat.num_col, mat.num_row); // placeholder
}



void Matrix::printMatrix() {

    // find a way to format this nicely (align)

    for(auto &v: mat) {
        for(auto i: v) {
            if(i == -0) i = 0;
            cout << i << " ";
        }
        cout << endl;
    }

    // for(auto &v: identity_mat) {
    //     for(auto i: v) {
    //         cout << i << " ";
    //     }
    //     cout << endl;
    // }
}