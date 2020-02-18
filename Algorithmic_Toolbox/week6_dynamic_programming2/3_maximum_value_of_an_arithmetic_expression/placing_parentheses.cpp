#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>

using namespace std;

long long eval(long long a, long long b, char op) {
  if (op == '*') {
    return a * b;
  } else if (op == '+') {
    return a + b;
  } else if (op == '-') {
    return a - b;
  } else {
    assert(0);
  }
}

void minMax(const string &expr, vector<vector<long long>>&m, vector<vector<long long>>&M, int i, int j){
  long long tmin = INT64_MAX, tmax = INT64_MIN;
  for(int k=i;k<j;k++){
    long long a = eval(m[i][k], m[k+1][j], expr[2*k-1]);
    long long b = eval(m[i][k], M[k+1][j], expr[2*k-1]);
    long long c = eval(M[i][k], m[k+1][j], expr[2*k-1]);
    long long d = eval(M[i][k], M[k+1][j], expr[2*k-1]);
    tmax = max(max(tmax,max(a,b)), max(c,d));
    tmin = min(min(tmin,min(a,b)), min(c,d));
  }
  m[i][j] = tmin;
  M[i][j] = tmax;
}

long long get_maximum_value(const string &exp) {
  //write your code here
  int n = (exp.size()+1)/2;
  vector<vector<long long>> M(n+1, vector<long long>(n+1)), m(n+1, vector<long long>(n+1));
  for(int i=1;i<=n;i++){
    M[i][i] = exp[i*2-2]-48;
    m[i][i] = M[i][i];
  }
  for(int s=1;s<n;s++){
    for(int i=1;i<=n-s;i++){
      int j=i+s;
      minMax(exp, m, M, i, j);
    }
  }
  return M[1][n];
}

int main() {
  string s;
  std::cin >> s;
  std::cout << get_maximum_value(s) << '\n';
}
