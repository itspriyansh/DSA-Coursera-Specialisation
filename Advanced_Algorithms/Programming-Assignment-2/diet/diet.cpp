#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdio>
#include <cmath>
#include <limits>
using namespace std;

typedef vector<vector<double>> matrix;
const double EPS = 1e-6;
const int PRECISION = 20;
const double neg_inf = numeric_limits<double>::lowest();

typedef std::vector<double> Column;
typedef std::vector<double> Row;
typedef std::vector<Row> Matrix;

struct Equation {
    Equation(const Matrix &a, const Column &b):
        a(a),
        b(b)
    {}

    Matrix a;
    Column b;
};

struct Position {
    Position(int column, int row):
        column(column),
        row(row)
    {}

    int column;
    int row;
};

Equation ReadEquation() {
    int size;
    std::cin >> size;
    Matrix a(size, std::vector <double> (size, 0.0));
    Column b(size, 0.0);
    for (int row = 0; row < size; ++row) {
        for (int column = 0; column < size; ++column)
            std::cin >> a[row][column];
        std::cin >> b[row];
    }
    return Equation(a, b);
}

Position SelectPivotElement(
  const Matrix &a, 
  std::vector <bool> &used_rows, 
  std::vector <bool> &used_columns, bool& feasible) {
    // This algorithm selects the first free element.
    // You'll need to improve it to pass the problem.
    Position pivot_element(0, 0);
    while (used_rows[pivot_element.row])
      ++pivot_element.row;
    while (used_rows[pivot_element.column])
      ++pivot_element.column;
    while(a[pivot_element.row][pivot_element.column]==0 || used_rows[pivot_element.row]){
      ++pivot_element.row;
      if(pivot_element.row+1>used_rows.size()){
        feasible = false;
        break;
      }
    }
    return pivot_element;
}

void SwapLines(Matrix &a, Column &b, std::vector <bool> &used_rows, Position &pivot_element) {
    std::swap(a[pivot_element.column], a[pivot_element.row]);
    std::swap(b[pivot_element.column], b[pivot_element.row]);
    std::swap(used_rows[pivot_element.column], used_rows[pivot_element.row]);
    pivot_element.row = pivot_element.column;
}

void ProcessPivotElement(Matrix &a, Column &b, const Position &pivot_element) {
    // Write your code here
    int k=pivot_element.row;
    for(int i=0;i<a.size();i++){
        if(i==k) continue;
        double f = a[i][k]/a[k][k];
        for(int j=k+1;j<a[i].size();j++){
            a[i][j] -= f*a[k][j];
        }
        b[i] -= f*b[k];
        a[i][k] = 0;
    }
}

void MarkPivotElementUsed(const Position &pivot_element, std::vector <bool> &used_rows, std::vector <bool> &used_columns) {
    used_rows[pivot_element.row] = true;
    used_columns[pivot_element.column] = true;
}

Column SolveEquation(Equation equation, bool& feasible) {
    Matrix &a = equation.a;
    Column &b = equation.b;
    int size = a.size();

    std::vector <bool> used_columns(size, false);
    std::vector <bool> used_rows(size, false);
    for (int step = 0; step < size; ++step) {
        Position pivot_element = SelectPivotElement(a, used_rows, used_columns, feasible);
        if(!feasible) return b;
        SwapLines(a, b, used_rows, pivot_element);
        ProcessPivotElement(a, b, pivot_element);
        MarkPivotElementUsed(pivot_element, used_rows, used_columns);
    }
    for(int i=0;i<b.size();i++){
      if(b[i]!=0)
        b[i] /= a[i][i];
    }

    return b;
}

void appendEquations(int n, int m, matrix& A, vector<double>& b){
  for(int i=0;i<m;i++){
    vector<double> temp(m, 0);
    temp[i] = -1;
    A.push_back(temp);
    b.push_back(0);
  }
  A.push_back(vector<double>(m,1));
  b.push_back(1e9);
}

bool check(Column& sol, Matrix& a, vector<double>& b, vector<double>& c, double& best, int& status, bool last){
  // for(int i=0;i<sol.size();i++){
  //   if(sol[i]<1e-3) return false;
  // }
  for(int i=0;i<a.size();i++){
    double r = 0;
    for(int j=0;j<a[i].size();j++){
      r += a[i][j]*sol[j];
    }
    if(r>b[i]+1e-3) return false;
  }
  double r = 0;
  for(int i=0;i<c.size();i++){
    r += sol[i]*c[i];
  }
  if(best<r){
    best=r;
    if(last) status = 1;
    else status = 0;
    return true;
  }
  return false;
}

pair<int, vector<double>> solve_diet_problem(
    int n, 
    int m, 
    matrix A, 
    vector<double> b, 
    vector<double> c) {

  // Write your code here
  Column result;
  appendEquations(n, m, A, b);

  // cout<<"Matrix: "<<endl;
  // for(int i=0;i<A.size();i++){
  //   for(int j=0;j<A[i].size();j++){
  //     cout<<A[i][j]<<" ";
  //   }cout<<b[i]<<endl;
  // }

  double bestCount=neg_inf;
  int l = m+n+1, status=-1;
  int64_t set = pow(2,l);
  for(int i=0;i<set;i++){
    Matrix a1; Column b1;
    for(int j=0;j<l;j++){
      if(i&(1 << j)){
        a1.push_back(A[j]);
        b1.push_back(b[j]);
      }
    }

    if(a1.size()!=m) continue;
    bool feasible=true;
    Column sol = SolveEquation(Equation(a1, b1), feasible);

    // cout<<"Solution: ";
    // for(int i=0;i<sol.size();i++){
    //   cout<<sol[i]<<" ";
    // }cout<<(feasible?"Feasible":"Unfeasible")<<endl;

    if(!feasible) continue;
    bool lastEquation = (b1.back()==b.back());
    if(check(sol, A, b, c, bestCount, status, lastEquation)){
      result = sol;
      // cout<<"Solution: ";
      // for(int i=0;i<sol.size();i++){
      //   cout<<sol[i]<<" ";
      // }cout<<(feasible?"Feasible":"Unfeasible")<<endl;
    }
  }
  return {status, result};
}

int main(){
  int n, m;
  cin >> n >> m;
  matrix A(n, vector<double>(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> A[i][j];
    }
  }
  vector<double> b(n);
  for (int i = 0; i < n; i++) {
    cin >> b[i];
  }
  vector<double> c(m);
  for (int i = 0; i < m; i++) {
    cin >> c[i];
  }

  pair<int, vector<double>> ans = solve_diet_problem(n, m, A, b, c);

  switch (ans.first) {
    case -1: 
      printf("No solution\n");
      break;
    case 0: 
      printf("Bounded solution\n");
      for (int i = 0; i < m; i++) {
        printf("%.18f%c", ans.second[i], " \n"[i + 1 == m]);
      }
      break;
    case 1:
      printf("Infinity\n");
      break;      
  }
  return 0;
}
