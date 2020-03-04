#include "Matrix.h"
#include <sstream>
#include <limits>

using namespace std;

Matrix::Matrix(int r, int c): num_row(r), num_col(c) {

    identity_mat.resize(num_row);
    int diag = 0;

    // create the identity matrix for later use
    for(auto &v: identity_mat) {
        v.resize(num_col);
        v[diag++] = 1;
    }
}


// User input handling is fairly robust
void Matrix::fillMatrix() {
    
    mat.resize(num_row);
    for(auto &v: mat) {
        v.reserve(num_col);
    }

    cout << "Enter each row, separarte elements with space, then press enter" << endl;
    for(int r = 0; r < num_row; ++r) {
        
        cout << "row " << r + 1 << ": ";

        string row, c;
        getline(cin, row);
        stringstream ss(row);
        while(ss >> c) {
            mat[r].push_back(stod(c));
        }

        // // abort when size don't match
        if(mat[r].size() != num_col) {
            cerr << "column size does not match." << endl;
            exit(0);  
        }
    }

}

// find the next potential pivot in the current column
int Matrix::findNextPivot(int start_row, int col) {
    // go down each rows, return -1 if reached end (zero-col)
    for(int i = start_row; i < num_row; ++i) {
        if(mat[i][col] != 0) return i;
    }
    return -1;
}

// might want to make it return the RREF (a new copy matrix)
void Matrix::getRREF() {

    int col = 0;
    // row operations
    for(int row = 0; row < num_row; ++row) {

        if(mat[row][col] == 0) { // entry is 0
            
            int pivot_row = findNextPivot(row, col);
            if(pivot_row == -1) {
                bool zero_row = true;
                // search next column (back to current row and go right)
                for(int i = col; i < num_col; ++i) {
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
            else {
                swap(mat[row], mat[pivot_row]);
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
        for(int other_row = 0; other_row < num_row; ++other_row) {
            if(other_row != row) {

                double divisor = mat[other_row][col];
                for(int c = 0; c < num_col; ++c) {
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