#include <iostream>
#include <vector>
#include <cmath>

using std::vector;

vector<int> optimal_summands(int n) {
  vector<int> summands;
  //write your code here
  for(size_t i=1;n!=0;i++){
    if(n>2*i || n==i){
      n-=i;
      summands.push_back(i);
    }
  }
  return summands;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> summands = optimal_summands(n);
  std::cout << summands.size() << '\n';
  for (size_t i = 0; i < summands.size(); ++i) {
    std::cout << summands[i] << ' ';
  }
}
