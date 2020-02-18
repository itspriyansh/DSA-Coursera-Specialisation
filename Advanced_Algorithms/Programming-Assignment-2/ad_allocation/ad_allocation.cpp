#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdio>
#include <cmath>
#include <iomanip>
using namespace std;

typedef vector<vector<long double>> matrix;
const long double EPS = std::numeric_limits<long double>::epsilon();

inline bool equalZero(long double a){
  return abs(a)<1e-3;
}
inline bool double_equals(long double a, long double b, long double epsilon = 0.001){
    return std::abs(a - b) < epsilon;
}

int solve(matrix& table, vector<int>& values, vector<int>& entry, vector<long double>& c, int count, bool phase){
  int l=table[0].size()-1;
  int n=table.size()-1, m=l-n-count;

  int no=0;
  while(true){
    int enter=-1;
    long double minn = std::numeric_limits<long double>::max();
    for(int i=0;i<l;i++){
      if(table.back()[i]<minn){
        enter=i;
        minn=table.back()[enter];
      }
    }
    if(enter==-1 || minn>=0){
      if((phase&&count<=0) ||(!phase&&equalZero(table.back().back()))) return 0;
      else{
        return -1;
      }
    }

    long double ratio=std::numeric_limits<long double>::max()-1;
    int leave = -1;
    for(int i=0;i<n;i++){
      long double r = table[i].back()/table[i][enter];
      if((table[i][enter]>0 || table[i][enter]<0) && r-ratio < EPS && r>0) {
        ratio = r;
        leave = i;
      }
    }
    if(leave==-1){
      return 1;
    }

    if(values[leave]>=n+m) count--;
    values[leave] = enter;
    entry[enter] = leave;

    long double div=table[leave][enter];
    for(int i=0;i<=l;i++){
      table[leave][i] /= div;
    }
    table[leave][enter]=1;

    for(int i=0;i<=n;i++){
      if(i==leave || table[i][enter]==0) continue;
      div=table[i][enter];
      for(int j=0;j<=l;j++){
        if(j==enter) continue;
        table[i][j] = (table[i][j]-table[leave][j]*div);
      }
      table[i][enter] = 0;
    }
  }
  return true;
}

pair<int, vector<long double>> allocate_ads(
    int n, 
    int m, 
    matrix A, 
    vector<long double> b, 
    vector<long double> c) {

  // Write your code here
  // Matrix Formation
  int artificial = 0;
  vector<int> values(n, -1);
  for(int i=0;i<n;i++){
    if(b[i]<0){
      values[i] = m+n+ artificial++;
    }else values[i] = m+i;
  }
  int count=0, l=n+m+artificial;

  vector<int> entry(l, -1);
  matrix table(n+1, vector<long double>(l+1));
  for(int i=0;i<n;i++){
    int mul=1;
    if(b[i]<0){
      mul=-1;
      table[i][m+n+count++]=1;
    }
    table[i][m+i] = mul;
    table[i].back() = mul*b[i];
    for(int j=0;j<m;j++){
      if(A[i][j]==0) table[i][j] = A[i][j];
      else table[i][j] = mul*A[i][j];
    }
  }

  for(int i=0;i<=l;i++){
    if(i>=m+n && i<l) table.back()[i] = 1;
    for(count=0;count<n;count++){
      if(values[count]>=m+n) table.back()[i] -= table[count][i];
    }
  }

  count = artificial;
  int feasible = solve(table, values, entry, c, count, false);

  if(feasible!=0) return {feasible, vector<long double>()};

  // Phase 2
  for(int i=0;i<=l;i++){
    if(i<m) table.back()[i] -= c[i];
    for(int j=0;j<n;j++){
      if(values[j]<m){
        table.back()[i] += (c[values[j]]*table[j][i]);
      }
    }
  }

  for(int i=0;i<=n;i++){
    table[i].erase(table[i].begin()+n+m, table[i].end()-1);
  }
  l-=artificial;
  feasible = solve(table, values, entry, c, 0, true);
  if(feasible!=0) return {feasible, vector<long double>()};

  vector<long double> result(m, 0);
  for (int i = 0; i < m; ++i) {
    long double sum = 0.0;
    int k = 0;
    for (int j = 0; j < n; ++j) {
        if (entry[j] >= 0.0)
            sum += fabs(table[j][i]);
        if (double_equals(table[j][i], 1.0)) {
            k = j;
        }
    }

    result[i] = (sum - 1.0 > EPS) ? 0.0 : table[k].back();
  }

  return {0, result};
}

int main(){
  int n, m;
  cin >> n >> m;
  matrix A(n, vector<long double>(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> A[i][j];
    }
  }
  vector<long double> b(n);
  for (int i = 0; i < n; i++) {
    cin >> b[i];
  }
  vector<long double> c(m);
  for (int i = 0; i < m; i++) {
    cin >> c[i];
  }

  pair<int, vector<long double>> ans = allocate_ads(n, m, A, b, c);

  switch (ans.first) {
    case -1: 
      printf("No solution\n");
      break;
    case 0: 
      printf("Bounded solution\n");
      for (int i = 0; i < m; i++) {
        printf("%.18Lf%c", ans.second[i], " \n"[i + 1 == m]);
      }
      break;
    case 1:
      printf("Infinity\n");
      break;      
  }
  return 0;
}