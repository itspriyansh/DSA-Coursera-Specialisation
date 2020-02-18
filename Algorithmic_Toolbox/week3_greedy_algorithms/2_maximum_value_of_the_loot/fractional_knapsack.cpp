#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

double get_optimal_value(int capacity, vector<int> weights, vector<int> values) {
  int n = weights.size();
  double value = 0.0;
  // write your code here
  vector<int> sorted(n);
  for(int i=0;i<n;i++)
    sorted[i]=i;
  for(int i=0;i<n;i++){
    for(int j=i+1;j<n;j++){
      if((double)values[sorted[j]]/weights[sorted[j]] > (double)values[sorted[i]]/weights[sorted[i]])
        swap(sorted[i], sorted[j]);
    }
  }
  for(int i=0;i<n;i++){
    int index=sorted[i];
    if(capacity==0)
      return value;
    int amount = min(capacity, weights[index]);
    value += (double)amount*(double)values[index]/(double)weights[index];
    capacity -= amount;
  }
  return value;
}

int main() {
  int n;
  int capacity;
  std::cin >> n >> capacity;
  vector<int> values(n);
  vector<int> weights(n);
  for (int i = 0; i < n; i++) {
    std::cin >> values[i] >> weights[i];
  }

  double optimal_value = get_optimal_value(capacity, weights, values);

  std::cout.precision(10);
  std::cout << optimal_value << std::endl;  
  return 0;
}
