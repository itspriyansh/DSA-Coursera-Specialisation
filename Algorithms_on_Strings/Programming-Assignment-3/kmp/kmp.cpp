#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Find all occurrences of the pattern in the text and return a
// vector with all positions in the text (starting from 0) where 
// the pattern starts in the text.
vector<int> find_pattern(const string& pattern, const string& text) {
  vector<int> result;
  // Implement this function yourself
  string S = pattern + '$' + text;
  vector<int> s(S.size());
  s[0] = 0;
  int border = 0;
  for(int i=1;i<S.size();i++){
    while(border>0 && S[border]!=S[i])
      border = s[border-1];
    if(S[border] == S[i]) border += 1;
    else border = 0;
    s[i] = border;
  }
  // for(int i=0;i<s.size();i++) cout<<s[i]<<" ";
  // cout<<endl;
  for(int i=2*pattern.size();i<S.size();i++){
    if(s[i] == pattern.size())
      result.push_back(i-2*pattern.size());
  }
  return result;
}

int main() {
  string pattern, text;
  cin >> pattern;
  cin >> text;
  vector<int> result = find_pattern(pattern, text);
  for (int i = 0; i < result.size(); ++i) {
    printf("%d ", result[i]);
  }
  printf("\n");
  return 0;
}
