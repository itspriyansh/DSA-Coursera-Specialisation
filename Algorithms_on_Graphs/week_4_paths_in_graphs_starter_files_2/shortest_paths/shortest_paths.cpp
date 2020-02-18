#include <iostream>
#include <limits>
#include <vector>
#include <queue>

using namespace std;

void shortest_paths(vector<vector<int> > &adj, vector<vector<long long> > &cost, int s, vector<long long> &distance, vector<int> &reachable, vector<int> &shortest) {
  //write your code here
  queue<int> Q;
  distance[s] = 0;
  reachable[s] = 1;
  for(int v=0;v<adj.size()-1;v++){
    for(int i=0;i<adj.size();i++){
      for(int j=0;j<adj[i].size();j++){
        if(distance[i]!=numeric_limits<long long>::max() && distance[adj[i][j]]>distance[i]+cost[i][j]){
          reachable[adj[i][j]] = 1;
          distance[adj[i][j]] = distance[i]+cost[i][j];
        }
      }
    }
  }
  vector<bool> visited(adj.size(), false);
  for(int i=0;i<adj.size();i++){
    for(int j=0;j<adj[i].size();j++){
      if(distance[i]!=numeric_limits<long long>::max() && distance[adj[i][j]]>distance[i]+cost[i][j]){
        Q.push(adj[i][j]);
      }
    }
  }
  while(!Q.empty()){
    int u = Q.front();
    Q.pop();
    visited[u] = true;
    shortest[u] = 0;
    for(vector<int>::iterator v=adj[u].begin();v!=adj[u].end();v++){
      if(!visited[*v]){
        Q.push(*v);
      }
    }
  }
}

int main() {
  int n, m, s;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<long long> > cost(n, vector<long long>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  std::cin >> s;
  s--;
  vector<long long> distance(n, std::numeric_limits<long long>::max());
  vector<int> reachable(n, 0);
  vector<int> shortest(n, 1);
  shortest_paths(adj, cost, s, distance, reachable, shortest);
  for (int i = 0; i < n; i++) {
    if (!reachable[i]) {
      std::cout << "*\n";
    } else if (!shortest[i]) {
      std::cout << "-\n";
    } else {
      std::cout << distance[i] << "\n";
    }
  }
}
