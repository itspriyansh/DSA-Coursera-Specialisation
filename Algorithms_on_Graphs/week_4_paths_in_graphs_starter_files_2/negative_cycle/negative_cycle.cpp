#include <iostream>
#include <vector>

using std::vector;

int negative_cycle(vector<vector<int> > &adj, vector<vector<int> > &cost) {
  //write your code here
  vector<int> dist(adj.size(), INT16_MAX);
  dist[0] = 0;
  for(int v=0;v<adj.size()-1;v++){
    bool change = false;
    for(int i=0;i<adj.size();i++){
      for(int j=0;j<adj[i].size();j++){
        if(dist[adj[i][j]]>dist[i]+cost[i][j]){
          change = true;
          dist[adj[i][j]] = dist[i]+cost[i][j];
        }
      }
    }
    if(!change) return 0;
  }
  for(int i=0;i<adj.size();i++){
    for(int j=0;j<adj[i].size();j++){
      if(dist[adj[i][j]]>dist[i]+cost[i][j]){
        return 1;
      }
    }
  }
  return 0;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  std::cout << negative_cycle(adj, cost);
}
