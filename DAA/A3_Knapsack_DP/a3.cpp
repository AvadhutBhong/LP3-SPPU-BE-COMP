#include <iostream>
#include <vector>
using namespace std;

// Function to solve 0/1 Knapsack using Dynamic Programming
int knapsack(int W, vector<int>& wt, vector<int>& val, int n, vector<vector<int>>& dp) {
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {

            if (i == 0 || w == 0)
                dp[i][w] = 0; // Base case

            else if (wt[i - 1] <= w)
                dp[i][w] = max(
                    val[i - 1] + dp[i - 1][w - wt[i - 1]],
                    dp[i - 1][w]
                );

            else
                dp[i][w] = dp[i - 1][w];
        }
    }

    return dp[n][W]; // Max value achievable with given capacity
}

// Function to print selected items
void printSelectedItems(int W, vector<int>& wt, vector<int>& val, vector<vector<int>>& dp) {
    int n = val.size();
    int w = W;

    cout << "\nItems included:\n";

    for (int i = n; i > 0; i--) {
        if (dp[i][w] != dp[i - 1][w]) {
            cout << "Item " << i << " (Value = " << val[i - 1] << ", Weight = " << wt[i - 1] << ")\n";
            w -= wt[i - 1];
        }
    }
}

int main() {

    int n, W;
    cout << "Enter number of items: ";
    cin >> n;

    vector<int> val(n), wt(n);

    cout << "Enter value and weight of each item:\n";
    for (int i = 0; i < n; i++)
        cin >> val[i] >> wt[i];

    cout << "Enter knapsack capacity: ";
    cin >> W;

    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0)); // DP table

    int maxValue = knapsack(W, wt, val, n, dp);
    cout << "\nMaximum value in Knapsack = " << maxValue << endl;

    printSelectedItems(W, wt, val, dp);

    return 0;
}
