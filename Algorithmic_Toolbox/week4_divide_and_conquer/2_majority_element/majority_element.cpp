#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void merge(vector<int> &a, int low, int mid, int high){
  vector<int> result;
  int i=low, j=mid+1;
  while(i<=mid && j<=high){
    if(a[i]<=a[j])
      result.push_back(a[i++]);
    else
      result.push_back(a[j++]);
  }
  while(i<=mid)
    result.push_back(a[i++]);
  while(j<=high)
    result.push_back(a[j++]);
  for(size_t i=0;i<result.size();i++)
    a[low+i]=result[i];
}

void merge_sort(vector<int> &a, int low, int high){
  if(low==high)
    return;
  int mid = (high+low-1)/2;
  merge_sort(a, low, mid);
  merge_sort(a, mid+1, high);
  merge(a, low ,mid, high);
}

int get_majority_element(vector<int> &a, int left, int right) {
  if (left == right) return -1;
  merge_sort(a, left, right-1);
  //write your code here
  int count=1, current=a[left];
  for(int i=left+1; i<right; i++){
    if(a[i]==current)
      count++;
    else{
      count=1;
      current=a[i];
    }
    if(count>(right+left)/2){
      return 1;
    }
  }
  return -1;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i];
  }
  std::cout << (get_majority_element(a, 0, a.size()) != -1) << '\n';
}
