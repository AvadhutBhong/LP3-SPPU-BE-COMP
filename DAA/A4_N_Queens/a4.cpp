#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Function to check if placing a queen at board[row] = col is safe
bool isSafe(int row, int col, vector<int> &board) {
    for (int prevRow = 0; prevRow < row; prevRow++) {
        int prevCol = board[prevRow];

        // Same column or diagonal conflict
        if (prevCol == col || abs(prevCol - col) == abs(prevRow - row)) {
            return false;
        }
    }
    return true;
}

// Backtracking function to place remaining queens
bool solveNQueens(int row, int n, vector<int> &board) {
    if (row == n) {
        return true; // All queens placed successfully
    }

    for (int col = 0; col < n; col++) {
        if (isSafe(row, col, board)) {
            board[row] = col;

            if (solveNQueens(row + 1, n, board))
                return true; // Stop when first valid solution is found

            board[row] = -1; // Backtrack
        }
    }
    return false;
}

// Function to print the final solution
void printBoard(vector<int> &board, int n) {
    cout << "\nFinal N-Queens board:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << (board[i] == j ? "Q " : ". ");
        }
        cout << endl;
    }
}

int main() {
    int choice;

    while (true) {
        cout << "\n========== N-QUEENS MENU ==========";
        cout << "\n1. Solve N-Queens (first queen fixed)";
        cout << "\n2. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        if (choice == 2) {
            cout << "Exiting program...\n";
            break;
        }

        int n, col;
        cout << "\nEnter the number of queens (N): ";
        cin >> n;

        if (n <= 3) {
            cout << "No solution exists for N <= 3 in N-Queens problem.\n";
            continue;
        }

        cout << "Enter the column index (0 to " << n - 1 << ") for the FIRST queen: ";
        cin >> col;

        if (col < 0 || col >= n) {
            cout << "Invalid column index...\n";
            continue;
        }

        vector<int> board(n, -1);
        board[0] = col; // First queen is fixed by user

        if (solveNQueens(1, n, board)) {
            printBoard(board, n);
            cout << "\nTime Complexity: O(N!)";
            cout << "\nSpace Complexity: O(N)  (due to recursion stack)\n";
        } else {
            cout << "\nNo solution possible when first queen is fixed at this position.\n";
        }
    }
    return 0;
}
