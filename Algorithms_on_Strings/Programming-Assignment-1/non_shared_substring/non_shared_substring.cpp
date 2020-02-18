#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

struct Node{
	int start;
	int end;
	vector<Node*> children;

	Node(){
		start = -1;
		end = -1;
	}
	Node(int a, int b){
		start = a;
		end = b;
	}

	void addChild(int a, int end){
		Node* ch = new Node(a, end);
		this->children.push_back(ch);
	}
	void splitChild(int p, int q, int end){
		Node* ch_1 = new Node(p, this->end);
		Node* ch_2 = new Node(q, end);
		for(int i=0;i < this->children.size();i++)
			ch_1->children.push_back(this->children[i]);
		this->children.clear();
		this->end = p;
		this->children.push_back(ch_1);
		this->children.push_back(ch_2);
	}
};

Node* build_suffix_tree(string &text){
	// text += '$';
	Node* root = new Node;
	root->addChild(0, text.size());
	for(int i=0;i<text.size();i++){
		int p = i;
		bool done = false;
		Node* current = root;
		while(p<text.size() && !done){
			bool flag = false;
			for(int j=0;j<current->children.size();j++){
				if(text[current->children[j]->start] == text[p]){
					flag = true;
					current = current->children[j];
					break;
				}
			}if(flag){
				for(int j=current->start;j<current->end;j++){
					if(text[j] != text[p]){
						current->splitChild(j, p, text.size());
						done = true;
						break;
					}else p++;
				}
			}else{
				current->addChild(p, text.size());
				done = true;
			}
		}
	}
	return root;
}

void shortestResult(Node* p, Node* q, int pos, string append, string &result, const string& a, const string& b){
	int j = pos;
	for(int i=p->start;i<p->end;i++){
		if(j >= q->end){
			bool flag = false;
			for(int k=0;k < q->children.size();k++){
				if(b[q->children[k]->start] == a[i]){
					q = q->children[k];
					j = q->start;
					flag = true;
					break;
				}
			}if(!flag){
				append += a[i];
				// cout<<append<<endl;
				if(result=="" || append.size()<result.size()) result=append;
				return;
			}
		}
		// cout<<i<<" "<<a[i]<<" "<<j<<" "<<b[j]<<endl;
		if(a[i]==b[j]){
			append += a[i];
			if(result != "" && append.size() >= result.size()) return;
		}
		else{
			append += a[i];
			// cout<<append<<endl;
			if(result=="" || append.size()<result.size()) result=append;
			return;
		}
		j++;
	}for(int i=0;i < p->children.size();i++){
		shortestResult(p->children[i], q, j, append, result, a, b);
	}
}

string solve (string p, string q)
{
	string result = "";
	Node* p_tree = build_suffix_tree(p);
	Node* q_tree = build_suffix_tree(q);
	for(int i=0;i<p_tree->children.size();i++){
		bool flag = false;
		for(int j=0;j<q_tree->children.size();j++){
			if(p[p_tree->children[i]->start] == q[q_tree->children[j]->start]){
				shortestResult(p_tree->children[i], q_tree->children[j], q_tree->children[j]->start, "", result, p, q);
				flag = true;
				break;
			}
		}if(!flag){
			result = p[p_tree->children[i]->start];
			break;
		}
	}
	return result;
}

int main (void)
{
	string p;
	cin >> p;
	string q;
	cin >> q;

	string ans = solve (p, q);

	cout << ans << endl;

	return 0;
}
