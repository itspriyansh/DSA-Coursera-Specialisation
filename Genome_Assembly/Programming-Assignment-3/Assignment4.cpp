#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#define SIZE 1618
#define k 15

using namespace std;

int main(){
	unordered_map<string,int> dir;
	unordered_set<string> set;

	// vector<string> tempo;
	int n=0;
	vector<vector<int> > adj, rdj;
	vector<int> incoming;
	for(int iter_string=0;iter_string<SIZE;iter_string++){
		string read;
		cin>>read;
		for(int i=0,s=read.size()-k;i<=s;i++){
			string temp = read.substr(i,k);
			if(set.find(temp)!=set.end()) continue;
			set.insert(temp);
			char c = temp.back();
			temp.pop_back();
			int u,v;
			if(dir.find(temp)==dir.end()){
				dir[temp]=n++;
				// tempo.push_back(temp);
			}
			u = dir[temp];
			temp = temp.substr(1)+c;
			if(dir.find(temp)==dir.end()){
				dir[temp]=n++;
				// tempo.push_back(temp);
			}
			v=dir[temp];
			if(adj.size()<n){
				adj.resize(n);
				incoming.resize(n,0);
			}
			if(u==v) continue;
			adj[u].push_back(v);
			incoming[v]++;
		}
	}
	int count=0;
	stack<int> s;
	for(int i=n-1;i>=0;i--){
		s.push(i);
	}
	vector<bool> visited(n, false);
	while(!s.empty()){
		int v=s.top();
		s.pop();
		visited[v]=true;
		if(!incoming[v]){
			count+=adj[v].size();
			for(auto it=adj[v].begin();it!=adj[v].end();it++){
				incoming[*it]--;
				if(visited[*it]){
					s.push(*it);
					visited[*it]=false;
				}
				// cout<<"From "<<tempo[v]<<" to "<<tempo[*it]<<endl;
			}
			adj[v].clear();
		}
	}
	// cout<<count<<endl;
	fill(visited.begin(), visited.end(), false);
	rdj.resize(n);
	for(int i=0;i<n;i++){
		incoming[i]=adj[i].size();
		for(auto it=adj[i].begin();it!=adj[i].end();it++){
			rdj[*it].push_back(i);
		}
	}

	for(int i=n-1;i>=0;i--){
		s.push(i);
	}
	while(!s.empty()){
		int v=s.top();
		s.pop();
		visited[v]=true;
		if(!incoming[v]){
			count+=rdj[v].size();
			for(auto it=rdj[v].begin();it!=rdj[v].end();it++){
				incoming[*it]--;
				if(visited[*it]){
					s.push(*it);
					visited[*it]=false;
				}
				// cout<<"From "<<tempo[*it]<<" to "<<tempo[v]<<endl;
			}
			rdj[v].clear();
		}
	}
	cout<<count<<endl;
	return 0;
}