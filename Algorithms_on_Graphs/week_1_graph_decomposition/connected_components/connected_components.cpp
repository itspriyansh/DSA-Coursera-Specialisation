#include <iostream>
#include <vector>

using std::vector;
using std::pair;

void explore(int v, vector<bool> &visited, vector<vector<int>> &N){
  visited[v] = true;
  for(int i=0;i<N[v].size();i++){
    if(!visited[N[v][i]])
      explore(N[v][i], visited, N);
  }
}

int number_of_components(vector<vector<int> > &adj) {
  int res = 0;
  //write your code here
  vector<bool> visited(adj.size(), false);
  for(int i=0;i<adj.size();i++){
    if(!visited[i]){
      explore(i, visited, adj);
      res++;
    }
  }
  return res;
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
  std::cout << number_of_components(adj);
}
