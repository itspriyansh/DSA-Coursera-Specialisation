#include <iostream>
#include <map>
#include <string>
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
  void addchildren(int a, int end){
    // cout<<this->start<<" "<<a<<" "<<end<<endl;
    Node* temp = new Node(a, end);
    this->children.push_back(temp);
  }
  void splitchildren(int p, int q, int end){
    // cout<<this->start<<" "<<p<<" "<<this->end<<" "<<q<<" "<<end<<endl;
    Node* ch_1 = new Node(p, this->end);
    Node* ch_2 = new Node(q, end);
    for(int i=0;i < this->children.size();i++){
      ch_1->children.push_back(this->children[i]);
    }this->children.clear();
    this->end = p;
    this->children.push_back(ch_1);
    this->children.push_back(ch_2);
  }
};

Node* build_suffix_tree(const string &text){
  Node* tree = new Node;
  tree->addchildren(0, text.size());
  for(int i=1;i<text.size();i++){
    // cout<<i<<".\n";
    bool done = false;
    int p = i;
    Node *current = tree;
    while(p<text.size() && !done){
      bool flag = false; 
      for(int j=0;j < current->children.size();j++){
        if(text[current->children[j]->start] == text[p]){
          flag = true;
          current = current->children[j];
          break;
        }
      }if(!flag){
        current->addchildren(p, text.size());
        done = true;
      }else{
        for(int j=current->start;j<current->end;j++){
          // cout<<"Start"<<current->start<<" end"<<current->end<<endl;
          // cout<<j<<" "<<text[j]<<" "<<p<<" "<<text[p]<<endl;
          if(text[j]!=text[p]){
            current->splitchildren(j, p, text.size());
            done = true;
            break;
          }else p++;
        }
      }
    }
  }
  return tree;
}

void traverseTrie(Node *t, const string &text,  vector<string> &result){
  for(int i=0;i<t->children.size();i++){
    string append="";
    for(int j=t->children[i]->start;j<t->children[i]->end;j++){
      append += text[j];
    }if(append!="") result.push_back(append);
    traverseTrie(t->children[i], text, result);
  }
}

// Build a suffix tree of the string text and return a vector
// with all of the labels of its edges (the corresponding 
// substrings of the text) in any order.
vector<string> ComputeSuffixTreeEdges(const string& text) {
  vector<string> result;
  // Implement this function yourself
  Node* n = build_suffix_tree(text);
  traverseTrie(n, text , result);
  return result;
}

int main() {
  string text;
  cin >> text;
  vector<string> edges = ComputeSuffixTreeEdges(text);
  for (int i = 0; i < edges.size(); ++i) {
    cout << edges[i] << endl;
  }
  return 0;
}
