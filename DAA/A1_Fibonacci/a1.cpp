#include <iostream>
using namespace std;

// --------------- Recursive Fibonacci -----------------
long long fibonacciRecursive(int n) {
    if (n <= 1)
        return n;
    return fibonacciRecursive(n - 1) + fibonacciRecursive(n - 2);
}

// --------------- Non-Recursive Fibonacci --------------
long long fibonacciNonRecursive(int n) {
    if (n <= 1)
        return n;

    long long prev = 0, curr = 1, next;
    for (int i = 2; i <= n; i++) {
        next = prev + curr;
        prev = curr;
        curr = next;
    }
    return curr;
}

// ------------------- Main Menu Program ----------------
int main() {
    int choice, n;
    while (true) {

        cout << "\n=========== Fibonacci Menu ===========";
        cout << "\n1. Recursive Fibonacci";
        cout << "\n2. Non-Recursive Fibonacci";
        cout << "\n3. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        if (choice == 3) {
            cout << "\nExiting program...\n";
            break;
        }

        cout << "Enter the value of n: ";
        cin >> n;

        switch (choice) {
            case 1:
                cout << "\nRecursive Fibonacci (" << n << ") = "
                     << fibonacciRecursive(n-1) << endl;
                break;

            case 2:
                cout << "\nNon-Recursive Fibonacci (" << n << ") = "
                     << fibonacciNonRecursive(n-1) << endl;
                break;

            default:
                cout << "\nInvalid choice! Please try again.\n";
        }
    }
    return 0;
}
