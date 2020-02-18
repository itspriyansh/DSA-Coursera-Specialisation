#include <cstdio>
#include <string>
#include <iostream>
#include <algorithm>
#include <stack>
#include <cstdlib>
using namespace std;

struct Vertex {
  char key;
  int size;
  Vertex* left;
  Vertex* right;
  Vertex* parent;

  Vertex(char key, Vertex* left, Vertex* right, Vertex* parent) 
  : key(key), size(1), left(left), right(right), parent(parent) {}
};

void update(Vertex* v) {
  if (v == NULL) return;
  v->size = 1 + (v->left != NULL ? v->left->size : 0) + (v->right != NULL ? v->right->size : 0);
  if (v->left != NULL) {
    v->left->parent = v;
  }
  if (v->right != NULL) {
    v->right->parent = v;
  }
}

void small_rotation(Vertex* v) {
  Vertex* parent = v->parent;
  if (parent == NULL) {
    return;
  }
  Vertex* grandparent = v->parent->parent;
  if (parent->left == v) {
    Vertex* m = v->right;
    v->right = parent;
    parent->left = m;
  } else {
    Vertex* m = v->left;
    v->left = parent;
    parent->right = m;
  }
  update(parent);
  update(v);
  v->parent = grandparent;
  if (grandparent != NULL) {
    if (grandparent->left == parent) {
      grandparent->left = v;
    } else {
      grandparent->right = v;
    }
  }
}

void big_rotation(Vertex* v) {
  if (v->parent->left == v && v->parent->parent->left == v->parent) {
    // Zig-zig
    small_rotation(v->parent);
    small_rotation(v);
  } else if (v->parent->right == v && v->parent->parent->right == v->parent) {
    // Zig-zig
    small_rotation(v->parent);
    small_rotation(v);
  } else {
    // Zig-zag
    small_rotation(v);
    small_rotation(v);
  }  
}
void splay(Vertex*& root, Vertex* v) {
  if (v == NULL) return;
  while (v->parent != NULL) {
    if (v->parent->parent == NULL) {
      small_rotation(v);
      break;
    }
    big_rotation(v);
  }
  root = v;
}

Vertex* find(Vertex* root, int index) {
  if(root == NULL || index >= root->size){
  	return NULL;
  }
  int s = (root->left != NULL) ? root->left->size : 0;
  if(index == s)
  	return root;
  else if(index < s)
  	return find(root->left, index);
  else if(index > s)
  	return find(root->right, index-s-1);
}

void split(Vertex* root, int index, Vertex*& left, Vertex*& right) {
  right = find(root, index);
  splay(root, right);
  if (right == NULL) {
    left = root;
    return;
  }
  left = right->left;
  right->left = NULL;
  if (left != NULL) {
    left->parent = NULL;
  }
  update(left);
  update(right);
}

Vertex* merge(Vertex* left, Vertex* right) {
  if (left == NULL) return right;
  if (right == NULL) return left;
  Vertex* min_right = right;
  while (min_right->left != NULL) {
    min_right = min_right->left;
  }
  splay(right, min_right);
  right->left = left;
  update(right);
  return right;
}

class Rope {
	std::string s;
	Vertex* root = NULL;

	void insert(char x) {
	  if(root == NULL){
	  	root = new Vertex(x, NULL, NULL, NULL);
	  	return;
	  }
	  Vertex* v = root;
	  while(v->right != NULL){
	  	v = v->right;
	  }
	  splay(root, v);
	  Vertex* new_vertex = new Vertex(x, NULL, NULL, v);
	  v->right = new_vertex;
	  update(v);
	  Vertex *p = find(root, rand()%root->size + 1);
	  splay(root, p);
	}
	void in_order(Vertex *root, string &s){
		if(root == NULL) return;
		in_order(root->left, s);
		s.push_back(root->key);
		// s.push_back(root->size + '0');
		in_order(root->right, s);
	}

public:
	Rope(const std::string &s) : s(s) {
		for(int i=0;i<s.size();i++){
			insert(s[i]);
		}
	}

	void process( int i, int j, int k ) {
        // Replace this code with a faster implementation
        // string s1, s2, s3, s4, s5, s6;
		Vertex* left = NULL;
	    Vertex* middle = NULL;
	    Vertex* right = NULL;
	    split(root, i, left, middle);
	    split(middle, j-i + 1, middle, right);
	    // in_order(left, s1);
	    // in_order(middle, s2);
	    // in_order(right, s3);
	    root = merge(left, right);
	    // in_order(root, s4);
	    split(root, k, left, right);
	    // in_order(left, s5);
	    // in_order(right, s6);
	    root = merge(merge(left, middle), right);
	    // s = "";
	    // cout<<s1<<endl<<s2<<endl<<s3<<endl<<s4<<endl<<s5<<endl<<s6<<endl;
	    // in_order(root, s);
	}

	void print() {
		stack<Vertex *> s;
		Vertex *v = root;
		while(v!=NULL || !s.empty()){
			while(v!=NULL){
				s.push(v);
				v = v->left;
			}
			v = s.top();
			s.pop();
			cout<<v->key;
			v = v->right;
		}
		cout<<endl;
	}

	std::string result() {
		return s;
	}
};

int main() {
	std::ios_base::sync_with_stdio(0);
	std::string s;
	std::cin >> s;
	Rope rope(s);
	int actions;
	std::cin >> actions;
        for (int action_index = 0; action_index < actions; ++action_index) {
                int i, j, k;
		std::cin >> i >> j >> k;
		rope.process(i, j, k);
	}
	// std::cout << rope.result() << std::endl;
	rope.print();
}
