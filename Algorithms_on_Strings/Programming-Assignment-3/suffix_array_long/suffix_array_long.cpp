#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

// Build suffix array of the string text and
// return a vector result of the same length as the text
// such that the value result[i] is the index (0-based)
// in text where the i-th lexicographically smallest
// suffix of text starts.

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
  // cout<<"SortCharacters:\n";
  // for(int i=0;i<order.size();i++) cout<<order[i]<<" ";
  // cout<<endl;
  return order;
}
vector<int> ComputeCharClasses(const string &text, const vector<int> &order){
  vector<int> classes(text.size());
  classes[order[0]] = 0;
  for(int i=1;i<text.size();i++){
    if(text[order[i]] != text[order[i-1]])
      classes[order[i]] = classes[order[i-1]]+1;
    else
      classes[order[i]] = classes[order[i-1]];
  }
  // cout<<"ComputeCharClasses:\n";
  // for(int i=0;i<classes.size();i++) cout<<classes[i]<<" ";
  // cout<<endl;
  return classes;
}
vector<int> SortDoubled(const string &text, int l, const vector<int>& order, const vector<int>& classes){
  vector<int> count(text.size(), 0);
  vector<int> newOrder(text.size());
  for(int i=0;i<classes.size();i++)
    count[classes[i]]++;
  for(int i=1;i<count.size();i++)
    count[i] += count[i-1];
  for(int i=classes.size()-1;i>=0;i--){
    int start = (order[i]-l+text.size()) % text.size();
    int cl = classes[start];
    count[cl]--;
    newOrder[count[cl]] = start
    ;
  }
  // cout<<"SortDoubled "<<l<<":\n";
  // for(int i=0;i<newOrder.size();i++) cout<<newOrder[i]<<" ";
  // cout<<endl;
  return newOrder;
}
vector<int> UpdateClasses(const vector<int>& order, const vector<int>& classes, int l){
  vector<int> newClasses(order.size());
  newClasses[order[0]] = 0;
  for(int i=1;i<order.size();i++){
    int current = order[i], prev = order[i-1];
    int mid = (current+l)%order.size();
    int midPrev = (prev+l)%order.size();
    if(classes[current]!=classes[prev] || classes[mid]!=classes[midPrev])
      newClasses[current] = newClasses[prev]+1;
    else
      newClasses[current] = newClasses[prev];
  }
  // cout<<"UpdateClasses "<<l<<":\n";
  // for(int i=0;i<newClasses.size();i++) cout<<newClasses[i]<<" ";
  // cout<<endl;
  return newClasses;
}

vector<int> BuildSuffixArray(const string& text) {
  vector<int> result;
  // Implement this function yourself
  result = SortCharacters(text);
  vector<int> classes = ComputeCharClasses(text, result);
  for(int l=1;l<text.size();l*=2){
    result = SortDoubled(text, l, result, classes);
    classes = UpdateClasses(result, classes, l);
  }
  return result;
}

int main() {
  string text;
  cin >> text;
  vector<int> suffix_array = BuildSuffixArray(text);
  for (int i = 0; i < suffix_array.size(); ++i) {
    cout << suffix_array[i] << ' ';
  }
  cout << endl;
  return 0;
}
