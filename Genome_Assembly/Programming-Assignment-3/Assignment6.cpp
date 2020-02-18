#include <iostream>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#define K 20
#define DEBUG true

using namespace std;

class DeBruijnGraph{
public:
	struct Vertex{
		int id;
		vector<int> in, out, edges;
		bool removed;
		string str;
		Vertex(): id(-1), removed(false){}
		Vertex(int id, string str): id(id), str(str), removed(false){}
	};
	struct Edge{
		int from, to;
		bool used;
	};
	struct Node{
		int id;
		Node* parent;
		vector<Node*> kids;
	};
private:
	vector<Vertex> vertices;
	vector<Edge> edges;
	unordered_map <string, int> countNodes;
	unordered_map <string, int> dict;
	vector<string> contigs;
	void printGraph(string s){
		#ifdef DEBUG
		cout<<s<<endl;
		for(int i=0;i<vertices.size();i++){
			cout<<i<<" -> ";
			for(auto j=vertices[i].in.begin();j!=vertices[i].in.end();j++){
				cout<<*j<<" ";
			}cout<<", ";
			for(auto j=vertices[i].out.begin();j!=vertices[i].out.end();j++){
				cout<<*j<<" ";
			}cout<<" "<<(vertices[i].removed?"removed":"not-removed")<<endl;
		}
		#endif
	}
	void inExplore(int id){
		if(!vertices[id].out.empty() || vertices[id].in.size()!=1){
			return;
		}
		vertices[id].removed=true;
		int inId=vertices[id].in[0];
		vertices[id].in.clear();
		for(int i=0;i<vertices[inId].out.size();i++){
			if(vertices[inId].out[i]==id){
				swap(vertices[inId].out[i], vertices[inId].out.back());
				vertices[inId].out.pop_back();
				break;
			}
		}
		inExplore(inId);
	}
	void outExplore(int id){
		if(!vertices[id].in.empty() || vertices[id].out.size()!=1){
			return;
		}
		vertices[id].removed=true;
		int outId=vertices[id].out[0];
		vertices[id].out.clear();
		for(int i=0;i<vertices[outId].in.size();i++){
			if(vertices[outId].in[i]==id){
				swap(vertices[outId].in[i], vertices[outId].in.back());
				vertices[outId].in.pop_back();
				break;
			}
		}
		outExplore(outId);
	}
	void dfs(Node* root, unordered_set<int>& parents, vector<bool>& visited, vector<Node*>& tree){
		if(parents.size()>=K+1) return;
		int id=root->id;
		for(auto it=vertices[id].out.begin();it!=vertices[id].out.end();it++){
			if(*it==-1) continue;
			if(parents.find(id)==parents.end()) return;
			if(visited[*it]){
				if(parents.find(*it)!=parents.end()){
					continue;
				}else{
					//bubble found
					#ifdef DEBUG
					cout<<"Bubble Detected reaching "<<*it<<" from "<<id<<endl;
					#endif
					bubbleRemove(*it, id, tree, visited, parents);
				}
			}else{
				visited[*it]=true;
				Node* child = new Node;
				child->parent=root;
				child->id=*it;
				tree[*it]=child;
				root->kids.push_back(child);
				parents.insert(*it);
				dfs(child, parents, visited, tree);
				if(parents.find(*it)!=parents.end()){
					parents.erase(*it);
				}
			}
		}
	}
	void bubbleRemove(int target, int stoppage, vector<Node*>& tree, vector<bool>& visited, unordered_set<int>& parents){
		int common = commonParent(tree[target], tree[stoppage]);
		#ifdef DEBUG
		cout<<"Common Parent is "<<common<<endl;
		#endif
		if(common==-1) return;
		double sum=0, count=0;
		for(Node* p=tree[target];p!=tree[common]&&p->parent!=NULL;p=p->parent){
			sum += countNodes[vertices[p->parent->id].str+vertices[p->id].str.back()];
			count++;
		}
		double avg1 = sum/count;

		#ifdef DEBUG
		cout<<"Case 1: "<<sum<<"/"<<count<<" = "<<avg1<<endl;
		#endif

		count=1;
		sum = countNodes[vertices[stoppage].str+vertices[target].str.back()];
		for(Node* p=tree[stoppage];p!=tree[common]&&p->parent!=NULL;p=p->parent){
			sum += countNodes[vertices[p->parent->id].str+vertices[p->id].str.back()];
			count++;
		}
		double avg2 = sum/count;
		Node* q=NULL;

		#ifdef DEBUG
		cout<<"Case 2: "<<sum<<"/"<<count<<" = "<<avg2<<endl;
		#endif

		if(avg1<avg2){
			Node* start;
			for(Node* p=tree[target];p!=tree[common];p=p->parent){
				if(p->parent==tree[common]){
					start = p;
					break;
				}
			}
			makeFalse(start, visited, target);
			for(Node* p=tree[target];p!=tree[common];p=p->parent){
				// vertices[p->parent->id].out.erase(remove(vertices[p->parent->id].out.begin(), vertices[p->parent->id].out.end(), p->id), vertices[p->parent->id].out.end());
				*(find(vertices[p->parent->id].out.begin(), vertices[p->parent->id].out.end(), p->id))=-1;
				// vertices[p->id].in.erase(remove(vertices[p->id].in.begin(), vertices[p->id].in.end(), p->parent->id), vertices[p->id].in.end());
				q=p;
			}
			visited[tree[target]->id]=true;
			tree[target]->parent = tree[stoppage];
			tree[stoppage]->kids.push_back(tree[target]);
			tree[common]->kids.erase(remove(tree[common]->kids.begin(), tree[common]->kids.end(), q), tree[common]->kids.end());
		}else{
			Node* start;
			for(Node* p=tree[stoppage];p!=tree[common];p=p->parent){
				if(p->parent==tree[common]){
					start = p;
					break;
				}
			}
			makeFalse(start, visited, target);
			// vertices[target].in.erase(remove(vertices[target].in.begin(), vertices[target].in.end(), stoppage), vertices[target].in.end());
			*(find(vertices[stoppage].out.begin(), vertices[stoppage].out.end(), target))=-1;
			for(Node* p=tree[stoppage];p!=tree[common];p=p->parent){
				// vertices[p->parent->id].out.erase(remove(vertices[p->parent->id].out.begin(), vertices[p->parent->id].out.end(), p->id), vertices[p->parent->id].out.end());
				*(find(vertices[p->parent->id].out.begin(), vertices[p->parent->id].out.end(), p->id))=-1;
				// vertices[p->id].in.erase(remove(vertices[p->id].in.begin(), vertices[p->id].in.end(), p->parent->id), vertices[p->id].in.end());
				parents.erase(p->id);
				q=p;
			}
			tree[common]->kids.erase(remove(tree[common]->kids.begin(), tree[common]->kids.end(), q), tree[common]->kids.end());
		}
	}
	void makeFalse(Node* root, vector<bool>& visited, int target){
		if(root->id==target) return;
		visited[root->id]=false;
		for(int i=0;i<root->kids.size();i++){
			makeFalse(root->kids[i], visited, target);
		}
	}
	int commonParent(Node* u, Node* v){
		unordered_set<int> path;
		for(Node* p=u;p!=NULL;p=p->parent){
			path.insert(p->id);
		}
		for(Node* p=v;p!=NULL;p=p->parent){
			if(path.find(p->id)!=path.end()){
				return p->id;
			}
		}
		return -1;
	}
	void run(vector<int>& path, int v, vector<bool>& visited){
		visited[v] = true;
		path.push_back(v);
		for(auto i=vertices[v].edges.begin();i!=vertices[v].edges.end();i++){
			if(!edges[*i].used){
				edges[*i].used = true;
				run(path, edges[*i].to, visited);
			}
		}
	}
	void printTree(Node* root){
		cout<<vertices[root->id].str<<endl;
		for(int i=0;i<root->kids.size();i++){
			printTree(root->kids[i]);
		}
	}
public:
	void readData(){
		int SIZE;
		cin>>SIZE;
		string read;
		for(int iter=0;iter<SIZE;iter++){
			cin>>read;
			for(int i=0, s=read.size()-K;i<=s;i++){
				string a = read.substr(i,K);
				countNodes[a]++;
				if(countNodes[a]==1){
					string b=a.substr(1);
					a.pop_back();
					if(dict.find(a)==dict.end()){
						dict.insert(make_pair(a, vertices.size()));
						vertices.push_back(Vertex(dict[a], a));
					}
					if(dict.find(b)==dict.end()){
						dict.insert(make_pair(b, vertices.size()));
						vertices.push_back(Vertex(dict[b], b));
					}
					int u=dict[a], v=dict[b];
					vertices[u].out.push_back(v);
					vertices[v].in.push_back(u);
				}
			}
		}
		#ifdef DEBUG
		printGraph("After read");
		cout<<"Count Nodes\n";
		for(auto it=countNodes.begin();it!=countNodes.end();it++){
			cout<<it->first<<" -> "<<it->second<<endl;
		}
		#endif
	}
	void tipRemoval(){
		for(int i=0;i<vertices.size();i++){
			if(vertices[i].removed) continue;
			if(vertices[i].out.empty() && vertices[i].in.size()==1){
				inExplore(i);
			}
			if(vertices[i].in.empty() && vertices[i].out.size()==1){
				outExplore(i);
			}	
		}
		#ifdef DEBUG
		printGraph("After Tip Removal");
		#endif
	}
	void bubbleRemoval(){
		Node* root=NULL;
		unordered_set<int> parents;
		vector<bool> visited(vertices.size());
		vector<Node*> tree(vertices.size(), NULL);
		for(int i=0;i<vertices.size();i++){
			if(vertices[i].removed || vertices[i].out.size()<=1) continue;
			root = new Node();
			root->parent = NULL;
			root->id=i;
			tree[i]=root;
			fill(visited.begin(), visited.end(), false);
			parents.clear();
			parents.insert(i);
			visited[i]=true;
			dfs(root, parents, visited, tree);

			#ifdef DEBUG
			cout<<"Tree at "<<i<<":\n";
			printTree(root);
			#endif
		}
		for(int i=0;i<vertices.size();i++){
			for(auto j=vertices[i].out.begin();j!=vertices[i].out.end();j++){
				if(*j==-1){
					vertices[i].out.erase(j);
					j--;
				}
			}
		}
		#ifdef DEBUG
		printGraph("After Bubble Removal");
		#endif
	}
	void clean(){
		for(int i=0;i<vertices.size();i++){
			if(vertices[i].removed) continue;
			for(auto j=vertices[i].out.begin();j!=vertices[i].out.end();j++){
				vertices[i].edges.push_back(edges.size());
				edges.push_back({i,*j,false});
			}
		}
		#ifdef DEBUG
		printGraph("After Cleaning");
		#endif
	}
	void populate(){
		for(int i=0;i<vertices.size();i++){
			for(int z=0, size=vertices[i].out.size();z<size;z++){
				int j = vertices[i].out[z];
				for(int k=1, repetation=countNodes[vertices[i].str+vertices[j].str.back()];k<repetation;k++){
					vertices[i].out.push_back(j);
					vertices[j].in.push_back(i);
				}
			}
		}
	}
	void print(){
		vector<int> path;
		vector<bool> visited(vertices.size(), false);
		for(int v=0;v<vertices.size();v++){
			if(vertices[v].removed || visited[v]) continue;
			path.clear();
			run(path, v, visited);

			#ifdef DEBUG
			cout<<"Eularian Path\n";
			for(int p: path){
				cout<<p<<" ";
			}cout<<endl;
			#endif

			if(path.size()<2) continue;
			string temp = vertices[path[0]].str;
			for(auto i=path.begin()+1;i!=path.end();i++){
				temp += vertices[*i].str.back();
				if((int)vertices[*i].out.size()>1 || (int)vertices[*i].in.size()>1){
					contigs.push_back(temp);
					temp = vertices[*i].str;
				}
			}
		}
		for(int i=0;i<contigs.size();i++){
			cout<<">CONTIG"<<i+1<<endl<<contigs[i]<<endl;
		}
	}
	void explore(int u, string temp, vector<bool>& visited){
		visited[u]=true;
		if(temp.empty()){
			temp += vertices[u].str;
		}else{
			temp += vertices[u].str.back();
			if((int)vertices[u].out.size()>1 || (int)vertices[u].in.size()>1){
				contigs.push_back(temp);
				temp = vertices[u].str;
			}
		}
		bool flag=false;
		if(vertices[u].out.size()==0){
			contigs.push_back(temp);
		}
		for(auto i=vertices[u].edges.begin();i!=vertices[u].edges.end();i++){
			if(!edges[*i].used){
				edges[*i].used = true;
				explore(edges[*i].to, temp, visited);
			}
		}
	}
};

int main(){
	DeBruijnGraph graph;
	graph.readData();
	graph.tipRemoval();
	graph.bubbleRemoval();
	graph.tipRemoval();
	graph.populate();
	graph.clean();
	graph.print();
	return 0;
}