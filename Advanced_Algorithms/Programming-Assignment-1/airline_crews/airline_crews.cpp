#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <stack>

using namespace std;

class MaxMatching {
 public:
  void Solve() {
    vector<vector<bool>> adj_matrix = ReadData();
    vector<int> matching = FindMatching(adj_matrix);
    WriteResponse(matching);
  }

 private:
  vector<vector<bool>> ReadData() {
    int num_left, num_right;
    cin >> num_left >> num_right;
    vector<vector<bool>> adj_matrix(num_left, vector<bool>(num_right));
    for (int i = 0; i < num_left; ++i)
      for (int j = 0; j < num_right; ++j) {
        int bit;
        cin >> bit;
        adj_matrix[i][j] = (bit == 1);
      }
    return adj_matrix;
  }

  void WriteResponse(const vector<int>& matching) {
    for (int i = 0; i < matching.size(); ++i) {
      if (i > 0)
        cout << " ";
      if (matching[i] == -1)
        cout << "-1";
      else
        cout << (matching[i] + 1);
    }
    cout << "\n";
  }

  vector<int> FindMatching(const vector<vector<bool>>& adj_matrix) {
    // Replace this code with an algorithm that finds the maximum
    // matching correctly in all cases.
    int rows = adj_matrix.size();
    int cols = adj_matrix[0].size();
    vector<int> matching(rows, -1);

    // Building the Graph
    vector<vector<bool>> adj(rows+cols+2, vector<bool>(rows+cols+2, false));
    for(int i=0;i<rows;i++){
      adj[0][i+1] = true;
    }
    for(int i=0;i<cols;i++){
      adj[i+rows+1][rows+cols+1] = true;
    }
    for(int i=0;i<rows;i++){
      for(int j=0;j<cols;j++){
        if(adj_matrix[i][j]){
          adj[i+1][j+rows+1] = true;
        }
      }
    }

    while(true){
      stack<int> list;
      vector<int> prev(rows+cols+2, -1);
      vector<bool> visited(rows+cols+2, false);
      visited[0] = true;
      list.push(0);
      while(!list.empty() && prev.back()==-1){
        int next = list.top();
        list.pop();
        for(int i=adj[next].size()-1;i>=0;i--){
          if(adj[next][i] && !visited[i]){
            list.push(i);
            prev[i] = next;
            visited[i] = true;
          }
        }
      }
      if(prev.back()==-1) break;
      // cout<<"Prev:"<<endl;
      for(int itr = rows+cols+1;itr!=0;itr = prev[itr]){
        // cout<<itr<<" ";
        if(prev[itr]>0 && prev[itr]<rows+1){
          matching[prev[itr]-1] = itr-rows-1;
        }
        adj[prev[itr]][itr] = false;
        adj[itr][prev[itr]] = true;
      }
    }

    return matching;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  MaxMatching max_matching;
  max_matching.Solve();
  return 0;
}