#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long merge(vector<int> &a, int low, int mid, int high){
  vector<int> result;
  int i=low, j=mid;
  long long count=0;
  while(i<mid && j<high){
    if(a[i]<=a[j]){
      result.push_back(a[i++]);
    }
    else{
      result.push_back(a[j++]);
      count+=mid-i;
    }
  }
  while(i<mid){
    result.push_back(a[i++]);
  }
  while(j<high){
    result.push_back(a[j++]);
  }
  for(size_t i=0;i<result.size();i++){
    a[low+i]=result[i];
  }
  return count;
}

void get_number_of_inversions(vector<int> &a, size_t left, size_t right, long long &count) {
  if(left+1 >= right)
    return;
  int mid = (left+right)/2;
  get_number_of_inversions(a, left, mid, count);
  get_number_of_inversions(a, mid, right, count);
  count+=merge(a, left, mid, right);
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); i++) {
    std::cin >> a[i];
  }
  long long count = 0;
  get_number_of_inversions(a, 0, a.size(), count);
  std::cout << count << '\n';
}
