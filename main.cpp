#include "Matrix.h"
#include <cassert>

using namespace std;

int check_input(const string &s) {

    for(char c: s) {
        if(!isdigit(c)) { // also takes care of negative numbers
            cout << "invalid input for matrix dimensions" << endl;
            exit(0);
        }
    }

    return stoi(s);
}

void test_REF() {

    int row, col;
    string input;

    cout << "Please enter number of rows: ";
    getline(cin, input); row = check_input(input);
    cout << "Please enter number of columns: ";
    getline(cin, input); col = check_input(input);

    Matrix m((size_t(row)), (size_t(col)));
    m.fillMatrix();
    cout << "Input Matrix: " << endl;
    m.printMatrix();

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
    //for testing multiplication
    string input;
    int row2,col2;
    cout << "Please enter number of rows for the second matrix: ";
    getline(cin, input); row2 = check_input(input);
    cout << "Please enter number of columns for the second matrix: ";
    getline(cin, input); col2 = check_input(input);

    Matrix b((size_t(row2)), (size_t(col2)));
    b.fillMatrix();

    int row3,col3;
    cout << "Please enter number of rows for the third matrix: ";
    getline(cin, input); row3 = check_input(input);
    cout << "Please enter number of columns for the third matrix: ";
    getline(cin, input); col3 = check_input(input);

    Matrix c((size_t(row3)), (size_t(col3)));
    c.fillMatrix();

    Matrix product = b.multiply(c);
    product.printMatrix();
}

int main(int argc, char *argv[]) {

    cout.precision(2);

    test_REF();
    // test_multiplication();

    
    return 0;
}