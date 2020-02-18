#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

using namespace std;

int partition2(vector<int> &a, int l, int r) {
  int x = a[l];
  int j = l;
  for (int i = l + 1; i <= r; i++) {
    if (a[i] <= x) {
      j++;
      swap(a[i], a[j]);
    }
  }
  swap(a[l], a[j]);
  return j;
}

void partition3(vector<int> &a, int l, int r, int &m1, int &m2){
  m1 = l;
  m2 = l;
  int x = a[l];
  for(size_t i=l+1;i<r;i++){
    if(a[i]<x){
      swap(a[i], a[++m2]);
    }else if(a[i]==x){
      swap(a[++m1], a[++m2]);
      if(m2!=i)
        swap(a[m1], a[i]);
    }
  }
  for(size_t i=l;i<=m2;i++){
    if(i<m2+l-m1)
      a[i]=a[m1+i+1-l];
    else
      a[i]=x;
  }
  m1=m2+l-m1;
}

void randomized_quick_sort(vector<int> &a, int l, int r) {
  if (l+1 >= r) {
    return;
  }

  int k = (l+r)/2;
  swap(a[l], a[k]);
  //int m = partition2(a, l, r);
  int m1, m2;
  partition3(a, l, r, m1, m2);

  randomized_quick_sort(a, l, m1);
  randomized_quick_sort(a, m2 + 1, r);
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i];
  }
  randomized_quick_sort(a, 0, n);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cout << a[i] << ' ';
  }
}
