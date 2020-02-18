#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

// Funciton List for Suffix Array Formation
vector<int> SortCharacters(const string &text){
  vector<int> order(text.size());
  vector<int> count(100, 0);
  for(int i=0;i<text.size();i++)
    count[text[i]-' ']++;
  for(int i=1;i<count.size();i++)
    count[i] += count[i-1];
  for(int i=text.size()-1;i>=0;i--){
    int c = text[i]-' ';
    count[c]--;
    order[count[c]] = i;
  }
  return order;
}
vector<int> ComputeCharClasses(const string& text, const vector<int>& order){
  vector<int> classes(text.size());
  classes[order[0]] = 0;
  for(int i=1;i<classes.size();i++){
    if(text[order[i]]!=text[order[i-1]])
      classes[order[i]] = classes[order[i-1]]+1;
    else
      classes[order[i]] = classes[order[i-1]];
  }
  return classes;
}
vector<int> SortDoubled(const string& text, int l, const vector<int>& order, const vector<int>& classes){
  vector<int> newOrder(order.size());
  vector<int> count(classes.size(), 0);
  for(int i=0;i<classes.size();i++)
    count[classes[i]]++;
  for(int i=1;i<count.size();i++)
    count[i] += count[i-1];
  for(int i=order.size()-1;i>=0;i--){
    int start = (order[i]-l+text.size()) % text.size();
    int cl = classes[start];
    count[cl]--;
    newOrder[count[cl]] = start;
  }
  return newOrder;
}
vector<int> UpdateClasses(const vector<int>& order, vector<int>& classes, int l){
  vector<int> newClasses(order.size());
  newClasses[order[0]] = 0;
  for(int i=1;i<newClasses.size();i++){
    int current = order[i], prev = order[i-1];
    int mid = (current+l)%order.size();
    int midPrev = (prev+l)%order.size();
    if(classes[current]!=classes[prev] || classes[mid]!=classes[midPrev])
      newClasses[order[i]] = newClasses[order[i-1]]+1;
    else
      newClasses[order[i]] = newClasses[order[i-1]];
  }
  return newClasses;
}

// Function List for Burrows Wheeler Implementation
vector<int> BuildSuffixArray(const string& text) {
  vector<int> order;

  // write your code here
  order = SortCharacters(text);
  vector<int> classes = ComputeCharClasses(text, order);
  for(int i=1;i<text.size();i*=2){
    order = SortDoubled(text, i, order, classes);
    classes = UpdateClasses(order, classes, i);
  }
  // for(int i=0;i<order.size();i++) cout<<order[i]<<" ";
  // cout<<endl;
  return order;
}

// int LcpOfSuffixes(const string& text, int i, int j, int equal){
//   int lcp = max(0, equal);
//   while(i+lcp < text.size() && i+lcp < text.size()){
//     if(text[i+lcp] == text[j+lcp]) lcp++;
//     else break;
//   }
//   return lcp;
// }
// vector<int> InvertSuffixArray(const vector<int>& order){
//   vector<int> pos(order.size());
//   for(int i=0;i<pos.size();i++)
//     pos[order[i]] = i;
//   return pos;
// }
// vector<int> ComputeLcpArray(const string& text, const vector<int>& order){
//   vector<int> lcpArray(order.size());
//   int lcp = 0;
//   vector<int> pos = InvertSuffixArray(text, order);
//   int suffix = order[0];
//   for(int i=0;i<text.size();i++){
//     int orderIndex = pos[suffix];
//     if(orderIndex == text.size()-1){
//       lcp = 0;
//       suffix = (suffix+1)%text.size();
//       continue;
//     }
//     int nextSuffix = order[orderIndex+1];
//     lcp = LcpOfSuffixes(text, suffix, nextSuffix, lcp-1);
//     lcpArray[orderIndex] = lcp;
//     suffix = (suffix+1)%text.size();
//   }
//   return lcpArray;
// }

vector<int> FindOccurrences(const string& pattern, const string& text, const vector<int>& suffix_array) {
  vector<int> result;
  // write your code here
  // vector<int> lcpArray = ComputeLcpArray(text, suffix_array);
  int minIndex = 0, maxIndex = text.size();
  while(minIndex < maxIndex){
    int mid = (minIndex+maxIndex)/2;
    // cout<<pattern<<" "<<text.substr(suffix_array[mid],pattern.size())<<endl;
    if(pattern>text.substr(suffix_array[mid],pattern.size()))
      minIndex = mid+1;
    else
      maxIndex = mid;
  }
  int start = minIndex;
  maxIndex = text.size();
  while(minIndex < maxIndex){
    int mid = (minIndex+maxIndex)/2;
    // cout<<pattern<<" "<<text.substr(suffix_array[mid],pattern.size())<<endl;
    if(pattern<text.substr(suffix_array[mid], pattern.size()))
      maxIndex = mid;
    else
      minIndex = mid+1;
  }
  int end = maxIndex;
  for(int i=start;i<end;i++)
    result.push_back(suffix_array[i]);
  return result;
}

int main() {
  char buffer[100001];
  scanf("%s", buffer);
  string text = buffer;
  text += '$';
  vector<int> suffix_array = BuildSuffixArray(text);
  int pattern_count;
  scanf("%d", &pattern_count);
  vector<bool> occurs(text.length(), false);
  for (int pattern_index = 0; pattern_index < pattern_count; ++pattern_index) {
    scanf("%s", buffer);
    string pattern = buffer;
    vector<int> occurrences = FindOccurrences(pattern, text, suffix_array);
    for (int j = 0; j < occurrences.size(); ++j) {
      occurs[occurrences[j]] = true;
    }
  }
  for (int i = 0; i < occurs.size(); ++i) {
    if (occurs[i]) {
      printf("%d ", i);
    }
  }
  printf("\n");
  return 0;
}
