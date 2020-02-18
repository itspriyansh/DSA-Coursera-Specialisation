#include <cstdio>
#include <cassert>
#include <vector>
#include <queue>
#include <limits>
#include <utility>

using namespace std;

// External vector of size 2 - for forward and backward search.
// Internal 2-dimensional vector is vector of adjacency lists for each node.
typedef vector<vector<vector<int>>> Adj;

// Distances can grow out of int type
typedef long long Len;

// Vector of two priority queues - for forward and backward searches.
// Each priority queue stores the closest unprocessed node in its head.
typedef vector<priority_queue<pair<Len, int>,vector<pair<Len,int>>,greater<pair<Len,int>>>> Queue;

const Len INFINITY = numeric_limits<Len>::max() / 4;

class Bidijkstra {
    // Number of nodes
    int n_;
    // Graph adj_[0] and cost_[0] correspond to the initial graph,
    // adj_[1] and cost_[1] correspond to the reversed graph.
    // Graphs are stored as vectors of adjacency lists corresponding
    // to nodes.
    // Adjacency list itself is stored in adj_, and the corresponding
    // edge costs are stored in cost_.
    Adj adj_;
    Adj cost_;
    // distance_[0] stores distances for the forward search,
    // and distance_[1] stores distances for the backward search.
    vector<vector<Len>> distance_;
    // Stores all the nodes visited either by forward or backward search.
    vector<int> workset_;
    // Stores a flag for each node which is True iff the node was visited
    // either by forward or backward search.
    vector<bool> visited_;

public:
    Bidijkstra(int n, Adj adj, Adj cost)
        : n_(n), adj_(adj), cost_(cost), distance_(2, vector<Len>(n, INFINITY)), visited_(n, false)
    { workset_.reserve(n); }

    // Initialize the data structures before new query,
    // clear the changes made by the previous query.
    void clear() {
        for (int i = 0; i < workset_.size(); ++i) {
            int v = workset_[i];
            distance_[0][v] = distance_[1][v] = INFINITY;
            visited_[v] = false;
        }
        workset_.clear();
    }

    // Processes visit of either forward or backward search 
    // (determined by value of side), to node v trying to
    // relax the current distance by dist.
    void visit(Queue& q, int side, int v, Len dist) {
        // Implement this method yourself
        if(distance_[side][v] > dist){
            distance_[side][v] = dist;
            q[side].push(make_pair(dist, v));
            workset_.push_back(v);
        }
    }
    int extractMin(Queue &q, int side){
        pair<Len,int> i = q[side].top();
        q[side].pop();
        return i.second;
    }
    void Process(Queue &q, int side, int u, vector<vector<int>> &adj, const vector<vector<int>> &weight){
        for(int i=0;i<adj[u].size();i++){
            visit(q, side, adj[u][i], distance_[side][u]+weight[u][i]);
        }
    }
    Len ShortestPath(int v){
        Len dist = INFINITY;
        for(int u: workset_){
            dist = min(dist, distance_[0][u] + distance_[1][u]);
        }
        if(dist == INFINITY) return -1;
        return dist;
    }
    // Returns the distance from s to t in the graph.
    Len query(int s, int t) {
        clear();
        Queue q(2);
        visit(q, 0, s, 0);
        visit(q, 1, t, 0);
        // Implement the rest of the algorithm yourself
        while(!q[0].empty() || !q[1].empty()){
            int v = extractMin(q, 0);
            Process(q, 0, v, adj_[0], cost_[0]);
            if (visited_[v] == true)
                return ShortestPath(v);
            visited_[v] = true;
            
            int v_r = extractMin(q, 1);
            Process(q, 1, v_r, adj_[1], cost_[1]);
            if (visited_[v_r] == true)
                return ShortestPath(v_r);
            visited_[v_r] = true;
        }
        return -1;
    }
};

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    // cout<<"First jinput done"<<endl;
    Adj adj(2, vector<vector<int>>(n));
    Adj cost(2, vector<vector<int>>(n));
    for (int i=0; i<m; ++i) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        adj[0][u-1].push_back(v-1);
        cost[0][u-1].push_back(c);
        adj[1][v-1].push_back(u-1);
        cost[1][v-1].push_back(c);
    }
    // cout<<"Second input done"<<endl;
    Bidijkstra bidij(n, adj, cost);

    int t;
    scanf("%d", &t);
    for (int i=0; i<t; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        printf("%lld\n", bidij.query(u-1, v-1));
    }
    // cout<<"Third input done"<<endl;
}
