#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> optimal_sequence(int n) {
  vector<int> sequence;
  vector<int> minStep(n+1);
  minStep[0] = 0;
  minStep[1] = 0;
  for(int i=2;i<=n;i++){
    int steps = INT8_MAX;
    if(i%3==0)
      steps = min(steps, minStep[i/3]+1);
    if(i%2==0)
      steps = min(steps, minStep[i/2]+1);
    minStep[i] = min(steps, minStep[i-1]+1);
  }
  for(int i=n;i>0;i--){
    sequence.push_back(i);
    int c1 = INT8_MAX, c2 = INT8_MAX, c3;
    if(i%3==0)
      c1 = minStep[i/3];
    if(i%2==0)
      c2 = minStep[i/2];
    c3 = minStep[i-1];
    if(c1 == min(min(c1, c2), c3)){
      i = i/3 + 1;
    } else if(c2 == min(min(c1, c2), c3)) {
      i = i/2 + 1;
    }
  }
  reverse(sequence.begin(), sequence.end());
  return sequence;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> sequence = optimal_sequence(n);
  std::cout << sequence.size() - 1 << std::endl;
  for (size_t i = 0; i < sequence.size(); ++i) {
    std::cout << sequence[i] << " ";
  }
}
