//
// Created by L on 25-10-22.
//
#include <iostream>
using namespace std;

bool Find(int* matrix, int row, int col, int num) {
     // 通过右上角的值的比较，来确定是否row col 的变动
    while (row >= 0 && col >= 0) {
        if (matrix[row * col + col] == num) {
            return true;
        }
        else if (matrix[row * col + col] > num) {
            col--;
        }
        else {
            row++;
        }
    }

    return false;
};

int main() {
    // cout << "Hello World!" << endl;
    int matrix[] = {1, 2, 8, 9, 2, 4, 9, 12, 4, 7, 10, 13, 6, 8, 11, 15};
    int row = 4;
    int col = 3;
    cout << Find(matrix, row, col, 4) << endl;

}