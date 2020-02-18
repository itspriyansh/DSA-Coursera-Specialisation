#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <limits>
#include <queue>
#include <iostream>
#include <memory>
#include <cassert>

using namespace std;
const int INFINITE = numeric_limits<int>::max() / 2;
bool compare(pair<int,int> &a, pair<int,int> &b){
    return a.second < b.second;
}
class Graph
{
    typedef int Distance;
    typedef int Vertex;

    // Number of nodes
    int N;
    // Source and target
    int s, t;
    // Estimate of the distance from s to t
    int estimate = INFINITE;
    // Lists of edges outgoing from each node
    std::vector<std::vector<std::pair<int, int>>> outgoing_edges;
    // Lists of edges incoming to each node
    std::vector<std::vector<std::pair<int, int>>> incoming_edges;
    std::vector<int> dist_;
    // static constexpr int INFINITE = std::numeric_limits<int>::max() / 2;
    // Levels of nodes for node ordering
    std::vector<int> level;
    // Ranks of nodes - positions in the node ordering
    std::vector<int> rank;

    // Distance to node v, bidistance[0][v] - from source in the forward search, bidistance[1][v] - from target
    // in the backward search.
    std::vector<std::vector<Distance>> bidistance;

    // Wrapper around STL priority_queue
    class StlHeap
    {
    public:
        using T = std::pair<Distance, Vertex>;
        using Queue = std::priority_queue<T, std::vector<T>, std::greater<T>>;

        StlHeap() {
            queue.reset(new Queue());
        }

        bool empty() const {
            return queue->empty();
        }

        void update(Vertex v, Distance d) {
            queue->push(std::make_pair(d,v));
        }

        void clear() {
            queue.reset(new Queue());
        }

        std::pair<Distance, Vertex> pop() {
            pair<Distance, Vertex> top = queue->top();
            queue->pop();
            return top;
        }

    private:
        std::unique_ptr<Queue> queue;
    };

    // Priority queues for forward and backward searches
    StlHeap diqueue[2];
public:
    Graph() {
        // incoming_edges.resize(N, vector<pair<int,int>>());
        // outgoing_edges.resize(N, vector<pair<int,int>>());
        read_stdin();
        bidistance.resize(2, std::vector<int>(N, INFINITE));
        rank.resize(N, -1);
        level.resize(N,  0);
        visited.resize(N);
    }

    int get_n() { return N;}

    std::vector<std::pair<int, int>>& get_adjacent(int v, bool forward = true) {
        if (forward) {
            return outgoing_edges[v];
        } else {
            return incoming_edges[v];
        }
    }

    void preprocess() {
        // Priority queue will store pairs of (importance, node) with the least important node in the head
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int,int>>, std::greater<std::pair<int, int>>> queue;
        // Implement the rest of the algorithm yourself
        std::queue<int> Q;
        vector<bool> visited(N, false);
        int prev = -1;
        vector<vector<Shortcut>> shortcut(N, vector<Shortcut>());
        while(find(visited.begin(), visited.end(), false) != visited.end()){
            int u = find(visited.begin(), visited.end(), false) - visited.begin();
            Q.push(u);
            visited[u] = true;
            queue.push({do_shortcut(u, shortcut[u], level[u], visited), u});
            while(!Q.empty()){
                int v = Q.back();
                Q.pop();
                for(vector<pair<int,int>>::iterator i=outgoing_edges[v].begin();i!=outgoing_edges[v].end();i++){
                    if(!visited[(*i).first]){
                        // rank[(*i).first] = ++prev;
                        Q.push((*i).first);
                        visited[(*i).first] = true;
                        queue.push({do_shortcut((*i).first, shortcut[i-outgoing_edges[v].begin()], level[(*i).first], visited), (*i).first});
                    }
                }
            }
        }
        while(!queue.empty()){
            int v = queue.top().second;
            queue.pop();
            int imp = lazy_update(v, shortcut[v]);
            if(!queue.empty() && imp > queue.top().first){
                queue.push({imp, v});
                shortcut[v].clear();
                continue;
            }
            // cout<<v+1<<" ";
            rank[v] = ++prev;
            for(int i=0;i<shortcut[v].size();i++){
                // if(rank[shortcut[v][i].from] == -1 && rank[shortcut[v][i].to] == -1)
                add_edge(shortcut[v][i].from, shortcut[v][i].to, shortcut[v][i].cost);
            }
        }
        // cout<<"Ranks: ";
        // for(int i=0;i<N;i++)
        //     cout<<rank[i]<<" ";
        // cout<<endl;
        finalize();
    }

