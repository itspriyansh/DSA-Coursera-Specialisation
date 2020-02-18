#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int optimal_weight(int W, const vector<int> &w) {
  //write your code here
  int n = w.size();
  vector<vector<int>> value(W+1, vector<int>(n+1));
  for(int i=0;i<=n;i++){
    for(int j=0;j<=W;j++){
      if(i==0 || j==0)
        value[j][i] = 0;
      else if(j>=w[i-1])
        value[j][i] = max(value[j-w[i-1]][i-1]+w[i-1], value[j][i-1]);
      else
        value[j][i] = value[j][i-1];
    }
  }
  return value[W][n];
}

int main() {
  int n, W;
  std::cin >> W >> n;
  vector<int> w(n);
  for (int i = 0; i < n; i++) {
    std::cin >> w[i];
  }
  std::cout << optimal_weight(W, w) << '\n';
}
