#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
	int n,m;
	cin>>n>>m;
	vector<vector<int> > adj(n, vector<int>(1,0));
	vector<int> incoming(n, 0);
	for(int i=0;i<m;i++){
		int a, b;
		cin>>a>>b;
		adj[a-1].push_back(b-1);
		adj[a-1][0]++;
		incoming[b-1]++;
	}

	// for(int i=0;i<adj.size();i++){
	// 	cout<<i<<" -> ";
	// 	for(int v: adj[i]){
	// 		cout<<v<<" ";
	// 	}cout<<endl;
	// }

	bool proceed=true;
	for(int i=0;i<n;i++){
		if(adj[i][0]!=incoming[i]){
			proceed = false;
			cout<<0<<endl;
			break;
		}
	}
	if(proceed){
		cout<<1<<endl;
		vector<int> bucket1, bucket2;
		bucket1.push_back(0);
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
		for(int i=0;i+1<bucket1.size();i++){
			cout<<bucket1[i]+1<<" ";
		}
		if(!bucket2.empty()) cout<<bucket1.back()+1<<" ";
		for(int i=bucket2.size()-1;i>0;i--){
			cout<<bucket2[i]+1<<" ";
		}cout<<endl;
	}
	return 0;
}