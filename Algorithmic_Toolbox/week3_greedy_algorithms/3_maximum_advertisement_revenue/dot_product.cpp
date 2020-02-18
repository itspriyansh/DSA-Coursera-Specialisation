#include <algorithm>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long max_dot_product(vector<int> a, vector<int> b) {
  // write your code here
  int l = a.size();
  for(int i=0;i<l;i++){
    for(int j=i+1;j<l;j++){
      if(a[i]<a[j])
        swap(a[i],a[j]);
    }
  }
  for(int i=0;i<l;i++){
    for(int j=i+1;j<l;j++){
      if(b[i]<b[j])
        swap(b[i],b[j]);
    }
  }
  long long result = 0;
  for (size_t i = 0; i < a.size(); i++) {
    result += ((long long) a[i]) * b[i];
  }
  return result;
}

int main() {
  size_t n;
  std::cin >> n;
  vector<int> a(n), b(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> a[i];
  }
  for (size_t i = 0; i < n; i++) {
    std::cin >> b[i];
  }
  std::cout << max_dot_product(a, b) << std::endl;
}
