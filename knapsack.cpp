#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Returns the maximum value that can be put in a knapsack of capacity W
int knapSack(int W, const vector<int>& wt, const vector<int>& val, int n) {
    // Create a 2D DP table: dp[number of items + 1][capacity + 1]
    vector<vector<int>> dp(n + 1, vector<int>(W + 1));

    // Build table dp[][] in bottom up manner
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            // Base Case: No items or 0 capacity
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            // If weight of current item is less than or equal to current capacity
            else if (wt[i - 1] <= w)
                dp[i][w] = max(val[i - 1] + dp[i - 1][w - wt[i - 1]], 
                               dp[i - 1][w]);
            else
                // Item too heavy, carry forward previous max value
                dp[i][w] = dp[i - 1][w];
        }
    }
    for(int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            cout << dp[i][w] << " ";
        }
        cout << endl;
    }
    return dp[n][W];
}

int main() {
    int n = 5;             // Number of items
    vector<int> val = {6, 10, 12, 8, 15}; // Item values
    vector<int> wt = {1, 2, 3, 4, 5};    // Item weights
    int W = 10;            // Knapsack capacity

    cout << "Maximum Value: " << knapSack(W, wt, val, n) << endl;
    return 0;
}