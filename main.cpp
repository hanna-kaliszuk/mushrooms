#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
const long long MOD = 1000000000;

int main() {
    int n, m, k, g;
    cin >> n >> m >> k >> g;

    if (n < 1 || n > 1000 || m < 1 || m > 1000 || k < 0 || k > 10 || g < 0 || g > n * m) {
        return 1;
    }

    // prevDP[row][collected][dir] = number of ways to reach cell in previously computed column from the 'dir' direction
    //                               with 'collected' mushrooms collected
    // currDP[row][collected[dir] = number of ways to reach cell in currently computed column from the 'dir' direction
    //                              with 'collected' mushrooms collected

    vector<vector<vector<long long>>> prevDP(n, (vector<vector<long long>>(k + 1, vector<long long>(3, 0LL))));
    vector<vector<vector<long long>>> currDP(n, (vector<vector<long long>>(k + 1, vector<long long>(3, 0LL))));

    // hasMushrooms[n][m] = 1 if there is a mushroom in cell (n, m), else 0
    vector<vector<int>> hasMushroom(n, vector<int>(m, 0));

    for (int i = 0; i < g; i++) {
        int a, b;
        cin >> a >> b;

        if (a < 1 || a > n || b < 1 || b > m) {
            return 1;
        }

        hasMushroom[a - 1][b - 1] = 1;
    }

    // initializing the starting position. We start from the left side of the forest.
    int initMushrooms = (k > 0 && hasMushroom[0][0] == 1) ? 1 : 0;
    prevDP[0][initMushrooms][0] = 1LL;
    prevDP[0][initMushrooms][1] = 0LL;
    prevDP[0][initMushrooms][2] = 0LL;

    // setting the first column (col = 0)
    for (int row = 1; row < n; row++) {
        for (int collected = 0; collected <=k; collected++) {
            int newMushrooms = collected + hasMushroom[row][0];
            if (newMushrooms > k) newMushrooms = k;

            // only moves from above
            long long abovePaths = (prevDP[row - 1][collected][0] + prevDP[row - 1][collected][1]) % MOD;
            prevDP[row][newMushrooms][1] = (prevDP[row][newMushrooms][1] + abovePaths) % MOD;
        }
    }

    for (int row = n - 1; row > 0; row--) {
        for (int collected = 0; collected <= k; collected++) {
            int newMushrooms = collected + hasMushroom[row][0];
            if (newMushrooms > k) newMushrooms = k;

            // only moves from below
            if (row < n - 1) {
                long long belowPaths = (prevDP[row + 1][collected][0] + prevDP[row + 1][collected][2]) % MOD;
                prevDP[row][newMushrooms][2] = (prevDP[row][newMushrooms][2] + belowPaths) % MOD;
            }
        }
    }

    // iterating through each column starting from the 1st one, as the 0th has been already initialized
    for (int col = 1; col < m; col++) {
        // clear currDP values
        for (int row_idx = 0; row_idx < n; ++row_idx) {
            for (int k_idx = 0; k_idx <= k; ++k_idx) {
                fill(currDP[row_idx][k_idx].begin(), currDP[row_idx][k_idx].end(), 0LL);
            }
        }

        // moving from left and from above
        for (int row = 0; row < n; row++) {
            for (int collected = 0; collected <= k; collected++) {
                int newMushrooms = collected + hasMushroom[row][col];
                if (newMushrooms > k) newMushrooms = k;

                if (col > 0) { // from the left
                    long long leftPaths = prevDP[row][collected][0] + prevDP[row][collected][1];
                    if (leftPaths >= MOD) leftPaths -= MOD;
                    leftPaths = leftPaths + prevDP[row][collected][2];
                    if (leftPaths >= MOD) leftPaths -= MOD;
                    currDP[row][newMushrooms][0] = currDP[row][newMushrooms][0] + leftPaths;
                    if (currDP[row][newMushrooms][0] >= MOD) currDP[row][newMushrooms][0] -= MOD;
                }

                if (row > 0) { // from above
                    long long abovePaths = currDP[row - 1][collected][0] + currDP[row - 1][collected][1];
                    if (abovePaths >= MOD) abovePaths -= MOD;
                    abovePaths = abovePaths + currDP[row - 1][collected][2];
                    if (abovePaths >= MOD) abovePaths -= MOD;
                    currDP[row][newMushrooms][1] = currDP[row][newMushrooms][1] + abovePaths;
                    if (currDP[row][newMushrooms][1] >= MOD) currDP[row][newMushrooms][1] -= MOD;
                }
            }
        }

        for (int row = n - 1; row >= 0; row--) {
            for (int collected = 0; collected <= k; collected++) {
                int newMushrooms = collected + hasMushroom[row][col];
                if (newMushrooms > k) newMushrooms = k;

                if (row < n - 1) {
                    long long belowPaths = currDP[row + 1][collected][0] + currDP[row + 1][collected][2];
                    if (belowPaths >= MOD) belowPaths -= MOD;
                    currDP[row][newMushrooms][2] = currDP[row][newMushrooms][2] + belowPaths;
                    if (currDP[row][newMushrooms][2] >= MOD) currDP[row][newMushrooms][2] -= MOD;
                }
            }
        }

        swap(prevDP, currDP);
    }

    long long result = 0LL;

    for (int dir = 0; dir < 3; dir++) {
        result += prevDP[n - 1][k][dir];
        if (result >= MOD) result -= MOD;
    }

    cout << result << endl;
    return 0;
}