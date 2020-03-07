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
    for(auto &v: identity_mat) {
        v.resize(num_col);
        v[diag++] = 1;
    }
}

void Matrix::fillMatrix(const vector<vector<double>> &v2) {
    mat = v2;
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
            // mat[r].push_back(stod(col));
            if(c > num_col) break; // safer than access out of bound
            mat[r][c++] = stod(col);
        }

        if(c != num_col) {
            cerr << "column size does not match." << endl;
            exit(0);  
        }

        // // abort when size don't match
        // if(mat[r].size() != num_col) {
        //     cerr << "column size does not match." << endl;
        //     exit(0);  
        // }
    }

}

// find the next potential pivot in the current column
int Matrix::findNextPivot(size_t start_row, size_t col) {
    // go down each rows, return -1 if reached end (zero-col)
    for(size_t i = start_row; i < num_row; ++i) {
        if(mat[i][col] != 0) return int(i);
    }
    return -1;
}

// might want to make it return the RREF (a new copy matrix)
void Matrix::getRREF() {

    size_t col = 0;
    // row operations
    for(size_t row = 0; row < num_row; ++row) {

        if(mat[row][col] == 0) { // entry is 0
            
            int pivot_row = findNextPivot(row, col);
            if(pivot_row != -1) {
                swap(mat[row], mat[unsigned(pivot_row)]);
            }
            else {
                bool zero_row = true;
                // search next column (back to current row and go right)
                for(size_t i = col; i < num_col; ++i) {
                    if(mat[row][i] != 0) {
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

        double pivot = mat[row][col];
        // divide entire row by the pivot to obtain pivot = 1 
        // (division causes precision error?)
        for(double &elem: mat[row]) {
            elem /= pivot;
        }

        // printMatrix();

        // eliminate the elements for other rows to obtain pivot column
        for(size_t other_row = 0; other_row < num_row; ++other_row) {
            if(other_row != row) {

                double divisor = mat[other_row][col];
                for(size_t c = 0; c < num_col; ++c) {
                    mat[other_row][c] -= (divisor * mat[row][c]);
                }
            }
        }
        ++col; // proceed to next potnetial pivot column
    } // for row
}

// Given matrices A, B, return product matrix C.
// A.multiply(B) gives A * B = C
Matrix Matrix::multiply(Matrix mat_b) {

    return Matrix(1, 1); // placeholder
}

// Transpose the matrix
Matrix Matrix::transpose(Matrix mat) {

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