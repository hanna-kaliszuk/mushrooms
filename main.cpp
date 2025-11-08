#include <iostream>
#include <vector>

using namespace std;

// constants
const long long MOD = 1000000000;
const int MAX_N = 1000;
const int MAX_M = 1000;
const int MAX_K = 10;


int main() {
   int n, m, k , g;
   cin >> n >> m >> k >> g;

   // create a 2D bool array to mark mashrooms' positions
   vector<vector<int>> hasMushroom(n, vector<int>(m, 0));

   for (int i = 0; i < g; i++) {
      int a, b;
      cin >> a >> b;
      hasMushroom[a - 1][b - 1] = 1;
   }

   // create a 4D DP array iniciated with 0
   // DP[i][j][col][dir] = number of ways to reach cell (i, j) coming from direction 'dir' with 'col' mushrooms collected
   // dir: 0 = from left
   //      1 = from above
   //      2 = from below
   // if >= k mushrooms collected, we consider it as k mushrooms collected

   vector<vector<vector<vector<long long>>>> DP(
      n,vector<vector<vector<long long>>>(m,vector<vector<long long>>(k,vector<long long>(3, 0LL))));



   return 0;
}