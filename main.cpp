#include "Matrix.h"
#include <cassert>
#include <iomanip>

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


void print_available_operation() {

    cout << "Please select a matrix operation to perform:\n"
        << "0: quit\n"
        << "1: get determinant\n"
        << "2: get REF\n"
        << "3: get RREF\n"
        << "4: multiply 2 matrix\n"
        << "5: get inverse\n"
        << "6: get transpose\n"
        << "Enter: \n";
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


void test_an_operation(size_t op_code) {

    if(op_code == 0) 
        return;

    size_t row, col;
    tie(row, col) = get_dimensions();
    Matrix m(row, col, true);

    Matrix result_matrix;
    switch (op_code) {
    case 1: {// numeric result
        double det = m.getDeterminant();
        cout << "determinant: " << det << endl;
        return;
    }
    case 2: {
        result_matrix = m.getREF(false);
        break;
    }
    case 3: {
        result_matrix = m.getREF(true);
        break;
    }
    case 4: {
        size_t row, col;
        tie(row, col) = get_dimensions();
        Matrix m2(row, col, true);

        result_matrix = m.multiply(m2);
        break;
    }
    case 5: {
        result_matrix = m.getInverse();
        // auto identity = m.multiply(result_matrix);
        // identity.printMatrix();
        break;
    }
    case 6: {
        result_matrix = m.getTranspose();
        break;
    }
    }

    cout << "result matrix: \n";
    result_matrix.printMatrix();
}


int main(int argc, char *argv[]) {

    // this translates it to scientific number then set precision
    // cout.precision(2);
    // e.g. 0.00015 --> 1.5e-4

    // this direcly sets precision
    // e.g. 0.00015 --> 0.00
    cout << fixed;
    cout << setprecision(2);

    print_available_operation();

    string op_code;
    getline(cin, op_code);
    test_an_operation(cast_to_sizet(op_code));
    
    return 0;
}
// some ideas
// - make it iteractive:
//  - put a while to create a session
//  - hold a set of matrix user created or resulted from operation
//    and make them reusable (with a map)