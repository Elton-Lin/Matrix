#include "Matrix.h"
#include <cassert>

using namespace std;

int check_input(string &s) {

    for(char c: s) {
        if(!isdigit(c)) { // also takes care of negative numbers
            cout << "invalid input for matrix dimensions" << endl;
            exit(0);
        }
    }

    return stoi(s);
}

int main(int argc, char *argv[]) {

    cout.precision(2);

    int row, col;
    string input;

    cout << "Please enter number of rows: ";
    getline(cin, input); row = check_input(input);
    cout << "Please enter number of columns: ";
    getline(cin, input); col = check_input(input);

    Matrix m((unsigned(row)), (unsigned(col)));
    m.fillMatrix();
    m.printMatrix();

    m.getRREF();
    cout << "RREF: " << endl;
    m.printMatrix();

    return 0;
}