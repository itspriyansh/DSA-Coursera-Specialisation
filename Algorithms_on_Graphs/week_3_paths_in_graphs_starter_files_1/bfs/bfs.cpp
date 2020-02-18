#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int distance(vector<vector<int> > &adj, int s, int t) {
  //write your code here
  vector<int> dist(adj.size(), -1);
  queue<int> Q;
  Q.push(s);
  dist[s] = 0;
  while(!Q.empty()){
    int ind = Q.front();
    Q.pop();
    for(vector<int>::iterator i=adj[ind].begin();i!=adj[ind].end();i++){
      if(dist[*i]==-1){
        Q.push(*i);
        dist[*i] = dist[ind]+1;
      }
    }
  }
  return dist[t];
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, s, t);
}