    // Returns distance from s to t in the graph
    int query(int u, int w) {
        clear();
        update(u, 0, true);
        update(w, 0, false);
        s = u; 
        t = w;
        // Implement the rest of the algorithm yourself
        while(!diqueue[0].empty() || !diqueue[1].empty()){
            if(!diqueue[0].empty()){
                int v = diqueue[0].pop().second;
                if(bidistance[0][v] <= estimate){
                    Process(v, outgoing_edges[v], true);
                    if(bidistance[0][v]+bidistance[1][v] < estimate)
                        estimate = bidistance[0][v]+bidistance[1][v];
                }
            }
            if(!diqueue[1].empty()){
                int v_r = diqueue[1].pop().second;
                if(bidistance[1][v_r] <= estimate){
                    Process(v_r, incoming_edges[v_r], false);
                    if(bidistance[0][v_r]+bidistance[1][v_r] < estimate)
                        estimate = bidistance[0][v_r]+bidistance[1][v_r];
                }
            }
        }
        if(estimate == INFINITE) return -1;
        return estimate;
    }

private:
    // Try to relax the node v using distance d either in the forward or in the backward search
    void update(int v, int d, bool forward) {
        // Implement this method yourself
        int side = (forward ? 0 : 1);
        if(bidistance[side][v] > d){
            diqueue[side].update(v, d);
            bidistance[side][v] = d;
            visited.add(v);
        }
    }
    void clear(){
        diqueue[0].clear();
        diqueue[1].clear();
        for (int i = 0; i < visited.get().size(); ++i) {
            int v = visited.get()[i];
            bidistance[0][v] = bidistance[1][v] = INFINITE;
        }
        visited.clear();
        estimate = INFINITE;
    }
    void Process(int u, vector<pair<int,int>> &adj, bool forward){
        int side = (forward ? 0 : 1);
        for(int i=0;i<adj.size();i++){
            if(u != adj[i].first)
                update(adj[i].first, bidistance[side][u]+adj[i].second, forward);
        }
    }
    class VertexSet
    {
    public:
        VertexSet(int n = 0) : visited(n) {}
        void resize(int n) {
            visited.resize(n);
        }
        void add(int v) {
            if (!visited[v]) {
                vertices.push_back(v);
                visited[v] = true;
            }
        }
        const std::vector<int>& get() const {
            return vertices;
        }
        const bool has(int v) {
            return visited[v];
        }
        void clear() {
            for (int v : vertices) {
                visited[v] = false;
            }
            vertices.clear();
        }

    private:
        std::vector<int> visited;
        std::vector<int> vertices;
    };
    VertexSet visited;
    // QEntry = (distance, vertex)
    typedef std::pair<int,int> QEntry;
    std::priority_queue<QEntry, std::vector<QEntry>, std::greater<QEntry>> queue;

