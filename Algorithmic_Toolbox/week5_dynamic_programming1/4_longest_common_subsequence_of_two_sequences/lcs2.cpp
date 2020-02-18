#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int lcs2(vector<int> &a, vector<int> &b) {
  //write your code here
  int m = a.size(), n = b.size();
  int lcs[m+1][n+1];
  for(int i=0;i<=m;i++){
    for(int j=0;j<=n;j++){
      if(i==0 || j==0)
        lcs[i][j] = 0;
      else if(a[i-1] == b[j-1])
        lcs[i][j] = lcs[i-1][j-1] + 1;
      else
        lcs[i][j] = max(lcs[i-1][j], lcs[i][j-1]);
    }
  }
  return lcs[m][n];
}

int main() {
  size_t n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  size_t m;
  std::cin >> m;
  vector<int> b(m);
  for (size_t i = 0; i < m; i++) {
    std::cin >> b[i];
  }

  std::cout << lcs2(a, b) << std::endl;
}
