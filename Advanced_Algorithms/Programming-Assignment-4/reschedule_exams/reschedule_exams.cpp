#include <iostream>
#include <vector>
#include <string>
#include <stack>
using namespace std;

/*
  Arguments:
    * `n` - the number of vertices.
    * `edges` - list of edges, each edge is a pair (u, v), 1 <= u, v <= n.
    * `colors` - string consisting of `n` characters, each belonging to the set {'R', 'G', 'B'}.
  Return value:
    * If there exists a proper recoloring, return value is a string containing new colors, similar to the `colors` argument.
    * Otherwise, return value is an empty string.
*/

void fillOrder(int v, vector<vector<int>>& adj, stack<int>& order, vector<bool>& visited){
    visited[v]=true;
    for(int i: adj[v]){
        if(!visited[i]){
            fillOrder(i, adj, order, visited);
        }
    }
    order.push(v);
}

void dfs(int v, vector<vector<int>>& adj, vector<bool>& visited, vector<int>& scc){
    visited[v] = true;
    scc.push_back(v);
    for(int i: adj[v]){
        if(!visited[i]){
            dfs(i, adj, visited, scc);
        }
    }
}

string assign_new_colors(int n, vector<pair<int, int>> edges, string colors) {
    // Insert your code here.
    vector<pair<int,int>> sat;
    for(int i=0;i<n;i++){
        int l, m, n;
        if(colors[i]=='R'){
            l=1;m=2;n=3;
        }else if(colors[i]=='G'){
            l=2;m=1;n=3;
        }else{
            l=3;m=1;n=2;
        }
        sat.push_back(make_pair(i*-3-l, 0));
        sat.push_back(make_pair(i*3+m, i*3+n));
        sat.push_back(make_pair(i*-3-m, i*-3-n));
    }
    for(pair<int,int> edge: edges){
        sat.push_back(make_pair(edge.first*-3+2, edge.second*-3+2));
        sat.push_back(make_pair(edge.first*-3+1, edge.second*-3+1));
        sat.push_back(make_pair(edge.first*-3, edge.second*-3));
    }

    // cout<<"Clauses Written: "<<sat.size()<<" "<<3*n<<endl;
    // for(pair<int,int> clause: sat){
    //     cout<<clause.first<<" V "<<clause.second<<endl;
    // }

    vector<vector<int>> adj(6*n+1, vector<int>()), adj2(6*n+1, vector<int>());
    for(pair<int,int> clause: sat){
        if(clause.second==0){
            adj[-1*clause.first+3*n].push_back(clause.first+3*n);
            adj2[clause.first+3*n].push_back(-1*clause.first+3*n);
        }else{
            adj[-1*clause.first+3*n].push_back(clause.second+3*n);
            adj[-1*clause.second+3*n].push_back(clause.first+3*n);
            adj2[clause.first+3*n].push_back(-1*clause.second+3*n);
            adj2[clause.second+3*n].push_back(-1*clause.first+3*n);
        }
    }
    stack<int> order;
    vector<bool> visited(6*n+1, false);
    for(int i=0;i<=6*n;i++){
        if(!visited[i]){
            fillOrder(i, adj, order, visited);
        }
    }

    fill(visited.begin(), visited.end(), false);
    vector<vector<int>> scc;
    while(!order.empty()){
        int v = order.top();
        order.pop();
        if(!visited[v]){
            scc.push_back({});
            dfs(v, adj2, visited, scc.back());
        }
    }

    for(int i=0;i<scc.size();i++){
        if(scc[i].empty() || scc[i][0]==3*n){
            scc.erase(scc.begin()+i--);
            continue;
        }
        for(int j=0;j<scc[i].size()-1;j++){
            for(int k=j+1;k<scc[i].size();k++){
                if(scc[i][j]+scc[i][k]==6*n){
                    return "";
                }
            }
        }
    }

    vector<int> result(3*n, 0);
    for(int i=scc.size()-1;i>=0;i--){
        for(int j: scc[i]){
            int val = (j>3*n ? j-3*n : 3*n-j);
            if(result[val-1]==0){
                result[val-1] = j-3*n;
            }
        }
    }

    // cout<<"Result: ";
    // for(int el: result){
    //     cout<<el<<" ";
    // }cout<<endl;

    string colours;
    for(int i=0;i<n;i++){
        for(int j=1;j<=3;j++){
            if(result[3*i+j-1]>0){
                if(j==1) colours += "R";
                else if(j==2) colours += "G";
                else colours += "B";
                break;
            }
        }
    }
    return colours;
}

int main() {
    int n, m;
    cin >> n >> m;
    string colors;
    cin >> colors;
    vector<pair<int, int> > edges;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        edges.push_back(make_pair(u, v));
    }
    string new_colors = assign_new_colors(n, edges, colors);
    if (new_colors.empty()) {
        cout << "Impossible";
    } else {
        cout << new_colors << endl;
    }
}
