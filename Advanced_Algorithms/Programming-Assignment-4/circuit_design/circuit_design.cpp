#include <bits/stdc++.h>
#include <sys/resource.h>
using namespace std;

struct Clause {
    int firstVar;
    int secondVar;
};

struct TwoSatisfiability {
    int numVars;
    vector<vector<int>> adj, adj2;

    TwoSatisfiability(int n, int m) :
        numVars(n),
        adj(2*n+1),
        adj2(2*n+1)
    {  }

    void fillOrder(int v, stack<int>& order, vector<bool>& visited){
        visited[v]=true;
        for(int i: adj[v]){
            if(!visited[i]){
                fillOrder(i, order, visited);
            }
        }
        order.push(v);
    }

    void dfs(int v, vector<bool>& visited, vector<int>& scc){
        visited[v] = true;
        scc.push_back(v);
        for(int i: adj2[v]){
            if(!visited[i]){
                dfs(i, visited, scc);
            }
        }
    }

    bool isSatisfiable(vector<int>& result) {
        // This solution tries all possible 2^n variable assignments.
        // It is too slow to pass the problem.
        // Implement a more efficient algorithm here.
        stack<int> order;
        vector<bool> visited(2*numVars+1, false);
        for(int i=0;i<=2*numVars;i++){
            if(!visited[i]){
                fillOrder(i, order, visited);
            }
        }

        fill(visited.begin(), visited.end(), false);
        vector<vector<int>> scc;
        while(!order.empty()){
            int v = order.top();
            order.pop();
            if(!visited[v]){
                scc.push_back({});
                dfs(v, visited, scc.back());
            }
        }

        for(int i=0;i<scc.size();i++){
            if(scc[i].empty() || scc[i][0]==numVars){
                scc.erase(scc.begin()+i--);
                continue;
            }
        }
        for(int i=scc.size()-1;i>=0;i--){
            for(int j=0;j<scc[i].size();j++){
                int val = (scc[i][j]>numVars ? scc[i][j]-numVars : numVars-scc[i][j]);
                if(result[val-1]==0){
                    result[val-1] = scc[i][j]-numVars;
                }else if(j>0){
                    int prev = (scc[i][j-1]>numVars ? scc[i][j-1]-numVars : numVars-scc[i][j-1]);
                    if(result[val-1]!=scc[i][j]-numVars && result[prev-1]==scc[i][j-1]-numVars){
                        return false;
                    }
                }
            }
        }
        return true;
    }
};

int main() {
    // This code is here to increase the stack size to avoid stack overflow
    // in depth-first search.
    const rlim_t kStackSize = 64L * 1024L * 1024L;  // min stack size = 64 Mb
    struct rlimit rl;
    int res;
    res = getrlimit(RLIMIT_STACK, &rl);
    if (res == 0)
    {
        if (rl.rlim_cur < kStackSize)
        {
            rl.rlim_cur = kStackSize;
            res = setrlimit(RLIMIT_STACK, &rl);
            if (res != 0)
            {
                fprintf(stderr, "setrlimit returned result = %d\n", res);
            }
        }
    }

    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    TwoSatisfiability twoSat(n, m);
    for (int i = 0; i < m; ++i) {
        // cin >> twoSat.clauses[i].firstVar >> twoSat.clauses[i].secondVar;
        Clause clause;
        cin>>clause.firstVar>>clause.secondVar;
        twoSat.adj[-1*clause.firstVar+n].push_back(clause.secondVar+n);
        twoSat.adj[-1*clause.secondVar+n].push_back(clause.firstVar+n);
        twoSat.adj2[clause.firstVar+n].push_back(-1*clause.secondVar+n);
        twoSat.adj2[clause.secondVar+n].push_back(-1*clause.firstVar+n);
    }

    vector<int> result(n, 0);
    if (twoSat.isSatisfiable(result)) {
        cout << "SATISFIABLE" << endl;
        for (int i = 1; i <= n; ++i) {
            // if (result[i-1]) {
            //     cout << -i;
            // } else {
            //     cout << i;
            // }
            cout<<result[i-1];
            if (i < n) {
                cout << " ";
            } else {
                cout << endl;
            }
        }
    } else {
        cout << "UNSATISFIABLE" << endl;
    }

    return 0;
}
