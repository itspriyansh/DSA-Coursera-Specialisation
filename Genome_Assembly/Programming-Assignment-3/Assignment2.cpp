#include <iostream>
#include <vector>
#include <cstring>
#include <unordered_map>
#include <stack>
#define SIZE 400

using namespace std;

int main(){
	int n=0;
	vector<string> data(SIZE);
	for(int i=0;i<SIZE;i++){
		cin>>data[i];
	}
	int k;
	for(k=data[0].size();k>1;k--){
		unordered_map<string, int> dir;
		vector<vector<int> > adj, rdj;
		int n=0;
		for(int i=0;i<SIZE;i++){
			for(int j=0;j<=data[i].size()-k;j++){
				string temp = data[i].substr(j, k);
				char c = temp.back();
				temp.pop_back();
				int u,v;
				if(dir.find(temp)==dir.end()){
					dir[temp] = n++;
				}
				u=dir[temp];
				temp = temp.substr(1)+c;
				if(dir.find(temp)==dir.end()){
					dir[temp] = n++;
				}
				v=dir[temp];
				if(adj.size()<n){
					adj.resize(n, vector<int>(1,0));
					rdj.resize(n, vector<int>(1,0));
				}
				adj[u].push_back(v);
				adj[u][0]++;
				rdj[v].push_back(u);
				rdj[v][0]++;
			}
		}
		bool valid=true;
		for(int i=0;i<n;i++){
			if(adj[i][0]!=rdj[i][0] || adj[i][0]<=0){
				valid=false;
				break;
			}
		}
		if(!valid){
			// cout<<"Ingoing and Outgoing not equal "<<k<<endl<<"Forward\n";
			// for(int i=0;i<n;i++){
			// 	cout<<i<<" -> ";
			// 	for(auto it=adj[i].begin();it!=adj[i].end();it++){
			// 		cout<<*it<<" ";
			// 	}cout<<endl;
			// }
			// cout<<"Reverse\n";
			// for(int i=0;i<n;i++){
			// 	cout<<i<<" -> ";
			// 	for(auto it=rdj[i].begin();it!=rdj[i].end();it++){
			// 		cout<<*it<<" ";
			// 	}cout<<endl;
			// }
			continue;
		};
		stack<int> record, s;
		vector<bool> visited(n, false);
		s.push(0);
		visited[0]=true;
		record.push(0);
		while(!s.empty()){
			int v = s.top();
			s.pop();
			for(auto it=adj[v].begin()+1;it!=adj[v].end();it++){
				if(visited[*it]) continue;
				record.push(*it);
				s.push(*it);
				visited[*it]=true;
			}
		}
		if(record.size() < n) continue;
		fill(visited.begin(), visited.end(), false);
		vector<int> check;
		while(!record.empty()){
			int u = record.top();
			record.pop();
			if(visited[u]) continue;
			s.push(u);
			visited[u]=true;
			check.push_back(0);
			if(check.size()>1){
				valid=false;
				break;
			}
			while(!s.empty()){
				int v = s.top();
				s.pop();
				for(auto it=rdj[v].begin()+1;it!=rdj[v].end();it++){
					if(visited[*it]) continue;
					visited[*it] = true;
					check.back() = check.back()+1;
				}
			}
		}
		if(valid) break;
	}
	cout<<k<<endl;
	return 0;
}