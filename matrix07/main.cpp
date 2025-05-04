#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class SparseMatrix {
public:
    int rows, cols;
    vector<int> vptr, vpos, vval;

    SparseMatrix(int r = 0, int c = 0) : rows(r), cols(c) {}

    void inputFromUser() {
        cout << "Enter number of rows and columns: ";
        cin >> rows >> cols;
        vptr.push_back(0);
        for (int i = 0; i < rows; ++i) {
            int count = 0;
            for (int j = 0; j < cols; ++j) {
                int val;
                cout << "Element [" << i << "][" << j << "]: ";
                cin >> val;
                if (val != 0) {
                    vval.push_back(val);
                    vpos.push_back(j);
                    ++count;
                }
            }
            vptr.push_back(vptr.back() + count);
        }
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file) {
            cerr << "Cannot open file.\n";
            return;
        }

        file >> rows >> cols;
        vector<vector<int>> matrix(rows, vector<int>(cols));
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                file >> matrix[i][j];

        vptr.push_back(0);
        for (int i = 0; i < rows; ++i) {
            int count = 0;
            for (int j = 0; j < cols; ++j) {
                if (matrix[i][j] != 0) {
                    vval.push_back(matrix[i][j]);
                    vpos.push_back(j);
                    ++count;
                }
            }
            vptr.push_back(vptr.back() + count);
        }
    }

    void displayMatrix() {
        vector<vector<int>> matrix(rows, vector<int>(cols, 0));
        int valIndex = 0;
        for (int i = 0; i < rows; ++i) {
            for (int j = vptr[i]; j < vptr[i + 1]; ++j) {
                matrix[i][vpos[j]] = vval[valIndex++];
            }
        }

        for (auto& row : matrix) {
            for (int val : row) cout << val << " ";
            cout << endl;
        }
    }

    void subtractFromDiagonal(int value) {
        vector<vector<int>> matrix(rows, vector<int>(cols, 0));
        int valIndex = 0;
        for (int i = 0; i < rows; ++i) {
            for (int j = vptr[i]; j < vptr[i + 1]; ++j) {
                matrix[i][vpos[j]] = vval[valIndex++];
            }
        }

        for (int i = 0; i < rows && i < cols; ++i) {
            matrix[i][i] -= value;
        }

        for (auto& row : matrix) {
            for (int val : row) cout << val << " ";
            cout << endl;
        }
    }
};

int main() {
    SparseMatrix matrix;
    int choice;
    cout << "Choose input method:\n1. From file\n2. From keyboard\nYour choice: ";
    cin >> choice;

    if (choice == 1) {
        matrix.loadFromFile("matrix.txt");
    }
    else {
        matrix.inputFromUser();
    }

    cout << "\nOriginal Matrix:\n";
    matrix.displayMatrix();

    int numberToSubtract;
    cout << "Enter a number to subtract from the diagonal: ";
    cin >> numberToSubtract;

    cout << "\nModified Matrix:\n";
    matrix.subtractFromDiagonal(numberToSubtract);

    return 0;
}
