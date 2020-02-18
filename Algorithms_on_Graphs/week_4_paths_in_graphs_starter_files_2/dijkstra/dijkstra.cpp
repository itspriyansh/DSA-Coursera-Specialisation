#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class comparison{
  public:
    bool operator() (pair<int, int> &a, pair<int, int> &b){
      return a.second>b.second;
    }
};

int distance(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, int t) {
  //write your code here
  vector<int> dist(adj.size(), INT16_MAX);
  vector<int> prev(adj.size(), -1);
  dist[s] = 0;
  priority_queue<pair<int, int>, vector<pair<int,int>>, comparison> Q;
  Q.push(make_pair(s, dist[s]));
  while(!Q.empty()){
    int u = Q.top().first;
    Q.pop();
    for(int v=0;v<adj[u].size();v++){
      if(dist[adj[u][v]]>dist[u]+cost[u][v]){
        dist[adj[u][v]] = dist[u] + cost[u][v];
        prev[v] = u;
        Q.push(make_pair(adj[u][v], dist[adj[u][v]]));
      }
    }
  }
  if(dist[t]==INT16_MAX)
    return -1;
  return dist[t];
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
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, cost, s, t);
}
