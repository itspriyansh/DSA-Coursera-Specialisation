#include <iostream>
#include <vector>
#include <cstring>
#include <unordered_map>
#include <unordered_set>
#define SIZE 1618

using namespace std;

class DeBruisinGraph{
private:
	// vector<Edge> edges;
	vector<vector<int> > adj;

	void getPaths(vector<int>& path, vector<vector<int> >& paths, vector<unordered_set<int> >& set, unordered_set<int>& visited, const int t){
		int u = path.back();
		if(path.size()==t || !adj[u].size()){
			paths.push_back(path);
			set.push_back(visited);
			return;
		}
		for(auto it=adj[u].begin();it!=adj[u].end();it++){
			if(visited.find(*it)!=visited.end()) continue;
			path.push_back(*it);
			visited.insert(*it);
			getPaths(path,paths,set,visited,t);
			visited.erase(*it);
			path.pop_back();
		}
	}
	string getString(vector<int>& left, vector<int>& right, int v){
		string ans;
		for(int l: left){
			ans += l;
			if(l==v) break;
			else ans += ',';
		}
		ans += '.';
		for(int r: right){
			ans += r;
			if(r==v) break;
			else ans += ',';
		}
		ans += '.';
		return ans;
	}
public:
	void readData(int k){
		unordered_set<string> s;
		unordered_map<string,int> dir;
		int n=0;
		for(int string_input=0;string_input<SIZE;string_input++){
			string t;
			cin>>t;
			for(int i=0;i<=t.size()-k;i++){
				string temp = t.substr(i,k);
				if(s.find(temp)!=s.end()) continue;
				s.insert(temp);
				char c = temp.back();
				temp.pop_back();
				if(dir.find(temp)==dir.end()){
					dir[temp]=n++;
				}
				int u=dir[temp];
				temp = temp.substr(1)+c;
				if(dir.find(temp)==dir.end()){
					dir[temp]=n++;
				}
				int v=dir[temp];
				if(adj.size()<n){
					adj.resize(n);
				}
				if(u==v) continue;
				// adj[u].push_back(edges.size());
				// edges.push_back({u,v});
				adj[u].push_back(v);
			}
		}
	}
	int bubbles(const int t){
		int count=0;
		vector<int> path;
		vector<vector<int> > lt, rt;
		vector<unordered_set<int> > left, right;
		unordered_set<int> visited;
		for(int u=0;u<adj.size();u++){
			if(adj[u].size()<=1) continue;
			for(auto i=adj[u].begin();i+1!=adj[u].end();i++){
				path.clear();
				visited.clear();
				lt.clear();
				left.clear();
				path.push_back(*i);
				visited.insert(*i);
				getPaths(path, lt, left, visited, t);
				for(auto j=i+1;j!=adj[u].end();j++){
					path.clear();
					visited.clear();
					rt.clear();
					right.clear();
					path.push_back(*j);
					visited.insert(*j);
					getPaths(path, rt, right, visited, t);
					
					unordered_set<string> sequences;
					for(int a=0;a<left.size();a++){
						for(int b=0;b<rt.size();b++){
							for(int x: rt[b]){
								if(left[a].find(x)!=left[a].end()){
									sequences.insert(getString(lt[a], rt[b], x));
									break;
								}
							}
						}
					}
					count += sequences.size();
				}
			}
		}
		return count;
	}
};
int main(){
	DeBruisinGraph graph;
	int k, t;
	cin>>k>>t;
	graph.readData(k);
	cout<<graph.bubbles(t)<<endl;
	return 0;
}