#include <iostream>
#include <vector>
using namespace std;

// --------------- Recursive Fibonacci -----------------
long long fibonacciRecursive(int n) {
    if (n <= 1)
        return n;
    return fibonacciRecursive(n - 1) + fibonacciRecursive(n - 2);
}

// --------- Fibonacci using Memoization (DP Top-Down) --------
long long fibonacciMemo(int n, vector<long long>& dp) {
    if (n <= 1)
        return n;

    if (dp[n] != -1)
        return dp[n];           // return already stored result

    dp[n] = fibonacciMemo(n - 1, dp) + fibonacciMemo(n - 2, dp);
    return dp[n];
}

// -------- Fibonacci using Tabulation (DP Bottom-Up) --------
long long fibonacciTabulation(int n) {
    if (n <= 1)
        return n;

    vector<long long> dp(n + 1);
    dp[0] = 0;
    dp[1] = 1;

    for (int i = 2; i <= n; i++)
        dp[i] = dp[i - 1] + dp[i - 2];

    return dp[n];
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
        cout << "\n3. Fibonacci using Memoization (DP Top-Down)";
        cout << "\n4. Fibonacci using Tabulation (DP Bottom-Up)";
        cout << "\n5. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        if (choice == 5) {
            cout << "\nExiting program...\n";
            break;
        }

        cout << "Enter the value of n: ";
        cin >> n;

        switch (choice) {
            case 1:
                cout << "\nRecursive Fibonacci (" << n << ") = "
                     << fibonacciRecursive(n) << endl;
                break;

            case 2:
                cout << "\nNon-Recursive Fibonacci (" << n << ") = "
                     << fibonacciNonRecursive(n) << endl;
                break;

            case 3: {
                vector<long long> dp(n + 1, -1);
                cout << "\nMemoized Fibonacci (" << n << ") = "
                     << fibonacciMemo(n, dp) << endl;
                break;
            }

            case 4:
                cout << "\nTabulation Fibonacci (" << n << ") = "
                     << fibonacciTabulation(n) << endl;
                break;

            default:
                cout << "\nInvalid choice! Please try again.\n";
        }
    }
    return 0;
}
