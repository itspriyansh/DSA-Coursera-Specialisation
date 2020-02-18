#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Preprocess the Burrows-Wheeler Transform bwt of some text
// and compute as a result:
//   * starts - for each character C in bwt, starts[C] is the first position 
//       of this character in the sorted array of 
//       all characters of the text.
//   * occ_count_before - for each character C in bwt and each position P in bwt,
//       occ_count_before[C][P] is the number of occurrences of character C in bwt
//       from position 0 to position P inclusive.
void PreprocessBWT(const string& bwt, 
                   map<char, int>& starts, 
                   map<char, vector<int> >& occ_count_before) {
  // Implement this function yourself
  string sorted = bwt;
  sort(sorted.begin(), sorted.end());
  char prev = '\0';
  for(int i=0;i<sorted.size();i++){
    if(sorted[i] != prev){
      starts.insert(pair<char, int>(sorted[i], i));
      occ_count_before.insert(pair<char, vector<int>>(sorted[i], vector<int>(bwt.size(), 0)));
      prev = sorted[i];
    }
  }for(int i=0;i<bwt.size();i++){
    if(i>0){
      for(map<char, vector<int>>::iterator it=occ_count_before.begin();it!=occ_count_before.end();it++){
        it->second[i] = it->second[i-1];
      }
    }occ_count_before[bwt[i]][i]++;
  }
  // cout<<"Starts:\n";
  // for(map<char, int>::iterator it = starts.begin();it!=starts.end();it++)
  //   cout<<it->first<<" "<<it->second<<endl;
  // cout<<"OCC Count Before:\n";
  // for(map<char, vector<int>>::iterator it = occ_count_before.begin();it!=occ_count_before.end();it++){
  //   cout<<it->first<<endl;
  //   for(int i=0;i<it->second.size();i++){
  //     cout<<it->second[i]<<" ";
  //   }cout<<endl;
  // }
}

// Compute the number of occurrences of string pattern in the text
// given only Burrows-Wheeler Transform bwt of the text and additional
// information we get from the preprocessing stage - starts and occ_counts_before.
int CountOccurrences(const string& pattern, 
                     const string& bwt, 
                     const map<char, int>& starts, 
                     const map<char, vector<int> >& occ_count_before) {
  // Implement this function yourself
  int top = 0, bottom = bwt.size()-1, i = pattern.size()-1;
  while(top <= bottom){
    // cout<<"Top: "<<top<<" Bottom: "<<bottom<<endl;
    if(i>=0){
      if(occ_count_before.find(pattern[i])!=occ_count_before.end() && (bwt[top]==pattern[i] || occ_count_before.find(pattern[i])->second[top] != occ_count_before.find(pattern[i])->second[bottom])){
        int diff = 0;
        if(bwt[top] == pattern[i]) diff=1;
        top = starts.find(pattern[i])->second + occ_count_before.find(pattern[i])->second[top]-diff;
        bottom = starts.find(pattern[i])->second + occ_count_before.find(pattern[i])->second[bottom] - 1;
        i--;
      }else return 0;
    }else{
      return bottom+1-top;
    }
  }
  return 0;
}
     

int main() {
  string bwt;
  cin >> bwt;
  int pattern_count;
  cin >> pattern_count;
  // Start of each character in the sorted list of characters of bwt,
  // see the description in the comment about function PreprocessBWT
  map<char, int> starts;
  // Occurrence counts for each character and each position in bwt,
  // see the description in the comment about function PreprocessBWT
  map<char, vector<int> > occ_count_before;
  // Preprocess the BWT once to get starts and occ_count_before.
  // For each pattern, we will then use these precomputed values and
  // spend only O(|pattern|) to find all occurrences of the pattern
  // in the text instead of O(|pattern| + |text|).
  PreprocessBWT(bwt, starts, occ_count_before);
  for (int pi = 0; pi < pattern_count; ++pi) {
    string pattern;
    cin >> pattern;
    int occ_count = CountOccurrences(pattern, bwt, starts, occ_count_before);
    printf("%d ", occ_count);
  }
  printf("\n");
  return 0;
}
