#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <stack>

using namespace std;

class StockCharts {
 public:
  void Solve() {
    vector<vector<int>> stock_data = ReadData();
    int result = MinCharts(stock_data);
    WriteResponse(result);
  }

 private:
  vector<vector<int>> ReadData() {
    int num_stocks, num_points;
    cin >> num_stocks >> num_points;
    vector<vector<int>> stock_data(num_stocks, vector<int>(num_points));
    for (int i = 0; i < num_stocks; ++i)
      for (int j = 0; j < num_points; ++j) {
        cin >> stock_data[i][j];
      }
    return stock_data;
  }

  void WriteResponse(int result) {
    cout << result << "\n";
  }

  int MinCharts(const vector<vector<int>>& stock_data) {
    // Replace this incorrect greedy algorithm with an
    // algorithm that correctly finds the minimum number
    // of charts on which we can put all the stock data
    // without intersections of graphs on one chart.

    int x = stock_data.size();
    // Vector of charts; each chart is a vector of indices of individual stocks.
    vector<vector<bool>> adj(2*(x+1), vector<bool>(2*(x+1), false));
    for(int i=0;i<x;i++){
      adj[0][i+1] = true;
      adj[i+x+1][2*x+1] = true;
    }
    for(int i=0;i<x;i++){
      for(int j=0;j<x;j++){
        if(i!=j){
          adj[i+1][j+x+1] = compare(stock_data[i], stock_data[j]);
        }
      }
    }
    vector<int> match(x, -1);

    while(true){
      stack<int> list;
      vector<int> prev(2*(x+1), -1);
      vector<bool> visited(2*(x+1), false);
      list.push(0);
      visited[0] = true;
      while(!list.empty() && !visited.back()){
        int next = list.top();
        list.pop();
        for(int i=2*x+1;i>=0;i--){
          if(adj[next][i] && !visited[i]){
            prev[i] = next;
            list.push(i);
            visited[i] = true;
          }
        }
      }
      if(!visited.back()) break;
      
      for(int itr = 2*x+1;itr!=0;itr=prev[itr]){
        if(prev[itr]>0 && prev[itr]<x+1){
          match[prev[itr]-1] = itr-x-1;
        }
        adj[prev[itr]][itr] = false;
        adj[itr][prev[itr]] = true;
      }
    }
    int count = 0;
    // vector<bool> visited = false;
    // for(int z=0;z<match.size();z++){
    //   if(visited[z]) continue;
    //   count++;
    //   visited[z] = true;
    //   for(int i=z;match[i]!=-1;i=match[i]){
    //     for(int j=match[i];j!=-1;j=match[j]){
    //       bool flag = (stock_data[i][0]<stock_data[j][0])?stoc
    //     }
    //   }
    // }
    for(int i=0;i<match.size();i++){
      if(match[i]==-1){
        count++;
      }
    }
    return count;
  }

  bool compare(const vector<int>& stock1, const vector<int>& stock2) {
    for (int i = 0; i < stock1.size(); ++i)
      if (stock1[i] >= stock2[i])
        return false;
    return true;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  StockCharts stock_charts;
  stock_charts.Solve();
  return 0;
}
