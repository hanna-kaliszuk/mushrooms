#include <iostream>
#include <vector>

using namespace std;

// constants
const long long MOD = 1000000000;

int main() {
   int n, m, k , g;
   cin >> n >> m >> k >> g;

   // create a 2D bool array to mark mushrooms' positions
   vector<vector<int>> hasMushroom(n, vector<int>(m, 0));

   for (int i = 0; i < g; i++) {
      int a, b;
      cin >> a >> b;
      hasMushroom[a - 1][b - 1] = 1;
   }

   // create a 4D DP array initiated with 0
   // DP[i][j][col][dir] = number of ways to reach cell (i, j) coming from direction 'dir' with 'col' mushrooms collected
   // dir: 0 = from left
   //      1 = from above
   //      2 = from below
   // if >= k mushrooms collected, we consider it as k mushrooms collected

   // DP[i][i][col][dir] =
   //   if dir == 0: DP[i][j][newCol][0] = DP[i][j - 1][ALL COLS][ALL 3 DIRECTIONS]
   //   if dir == 1: DP[i][j][newCol][1] = DP[i - 1][j][ALL COLS][ALL DIRECTIONS EXCEPT 2]
   //   if dir == 2: DP[i][j][newCol][2] = DP[i + 1][j][ALL COLS][ALL DIRECTIONS EXCEPT 1]

   // let's assume that we enter the forest from the left side => DP[0][0][hasMushroom[0][0]][0] = 1
   //                                                             DP[0][0][hasMushroom[0][0]][1] = 0;
   //                                                             DP[0][0][hasMushroom[0][0]][2] = 0;

   vector<vector<vector<vector<long long>>>> DP(
      n,vector<vector<vector<long long>>>(m,vector<vector<long long>>(k + 1,vector<long long>(3, 0LL))));

   int initMushrooms = (k > 0 && hasMushroom[0][0] == 1) ? 1 : 0;
   DP[0][0][initMushrooms][0] = 1LL;
   DP[0][0][initMushrooms][1] = 0LL;
   DP[0][0][initMushrooms][2] = 0LL;

   for (int column = 0; column < m; column++) {
      for (int row = 0; row < n; row ++) {
         // it's the first case when we calculate only the moves from the left and from the above
         if (row == 0 && column == 0) continue; // skip the starting cell
         for (int collected = 0; collected <= k; collected++) {
            // we calculate how many mushrooms we have in the current position
            int newMushrooms = collected + hasMushroom[row][column];
            if (newMushrooms > k) newMushrooms = k;

            // from the left (if possible)
            if (column > 0) {
               long long leftPaths = (DP[row][column - 1][collected][0] + DP[row][column - 1][collected][1]) % MOD;
               leftPaths = (leftPaths + DP[row][column - 1][collected][2]) % MOD;
               DP[row][column][newMushrooms][0] = (DP[row][column][newMushrooms][0] + leftPaths) % MOD;
            }

            // from above (if possible)
            if (row > 0) {
               long long abovePaths = (DP[row - 1][column][collected][0] + DP[row - 1][column][collected][1]) % MOD;
               DP[row][column][newMushrooms][1] = (DP[row][column][newMushrooms][1] + abovePaths) % MOD;
            }
         }
      }

      for (int row = n - 1; row >= 0; row--) {
         // it's the second case when we calculate only the moves from below as the cells have already been calculated
         if (row == 0 && column == 0) continue; // skip the starting cell

         for (int collected = 0; collected <= k; collected++) {
            int newMushrooms = collected + hasMushroom[row][column];
            if (newMushrooms > k) newMushrooms = k;

            // from below (if possible)
            if (row < n - 1) {
               long long belowPaths = (DP[row + 1][column][collected][0] + DP[row + 1][column][collected][2]) % MOD;
               DP[row][column][newMushrooms][2] = (DP[row][column][newMushrooms][2] + belowPaths) % MOD;
            }
         }
      }
   }

   long long result = 0LL;
   for (int dir = 0; dir < 3; dir++) {
      result = (result + DP[n - 1][m - 1][k][dir]) % MOD;
   }
   cout << result << endl;
   return 0;
}