#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int lcs3(vector<int> &a, vector<int> &b, vector<int> &c) {
  //write your code here
  int m = a.size(), n = b.size(), o = c.size();
  int lcs[m+1][n+1][o+1];
  for(int i=0;i<=m;i++){
    for(int j=0;j<=n;j++){
      for(int k=0;k<=o;k++){
        if(i==0 || j==0 || k==0)
          lcs[i][j][k] = 0;
        else if(a[i-1] == b[j-1] && b[j-1] == c[k-1])
          lcs[i][j][k] = lcs[i-1][j-1][k-1] + 1;
        else
          lcs[i][j][k] = max(max(lcs[i-1][j][k], lcs[i][j-1][k]), lcs[i][j][k-1]);
      }
    }
  }
  return lcs[m][n][o];
}

int main() {
  size_t an;
  std::cin >> an;
  vector<int> a(an);
  for (size_t i = 0; i < an; i++) {
    std::cin >> a[i];
  }
  size_t bn;
  std::cin >> bn;
  vector<int> b(bn);
  for (size_t i = 0; i < bn; i++) {
    std::cin >> b[i];
  }
  size_t cn;
  std::cin >> cn;
  vector<int> c(cn);
  for (size_t i = 0; i < cn; i++) {
    std::cin >> c[i];
  }
  std::cout << lcs3(a, b, c) << std::endl;
}
