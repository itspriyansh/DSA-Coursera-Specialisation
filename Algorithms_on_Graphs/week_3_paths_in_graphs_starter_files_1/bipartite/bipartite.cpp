#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int bipartite(vector<vector<int> > &adj) {
  //write your code here
  vector<int> color(adj.size(), -1);
  queue<int> Q;
  color[0] = 1;
  Q.push(0);
  while(!Q.empty()){
    int ind = Q.front();
    Q.pop();
    for(vector<int>::iterator i=adj[ind].begin();i!=adj[ind].end();i++){
      if(ind == *i)
        return 0;
      else if(color[*i]==-1){
        color[*i] = 1 - color[ind];
        Q.push(*i);
      }
      else if(color[*i] == color[ind])
        return 0;
    }
  }
  return 1;
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
  std::cout << bipartite(adj);
}
