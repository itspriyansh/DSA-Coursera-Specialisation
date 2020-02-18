#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

double distance(int x1, int y1, int x2, int y2){
  return sqrt(pow((x2-x1), 2) + pow((y2-y1), 2));
}

double minimum_distance(vector<int> x, vector<int> y) {
  vector<double> cost(x.size(), numeric_limits<double>::max());
  vector<bool> processed(x.size(), false);
  cost[0] = 0;
  for(int i=1;i<cost.size();i++){
    cost[i] = distance(x[0], y[0], x[i], y[i]);
  }
  processed[0] = true;
  int remain = x.size()-1;
  while(remain){
    double m = numeric_limits<double>::max();
    int index = -1;
    for(int i=0;i<cost.size();i++){
      if(!processed[i] && cost[i]<m){
        index = i;
        m = cost[i];
      }
    }
    if(index!=-1){
      remain--;
      processed[index] = true;
      for(int i=0;i<cost.size();i++){
        if(!processed[i] && cost[i] > distance(x[index], y[index], x[i], y[i]))
          cost[i] = distance(x[index], y[index], x[i], y[i]);
      }
    }
  }
  double result = 0.;
  for(int i=0;i<cost.size();i++)
    result += cost[i];
  //write your code here
  return result;
} 

int main() {
  size_t n;
  std::cin >> n;
  vector<int> x(n), y(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
  }
  std::cout << std::setprecision(10) << minimum_distance(x, y) << std::endl;
}
