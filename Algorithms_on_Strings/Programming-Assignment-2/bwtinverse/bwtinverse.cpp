#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <cassert>

using namespace std;

int letterToIndex(char ch){
	switch(ch){
		case 'A': return 0; break;
		case 'C': return 1; break;
		case 'G': return 2; break;
		case 'T': return 3; break;
		default:{
			// cout<<ch<<endl;
			assert(false);
			return -1;
		}
	}
}

string InverseBWT(const string& bwt) {
  string text = "$";
  // write your code here
  vector<int> count(4,0), iter(bwt.size());
  for(int i=0;i<bwt.size();i++){
  	if(bwt[i]!='$'){
  		iter[i] = count[letterToIndex(bwt[i])]++;
  	}
  }fill(count.begin(), count.end(), 0);
  for(int i=0;i<bwt.size();i++){
  	if(bwt[i]!='$'){
  		count[letterToIndex(bwt[i])]++;
  	}
  }
  int current = 0;
  text += bwt[current];
  while(text.size() < bwt.size()){
  	// cout<<text<<" "<<current<<endl;
  	char ch = bwt[current];
  	int x = letterToIndex(ch);
  	current = 1 + iter[current];
  	for(int n=0;n<x;n++) current += count[n];
  	text += bwt[current];
  }reverse(text.begin(), text.end());
  return text;
}

int main() {
  string bwt;
  cin >> bwt;
  cout << InverseBWT(bwt) << endl;
  return 0;
}