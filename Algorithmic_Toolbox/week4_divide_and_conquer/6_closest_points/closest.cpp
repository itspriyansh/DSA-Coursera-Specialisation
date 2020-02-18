#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>

using namespace std;

double distance(pair<int, int> a, pair<int, int> b){
  return sqrt(pow((a.first-b.first), 2) + pow((a.second-b.second), 2));
}

double smallCase(pair<int, int> a[], int n){
  double m = INT16_MAX;
  for(size_t i=0;i<n;i++){
    for(size_t j=i+1;j<n;j++){
      m = min(m, distance(a[i], a[j]));
    }
  }
  return m;
}

double centerStripMin(pair<int, int> a[], int mid, int n, double d){
  vector<pair<int, int>> stripMin;
  int midPoint = (a[mid-1].first+a[mid].first)/2;
  pair<int, int> temp;
  for(size_t i=0;i<n;i++){
    if(abs(a[i].first - midPoint)<=d){
      temp.first = a[i].second;
      temp.second = a[i].first;
      stripMin.push_back(temp);
    }
  }
  sort(stripMin.begin(), stripMin.end());
  double result = d;
  for(size_t i=0;i<stripMin.size();i++){
    for(size_t j=i+1;j<min(i+8, stripMin.size());j++){
      if(abs(stripMin[i].first - stripMin[j].first) <= d)
        result = min(result, distance(stripMin[i], stripMin[j]));
    }
  }
  return result;
}

double closest(pair<int, int> a[], int n){
  if(n<=3)
    return smallCase(a, n);
  int mid = n/2;
  double dl = closest(a, mid);
  double dr = closest(a+mid, n-mid);
  double d = min(dl, dr);
  double centerStrip = centerStripMin(a, mid, n, d);
  return min(d, centerStrip);
}

double minimal_distance(vector<int> x, vector<int> y) {
  //write your code here
  int n = x.size();
  pair<int, int> points[n];
  for(size_t i=0;i<n;i++){
    points[i].first = x[i];
    points[i].second = y[i];
  }
  sort(points, points+n);
  return closest(points, n);
}

double minimal_distance_naive(vector<int> x, vector<int> y){
  double d = INT16_MAX;
  for(size_t i=0;i<x.size();i++){
    for(size_t j=i+1;j<x.size();j++){
      double distance = sqrt(pow((x[j]-x[i]), 2)+pow((y[j]-y[i]), 2));
      d = min(distance, d);
    }
  }
  return d;
}

void stress_test(){
  int n;
  while(true){
    n = rand()%50 + 2;
    vector<int> x(n), y(n);
    for(size_t i=0;i<n;i++){
      x[i] = rand()%30;
      y[i] = rand()%30;
      cout<<"("<<x[i]<<", "<<y[i]<<"), ";
    }cout<<endl;
    double result1 = minimal_distance_naive(x, y);
    double result2 = minimal_distance(x, y);
    if(result1 == result2)
      cout<<"OK"<<endl;
    else{
      cout<<"Wrong Answer: "<<result1<<' '<<result2<<endl;
      break;
    }
  }
}

int main() {
  // stress_test();
  size_t n;
  std::cin >> n;
  vector<int> x(n);
  vector<int> y(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
  }
  std::cout << std::fixed;
  std::cout << std::setprecision(9) << minimal_distance(x, y) << "\n";
}
