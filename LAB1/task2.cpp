// MUHAMMAD JUNAID ASLAM
// DSALA-2025-CS-35
// LAB 01 
// 2D Array Spiral Fill

#include <iostream>
using namespace std;

int main() {
    int arr[4][5];
    int value = 1;

    // Fill first row left to right
    for(int j = 0; j < 5; j++) arr[0][j] = value++;

    // Fill last column top to bottom
    for(int i = 1; i < 3; i++) arr[i][4] = value++;

    // Fill last row right to left
    for(int j = 4; j >= 0; j--) arr[3][j] = value++;

    // Fill first column bottom to top
    for(int i = 2; i >= 1; i--) arr[i][0] = value++;

    // Fill middle inner row left to right
    for(int j = 1; j < 4; j++) arr[1][j] = value++;

    // Fill middle inner row right to left
    for(int j = 3; j > 0; j--) arr[2][j] = value++;

    // Print the array
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 5; j++)
            cout << arr[i][j] << " ";
        cout << endl;
    }

    return 0;
}