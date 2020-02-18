#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

int largestBorder(string& a, string& b){
	string temp = b+a;
	vector<int> s(temp.size());
	s[0]=0;
	int border=0;
	for(int i=1;i<s.size();i++){
		while(border>0 && temp[border]!=temp[i]){
			border = s[border-1];
		}
		if(temp[border]==temp[i]) border++;
		else border = 0;
		s[i]=border;
	}
	return s.back();
}

void hamiltonian(vector<string>& data, string& genome){
	vector<bool> visited(data.size(), false);
	visited[0]=true;
	int count=1, prev=0;
	while(count<data.size()){
		int min=-1, match;
		for(int i=1;i<data.size();i++){
			if(visited[i]) continue;
			int m=largestBorder(data[prev], data[i]);
			if(min==-1 || match<m){
				match=m;
				min = i;
			}
		}
		for(int i=0;i<data[prev].size()-match;i++){
			genome += data[prev][i];
		}
		visited[min]=true;
		count++;
		prev = min;
	}
	int match = largestBorder(data[prev], data[0]);
	for(int i=0;i<data[prev].size()-match;i++){
		genome += data[prev][i];
	}
}

int main(){
	vector<string> dataset;
	string temp;
	for(int i=0;i<1618;i++){
		cin>>temp;
		dataset.push_back(temp);
	}

	string genome;
	hamiltonian(dataset, genome);
	cout<<genome<<endl;
	return 0;
}