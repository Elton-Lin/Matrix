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

void test_RREF() {

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

    m.getRREF();
    cout << "RREF: " << endl;
    m.printMatrix();

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
void test_trans() {
    string input;
    int row2,col2;
    cout << "Please enter number of rows for the matrix: ";
    getline(cin, input); row2 = check_input(input);
    cout << "Please enter number of columns for the matrix: ";
    getline(cin, input); col2 = check_input(input);
    Matrix b((size_t(row2)), (size_t(col2)));
    b.fillMatrix();

    Matrix trans = b.transpose(b);
    trans.printMatrix();
}

int main(int argc, char *argv[]) {

    cout.precision(2);

    // test_RREF();
    //test_multiplication();
    //test_trans();
    vector<string> types{ "RREF", "Multiplication", "Transpose", "(stab)" };
    unsigned int choice;
    cout<<endl;
    cout << "             << -- Matrix tester -- >>" << endl;
    cout << "===================================================" <<endl;
    for (size_t i = 0; i < types.size(); ++i)
        cout << "  " << i << ") " << types[i] << endl;
    cout << endl;
    cout << "Select one: ";
    cin >> choice;
    string junk;
    getline(cin,junk);

    if (choice == 0) {
        test_RREF();
    } // if
    else if (choice == 1) {
        test_multiplication();
    } // else if
    else if (choice == 2) {
        test_trans();
    } // else if
    else if (choice == 3) {
        cout << "Not yet implemented"<<endl;
    } // else if
    else {
        cout << "Unknown function!" << endl << endl;
        exit(1);
    } // else

    
    return 0;
}