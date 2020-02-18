#include <algorithm>
#include <cstdio>
#include <string>
#include <utility>
#include <vector>
#include <iostream>

using std::make_pair;
using std::pair;
using std::string;
using std::vector;
using namespace std;

// Data structure to store edges of a suffix tree.
struct Node{
  int start;
  int end;
  int depth;
  Node* parent;
  vector<Node*> children;

  Node(): start(-1), end(-1), parent(NULL), depth(0) {};
  Node(int start_, int end_, Node* parent_): start(start_), end(end_), parent(parent_), depth(parent_->depth) {};

  Node* AddChild(int start, int end){
    // cout<<"Add start "<<this->start<<" end "<<this->end<<" "<<start<<" "<<end<<endl;
    Node* ch = new Node(start, end, this);
    this->children.push_back(ch);
    ch->depth += (end - start);
    // cout<<ch->start<<" "<<ch->end<<" "<<ch->depth<<endl;
    return ch;
  }
  Node* SplitChild(int lcp, int suffix, int end){
    // cout<<"Split start "<<this->start<<" end "<<this->end<<" "<<lcp<<" "<<suffix<<" "<<end<<endl;
    // cout<<"Parent: "<<this->parent->depth<<endl;
    Node* ch1 = new Node(this->start+lcp-this->parent->depth, this->end, this);
    Node* ch2 = new Node(suffix+lcp, end, this);
    ch1->children = this->children;
    this->children.clear();
    ch1->depth = this->depth;
    this->end = ch1->start;
    this->depth = lcp;
    ch2->depth = this->depth + (ch2->end-ch2->start);
    this->children.push_back(ch1);
    this->children.push_back(ch2);
    // cout<<this->start<<" "<<this->end<<" "<<this->depth<<endl;
    // cout<<ch1->start<<" "<<ch1->end<<" "<<ch1->depth<<"; "<<ch2->start<<" "<<ch2->end<<" "<<ch2->depth<<endl;
    return ch2;
  }
};

// Build suffix tree of the string text given its suffix array suffix_array
// and LCP array lcp_array. Return the tree as a mapping from a node ID
// to the vector of all outgoing edges of the corresponding node. The edges in the
// vector must be sorted in the ascending order by the first character of the edge label.
// Root must have node ID = 0, and all other node IDs must be different
// nonnegative integers.
//
// For example, if text = "ACACAA$", an edge with label "$" from root to a node with ID 1
// must be represented by Edge(1, 6, 7). This edge must be present in the vector tree[0]
// (corresponding to the root node), and it should be the first edge in the vector 
// (because it has the smallest first character of all edges outgoing from the root).
Node* SuffixTreeFromSuffixArray(
    const vector<int>& suffix_array,
    const vector<int>& lcp_array,
    const string& text) {
  Node* tree = new Node();
  Node* current = tree;
  int lcpPrev = 0;
  for(int i=0;i<suffix_array.size();i++){
    int suffix = suffix_array[i];
    int depth = current->depth;
    if(current->parent != NULL) depth = current->parent->depth;
    // // cout<<"Depth: "<<depth<<endl;
    // // cout<<current->start<<" "<<current->end<<endl;
    while(depth > lcpPrev){
      depth = current->parent->parent->depth;
      current = current->parent;
    }
    // // cout<<"Imp. Depth: "<<depth<<" "<<lcpPrev<<endl;
    // // cout<<current->start<<" "<<current->end<<endl;
    if(depth == lcpPrev){
      if(current->parent != NULL) current = current->parent;
      current = current->AddChild(suffix+lcpPrev, text.size());
    }else{
      current = current->SplitChild(lcpPrev, suffix, text.size());
    }
    if(i < lcp_array.size()) lcpPrev = lcp_array[i];
  }
  return tree;
}


int main() {
  char buffer[200001];
  scanf("%s", buffer);
  string text = buffer;
  vector<int> suffix_array(text.length());
  for (int i = 0; i < text.length(); ++i) {
    scanf("%d", &suffix_array[i]);
  }
  vector<int> lcp_array(text.length() - 1);
  for (int i = 0; i + 1 < text.length(); ++i) {
    scanf("%d", &lcp_array[i]);
  }
  // Build the suffix tree and get a mapping from 
  // suffix tree node ID to the list of outgoing Edges.
  Node* tree = SuffixTreeFromSuffixArray(suffix_array, lcp_array, text);
  printf("%s\n", buffer);
  vector<Node*> stack;
  stack.push_back(tree);
  while(!stack.empty()){
    Node* current = stack.back();
    stack.pop_back();
    if(current->start != -1)
      printf("%d %d\n", current->start, current->end);
    for(int i=current->children.size()-1;i>=0;i--)
      stack.push_back(current->children[i]);
  }
  return 0;
}