    struct Shortcut {
        int from;
        int to;
        int cost;
        bool operator == (const Shortcut &b) {
            return (from == b.from && to == b.to);
        }
    };
    // Adds all the shortcuts for the case when node v is contracted, and returns the importance of node v
    // in this case
    int do_shortcut(int v, std::vector<Shortcut>& shortcuts, int& mylevel, vector<bool> &visit) {
        // // Implement this method yourself                 
        // priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> Q;
        // // vector<bool> incoming_flag(incoming_edges[v].size(), false);
        // // vector<bool> outgoing_flag(outgoing_edges[v].size(), false);

        // vector<pair<int,int>>::iterator itr = max_element(incoming_edges[v].begin(), incoming_edges[v].end(), compare);
        // vector<pair<int,int>>::iterator itr_ = max_element(outgoing_edges[v].begin(), outgoing_edges[v].end(), compare);
        // int len = 0;
        // if(itr!=incoming_edges[v].end()) len += (*itr).second;
        // if(itr_!=outgoing_edges[v].end()) len += (*itr_).second;
        // int count = 0;
        // for(vector<pair<int,int>>::iterator q=incoming_edges[v].begin();q!=incoming_edges[v].end();q++){
        //     pair<int,int> i = *q;
        //     int a = i.first;
        //     visited.clear();
        //     dist_[a] = 0;
        //     visited.add(a);
        //     int limit = 5 * outgoing_edges[a].size(), present=1, future = 0;
        //     Q.push({0,a});
        //     while(!Q.empty() && limit>=0){
        //         int u = Q.top().second;
        //         Q.pop();
        //         for(pair<int,int> w: outgoing_edges[u]){
        //             if(w.first != v && (!visited.has(w.first) || dist_[w.first] > dist_[u]+w.second)){
        //                 dist_[w.first] = dist_[u]+w.second;
        //                 visited.add(w.first);
        //                 if(dist_[w.first] <= len){
        //                     Q.push({dist_[w.first], w.first});
        //                 }
        //                 limit--;
        //             }
        //         }
        //     }
        //     for(vector<pair<int,int>>::iterator r=outgoing_edges[v].begin();r!=outgoing_edges[v].end();r++){
        //         pair<int,int> j = *r;
        //         if(!visited.has(j.first) || dist_[j.first] > i.second+j.second){
        //             count++;

        //             // outgoing_flag[r-outgoing_edges[v].begin()] = true;
        //             // incoming_flag[q-incoming_edges[v].begin()] = true;
        //         }
        //     }
        // }

        // // int short_cover = 0;
        // // for(int i=0;i<incoming_flag.size();i++)
        // //     if(incoming_flag[i])
        // //         short_cover++;
        // // for(int j=0;j<outgoing_flag.size();j++)
        // //     if(outgoing_flag[j])
        // //         short_cover++;

        // int cont_neigh = 0;
        // for(pair<int,int> i: incoming_edges[v]){
        //     if(visit[i.first]){
        //         cont_neigh++;
        //         mylevel = max(mylevel, 1+level[i.first]);
        //     }
        // }
        // for(pair<int,int> i: outgoing_edges[v]){
        //     if(visit[i.first]){
        //         cont_neigh++;
        //         mylevel = max(mylevel, 1+level[i.first]);
        //     }
        // }
        // // Add neighbors and shortcut cover heuristics
        // return (count - outgoing_edges[v].size() - incoming_edges[v].size()) +  cont_neigh + mylevel;
        return incoming_edges[v].size()*outgoing_edges[v].size();
    }
    int lazy_update(int v, std::vector<Shortcut>& shortcuts){
        level[v] = 0;
        // vector<bool> incoming_flag(incoming_edges[v].size(), false);
        // vector<bool> outgoing_flag(outgoing_edges[v].size(), false);
        shortcuts.clear();
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> Q;
        vector<pair<int,int>>::iterator itr = max_element(incoming_edges[v].begin(), incoming_edges[v].end(), compare);
        vector<pair<int,int>>::iterator itr_ = max_element(outgoing_edges[v].begin(), outgoing_edges[v].end(), compare);
        int len = 0;
        if(itr!=incoming_edges[v].end()) len += (*itr).second;
        if(itr_!=outgoing_edges[v].end()) len += (*itr_).second;
        for(int i=0;i<incoming_edges[v].size();i++){
            pair<int,int> x = incoming_edges[v][i];
            if(rank[x.first] != -1) continue;
            visited.clear();
            dist_[x.first] = 0;
            visited.add(x.first);
            Q.push({0,x.first});
            while(!Q.empty()){
                int u = Q.top().second;
                Q.pop();
                for(pair<int,int> w: outgoing_edges[u]){
                    if(w.first != v && rank[w.first] == -1 && (!visited.has(w.first) || dist_[w.first] > dist_[u]+w.second)){
                        dist_[w.first] = dist_[u]+w.second;
                        visited.add(w.first);
                        if(dist_[w.first] <= len){
                            Q.push({dist_[w.first], w.first});
                        }
                    }
                }
            }

            for(int j=0;j<outgoing_edges[v].size();j++){
                pair<int,int> y = outgoing_edges[v][j];
                if(rank[y.first] != -1) continue;
                if(!visited.has(y.first) || dist_[y.first] > x.second+y.second){
                    Shortcut s;
                    s.from = x.first;
                    s.to = y.first;
                    s.cost = x.second+y.second;
                    shortcuts.push_back(s);
                    // incoming_flag[i] = true;
                    // outgoing_flag[j] = true;
                }
            }
        }

        // int short_cover = 0;
        // for(int i=0;i<incoming_flag.size();i++)
        //     if(incoming_flag[i])
        //         short_cover++;
        // for(int j=0;j<outgoing_flag.size();j++)
        //     if(outgoing_flag[j])
        //         short_cover++;
        int cont_neigh = 0;
        for(pair<int,int> i: incoming_edges[v]){
            if(rank[i.first]!=-1){
                cont_neigh++;
                level[v] = max(level[v], 1+level[i.first]);
            }
        }
        for(pair<int,int> i: outgoing_edges[v]){
            if(rank[i.first]!=-1){
                cont_neigh++;
                level[v] = max(level[v], 1+level[i.first]);
            }
        }
        return (shortcuts.size() - outgoing_edges[v].size() - incoming_edges[v].size()) + cont_neigh + level[v];
    }
    void set_n(int n) {
        N = n;
        outgoing_edges.resize(n);
        incoming_edges.resize(n);
        dist_.resize(n, INFINITE);
    }


