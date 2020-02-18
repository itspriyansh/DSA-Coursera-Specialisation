#include <string>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

typedef map<char, int> edges;
typedef vector<edges> trie;

trie build_trie(vector<string> & patterns) {
  trie t;
  // write your code here
  edges new0;
  t.push_back(new0);
  for(int i=0;i<patterns.size();i++){
    int current = 0;
    for(int j=0;j<patterns[i].size();j++){
      if(t[current].find(patterns[i][j]) != t[current].end()){
        current = t[current][patterns[i][j]];
      }else{
        t[current].insert(pair<char, int>(patterns[i][j], t.size()));
        current = t.size();
        edges temp;
        t.push_back(temp);
      }
    }
  }
  return t;
}

int main() {
  size_t n;
  std::cin >> n;
  vector<string> patterns;
  for (size_t i = 0; i < n; i++) {
    string s;
    std::cin >> s;
    patterns.push_back(s);
  }

  trie t = build_trie(patterns);
  for (size_t i = 0; i < t.size(); ++i) {
    for (const auto & j : t[i]) {
      std::cout << i << "->" << j.second << ":" << j.first << "\n";
    }
  }

  return 0;
}