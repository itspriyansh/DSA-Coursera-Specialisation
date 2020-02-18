#include <iostream>
#include <unordered_map>
#include <vector>
#include <cstring>
#include <algorithm>
#define SIZE 5396

using namespace std;

int main(){
	int n=0;
	unordered_map<string, int> dict;
	vector<string> list(SIZE), rev;
	for(int i=0;i<SIZE;i++){
		cin>>list[i];
		char c = list[i].back();
		list[i].pop_back();
		if(dict.find(list[i])==dict.end()){
			dict[list[i]] = n++;
			rev.push_back(list[i]);
		}list[i] += c;
		string s = list[i].substr(1);
		if(dict.find(s)==dict.end()){
			dict[s] = n++;
			rev.push_back(s);
		}
	}
	vector<vector<int> > adj(n, vector<int>(1,0));
	for(int i=0;i<list.size();i++){
		char c = list[i].back();
		list[i].pop_back();
		int a = dict[list[i]];
		list[i] += c;
		int b = dict[list[i].substr(1)];
		adj[a].push_back(b);
		adj[a][0]++;
	}

	// for(int i=0;i<n;i++){
	// 	cout<<i<<" -> ";
	// 	for(int v: adj[i]){
	// 		cout<<v<<" ";
	// 	}cout<<endl;
	// }

	int m=SIZE;
	vector<int> bucket1(1,0), bucket2;
	while(m>0){
		int v = bucket1.back();
		if(adj[v][0]>0){
			bucket1.push_back(adj[v][1]);
			swap(adj[v][1], adj[v][adj[v][0]--]);
			m--;
		}else{
			bucket2.push_back(bucket1.back());
			bucket1.pop_back();
		}
	}
	string ans;
	for(int i=0;i+1<bucket1.size();i++){
		ans += rev[bucket1[i]].back();
	}if(!bucket2.empty()) ans += rev[bucket1.back()].back();
	for(int i=bucket2.size()-1;i>0;i--){
		ans += rev[bucket2[i]].back();
	}
	cout<<ans<<endl;
	return 0;
}