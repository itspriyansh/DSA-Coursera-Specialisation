#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
	int n,m=0;
	cin>>n;
	int s = 1<<(n-1), t = s-(1<<(n-2));
	vector<vector<int> > adj(s, vector<int>(1, 0));
	for(int i=0;i<s;i++){
		for(int j=0;j<2;j++){
			adj[i].push_back(((i%t)<<1)+j);
			adj[i][0]++;
			m++;
		}
	}

	// for(int i=0;i<s;i++){
	// 	cout<<i<<" -> ";
	// 	for(int v: adj[i]){
	// 		cout<<v<<" ";
	// 	}cout<<endl;
	// }

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

	// for(int i=0;i+1<bucket1.size();i++){
	// 	cout<<bucket1[i]<<" ";
	// }
	// if(!bucket2.empty()) cout<<bucket1.back()<<" ";
	// for(int i=bucket2.size()-1;i>0;i--){
	// 	cout<<bucket2[i]<<" ";
	// }cout<<endl;

	for(int i=0;i+1<bucket1.size();i++){
		ans += bucket1[i]%2+'0';
	}
	if(!bucket2.empty()) ans += bucket1.back()%2+'0';
	for(int i=bucket2.size()-1;i>0;i--){
		ans += bucket2[i]%2+'0';
	}
	cout<<ans<<endl;
	return 0;
}