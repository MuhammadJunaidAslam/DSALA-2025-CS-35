// MUHAMMAD JUNAID ASLAM
// DSALA-2025-CS-35
// LAB 01 
// Butterfly Pattern

#include <iostream>
using namespace std;

int main() {
    int n = 5;

    // Upper half
    for(int i = 1; i <= n; i++) {
        // left stars
        for(int j = 1; j <= i; j++)
            cout << "*";

        // spaces
        for(int j = 1; j <= 2*(n - i); j++)
            cout << " ";

        // right stars
        for(int j = 1; j <= i; j++)
            cout << "*";

        cout << endl;
    }

    // Lower half
    for(int i = n - 1; i >= 1; i--) {
        // left stars
        for(int j = 1; j <= i; j++)
            cout << "*";

        // spaces
        for(int j = 1; j <= 2*(n - i); j++)
            cout << " ";

        // right stars
        for(int j = 1; j <= i; j++)
            cout << "*";

        cout << endl;
    }

    return 0;
}