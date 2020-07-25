#include "Matrix.h"
#include <cassert>

using namespace std;

size_t cast_to_sizet(const string &s) {

    for(char c: s) {
        if(!isdigit(c)) { // also takes care of negative numbers
            cout << "invalid input for matrix dimensions" << endl;
            exit(0);
        }
    }
    
    return size_t(stoi(s));
}


pair<int, int> get_dimensions() {
    size_t row, col;
    string input;

    cout << "Please enter number of rows: ";
    getline(cin, input); row = cast_to_sizet(input);
    cout << "Please enter number of columns: ";
    getline(cin, input); col = cast_to_sizet(input);

    return {row, col};
}


void test_REF() {

    size_t row, col;
    tie(row, col) = get_dimensions();
    Matrix m(row, col, true);

    auto rref_m = m.getREF(true);
    cout << "RREF: " << endl;
    rref_m.printMatrix();

    auto ref_m = m.getREF(false);
    cout << "REF: " << endl;
    ref_m.printMatrix();

    double det = m.getDeterminant();
    cout << "det: " << det << endl;

}

void test_multiplication() {
    
    size_t row, col;
    tie(row, col) = get_dimensions();
    Matrix b(row, col, true);

    size_t row2, col2;
    tie(row2, col2) = get_dimensions();
    Matrix c(row2, col2, true);

    Matrix product = b.multiply(c);
    product.printMatrix();
}

void test_inverse() {
    
    size_t row, col;
    tie(row, col) = get_dimensions();
    Matrix m(row, col, true);

    Matrix mInv = m.getInverse();
    mInv.printMatrix();
}




int main(int argc, char *argv[]) {

    cout.precision(2);

    //test_REF();
    // test_multiplication();

    test_inverse();
    return 0;
}