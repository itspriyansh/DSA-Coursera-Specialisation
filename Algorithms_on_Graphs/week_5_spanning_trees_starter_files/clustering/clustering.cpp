#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>
#include <cmath>

using namespace std;

class node{
public:
    int parent, rank, x, y;

    node(int x, int y, int parent=-1, int rank=0): x(x), y(y), parent(parent), rank(rank) {}
};

class edge{
  public:
    int u, v;
    double weight;

    edge(int u, int v, double weight): u(u), v(v), weight(weight) {}
};

bool compare(edge x, edge y){
  return x.weight<y.weight;
}

void make_set(int i, vector<node> &nodes, vector<int> &x, vector<int> &y){
  nodes.push_back(node(x[i], y[i], i));
}

double distance(int x1, int y1, int x2, int y2){
  return sqrt(pow((x2-x1), 2) + pow((y2-y1), 2));
}

int Find(int i, vector<node> &nodes){
  if(i != nodes[i].parent)
    nodes[i].parent = Find(nodes[i].parent, nodes);
  return nodes[i].parent;
}

void Merge(int u, int v, vector<node> &nodes){
  int s1 = Find(u, nodes), s2 = Find(v, nodes);
  if(s1!=s2){
    if(nodes[s1].rank > nodes[s2].rank)
      nodes[s2].parent = s1;
    else{
      nodes[s1].parent = s2;
      if(nodes[s1].rank == nodes[s2].rank)
        nodes[s2].rank++;
    }
  }
}

double clustering(vector<int> x, vector<int> y, int k) {
  //write your code here
  vector<node> nodes;
  for(int i=0;i<x.size();i++)
    make_set(i, nodes, x, y);
  vector<edge> edges;
  for(int i=0; i<x.size();i++){
    for(int j=i+1; j<y.size();j++){
      edges.push_back(edge(i, j, distance(x[i], y[i], x[j], y[j])));
    }
  }
  sort(edges.begin(), edges.end(), compare);
  int count = 0;
  for(int i=0;i<edges.size();i++){
    edge current = edges[i];
    int u = current.u, v = current.v;
    if(Find(u, nodes) != Find(v, nodes)){
      Merge(u, v, nodes);
      count++;
    }
    if(count>x.size()-k) return current.weight;
  }
  return -1.;
} 

int main() {
  size_t n;
  int k;
  std::cin >> n;
  vector<int> x(n), y(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
  }
  std::cin >> k;
  std::cout << std::setprecision(10) << clustering(x, y, k) << std::endl;
}