    void add_edge_to_list(std::vector<std::pair<int,int>>& list, int w, int c) {
        for (int i = 0; i < list.size(); ++i) {
            std::pair<int, int>& p = list[i];
            if (p.first == w) {
                if (p.second > c) {
                    p.second = c;
                }
                return;
            }
        }
        list.push_back({w, c});
    }

    void add_directed_edge(int u, int v, int c) {
        add_edge_to_list(outgoing_edges[u], v, c);
        add_edge_to_list(incoming_edges[v], u, c);
    }

    void add_edge(int u, int v, int c) {
        add_directed_edge(u, v, c);
    }

    void finalize() {
        // Remove unnecessary edges
        for(int i=0;i<N;i++){
            for(int j=0;j<outgoing_edges[i].size();j++){
                if(rank[i] > rank[outgoing_edges[i][j].first])
                    outgoing_edges[i].erase(outgoing_edges[i].begin()+(j--));
            }
        }
        for(int i=0;i<N;i++){
            for(int j=0;j<incoming_edges[i].size();j++){
                if(rank[i] > rank[incoming_edges[i][j].first])
                    incoming_edges[i].erase(incoming_edges[i].begin()+(j--));
            }
        }
        visited.clear();
        // cout<<"Outgoing Edges: "<<endl; 
        // for(int i=0;i<N;i++){
        //     sort(outgoing_edges[i].begin(), outgoing_edges[i].end());
        //     for(int j=0;j<outgoing_edges[i].size();j++){
        //         cout<<i+1<<": "<<outgoing_edges[i][j].first+1<<" "<<outgoing_edges[i][j].second<<endl;
        //     }
        // }cout<<"Incoming Edges: "<<endl; 
        // for(int i=0;i<N;i++){
        //     sort(incoming_edges[i].begin(), incoming_edges[i].end());
        //     for(int j=0;j<incoming_edges[i].size();j++){
        //         cout<<i+1<<": "<<incoming_edges[i][j].first+1<<" "<<incoming_edges[i][j].second<<endl;
        //     }
        // }
    }

    bool read_stdin() {
        int u,v,c,n,m;
        assert(scanf("%d %d", &n, &m) == 2);
        set_n(n);
        for (int i = 0; i < m; ++i) {
            assert(scanf("%d %d %d", &u, &v, &c) == 3);
            add_edge(u-1, v-1, c);
        }
        // finalize();
        return true;
    }
};

int main() {
    Graph g;
    g.preprocess();
    std::cout << "Ready" << std::endl;

    int t;
    assert(scanf("%d", &t) == 1);
    for (int i = 0; i < t; ++i) {
        int u, v;
        assert(scanf("%d %d", &u, &v) == 2);
        printf("%d\n", g.query(u-1, v-1));
    }
}
