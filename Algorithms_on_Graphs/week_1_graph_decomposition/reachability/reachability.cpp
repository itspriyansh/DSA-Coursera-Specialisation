#include <iostream>
#include <vector>

using std::vector;
using std::pair;

void explore(int v, vector<bool> &visited, vector<vector<int>> &neighbours){
  visited[v] = true;
  for(int i=0;i<neighbours[v].size();i++){
    if(!visited[neighbours[v][i]])
      explore(neighbours[v][i], visited, neighbours);
  }
}

int reach(vector<vector<int> > &adj, int x, int y) {
  //write your code here
  vector<bool> visited(adj.size(), false);
  explore(x, visited, adj);
  if(visited[y])
    return 1;
  return 0;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  int x, y;
  std::cin >> x >> y;
  std::cout << reach(adj, x - 1, y - 1);
}
