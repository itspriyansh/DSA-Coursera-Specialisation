#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

string BWT(const string& text) {
  string result = "";
  // write your code here
  vector<string> list(text.size());
  for(int i=0;i<text.size();i++){
  	list[i] = text.substr(i) + text.substr(0,i);
  }sort(list.begin(), list.end());
  for(int i=0;i<list.size();i++) result += list[i][text.size()-1];
  return result;
}

int main() {
  string text;
  cin >> text;
  cout << BWT(text) << endl;
  return 0;
}