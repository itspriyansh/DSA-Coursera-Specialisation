#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void explore(int v, vector<bool> &visited, vector<vector<int>> &adj){
  visited[v] = true;
  // cout<<v<<" ";
  for(vector<int>::iterator i=adj[v].begin(); i!=adj[v].end(); i++){
    if(!visited[*i]) explore(*i, visited, adj);
  }
}

void dfs(vector<vector<int>> &adj, vector<bool> &visited, vector<int> &order, int v){
  visited[v] = true;
  for(int i=0;i<adj[v].size();i++)
    if(!visited[adj[v][i]])
      dfs(adj, visited, order, adj[v][i]);
  order.push_back(v);
}

int number_of_strongly_connected_components(vector<vector<int> > adj, vector<vector<int> > reverse) {
  //write your code here
  vector<bool> visited(adj.size(), false);
  vector<int> order;
  for(int i=0;i<adj.size();i++)
    if(!visited[i])
      dfs(reverse, visited, order, i);
  fill(visited.begin(), visited.end(), false);
  int res = 0;
  for(int i=order.size()-1;i>=0;i--){
    if(!visited[order[i]]){
      explore(order[i], visited, adj);
      res++;
      // cout<<endl;
    }
  }
  return res;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  //Reverse Graph
  vector<vector<int> > adjReverse(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adjReverse[y - 1].push_back(x - 1);
  }
  std::cout << number_of_strongly_connected_components(adj, adjReverse);
}
