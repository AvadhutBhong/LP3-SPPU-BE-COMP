#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// UPDATED SAFE CHECK (checks against ALL placed queens)
bool isSafe(int row, int col, vector<int> &board) {
    for (int r = 0; r < board.size(); r++) {
        if (board[r] != -1) { // If a queen exists on row r
            int c = board[r];

            // Column conflict or diagonal conflict
            if (c == col || abs(c - col) == abs(r - row))
                return false;
        }
    }
    return true;
}

// Backtracking function to store ALL solutions
void solveNQueens(int row, int n, vector<int> &board, vector<vector<int>> &solutions) {

    // If reached end, store the valid configuration
    if (row == n) {
        solutions.push_back(board);
        return;
    }

    // If user already fixed queen in this row, skip placing new queen
    if (board[row] != -1) {
        solveNQueens(row + 1, n, board, solutions);
        return;
    }

    // Try placing queen in all possible columns in current row
    for (int col = 0; col < n; col++) {
        if (isSafe(row, col, board)) {
            board[row] = col;
            solveNQueens(row + 1, n, board, solutions);
            board[row] = -1; // Backtrack
        }
    }
}

// Print solution in chessboard form
void printBoard(const vector<int> &board, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << (board[i] == j ? "Q " : ". ");
        cout << endl;
    }
}

int main() {

    while (true) {
        cout << "\n========== N-QUEENS MENU ==========\n";
        cout << "1. Solve N-Queens (Fixed queen position)\n";
        cout << "2. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        if (choice == 2) break;

        int n, fixedRow, fixedCol;
        cout << "\nEnter number of queens (N): ";
        cin >> n;

        if (n <= 3) {
            cout << "❌ No valid solutions for N <= 3.\n";
            continue;
        }

        cout << "Enter fixed queen position:\n";
        cout << "Row (0 to " << n - 1 << "): ";
        cin >> fixedRow;
        cout << "Column (0 to " << n - 1 << "): ";
        cin >> fixedCol;

        if (fixedRow < 0 || fixedRow >= n || fixedCol < 0 || fixedCol >= n) {
            cout << "❌ Invalid queen position.\n";
            continue;
        }

        vector<int> board(n, -1);
        board[fixedRow] = fixedCol;

        vector<vector<int>> solutions;

        solveNQueens(0, n, board, solutions);

        if (solutions.empty()) {
            cout << "\n❌ No solution exists with queen at (" << fixedRow << ", " << fixedCol << ")\n";
        } else {
            cout << "\n✅ Total Solutions Found: " << solutions.size() << "\n";

            for (int s = 0; s < solutions.size(); s++) {
                cout << "\nSolution " << s + 1 << ":\n";
                printBoard(solutions[s], n);
            }

            cout << "\nTime Complexity: O(N!)";
            cout << "\nSpace Complexity: O(N)\n";
        }
    }

    return 0;
}
