#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool isGreater(string a, string b){
  string first = a+b;
  string second = b+a;
  return first>second;
}

string largest_number(vector<string> a) {
  //write your code here
  std::stringstream ret;
  while(a.size()>0){
    string maxDigit = a[0];
    for(size_t i=1;i<a.size();i++){
      if(isGreater(a[i], maxDigit))
        maxDigit = a[i];
    }
    ret << maxDigit;
    a.erase(find(a.begin(), a.end(), maxDigit));
  }
  // for (size_t i = 0; i < a.size(); i++) {
  //   ret << a[i];
  // }
  string result;
  ret >> result;
  return result;
}

int main() {
  int n;
  std::cin >> n;
  vector<string> a(n);
  for (size_t i = 0; i < a.size(); i++) {
    std::cin >> a[i];
  }
  std::cout << largest_number(a);
}
