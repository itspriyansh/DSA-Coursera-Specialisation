#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/* This class implements a bit unusual scheme for storing edges of the graph,
 * in order to retrieve the backward edge for a given edge quickly. */
class FlowGraph {
public:
    struct Edge {
        int from, to, capacity, flow;
    };

private:
    /* List of all - forward and backward - edges */
    vector<Edge> edges;

    /* These adjacency lists store only indices of edges in the edges list */
    vector<vector<size_t> > graph;

public:
    explicit FlowGraph(size_t n): graph(n) {}

    void add_edge(int from, int to, int capacity) {
        /* Note that we first append a forward edge and then a backward edge,
         * so all forward edges are stored at even indices (starting from 0),
         * whereas backward edges are stored at odd indices in the list edges */
        Edge forward_edge = {from, to, capacity, 0};
        Edge backward_edge = {to, from, 0, 0};
        graph[from].push_back(edges.size());
        edges.push_back(forward_edge);
        graph[to].push_back(edges.size());
        edges.push_back(backward_edge);
    }

    size_t size() const {
        return graph.size();
    }

    const vector<size_t>& get_ids(int from) const {
        return graph[from];
    }

    const Edge& get_edge(size_t id) const {
        return edges[id];
    }

    void add_flow(size_t id, int flow) {
        /* To get a backward edge for a true forward edge (i.e id is even), we should get id + 1
         * due to the described above scheme. On the other hand, when we have to get a "backward"
         * edge for a backward edge (i.e. get a forward edge for backward - id is odd), id - 1
         * should be taken.
         *
         * It turns out that id ^ 1 works for both cases. Think this through! */
        edges[id].flow += flow;
        edges[id ^ 1].flow -= flow;
    }

    bool findPath(vector<int>& prev){
        vector<int> dist(graph.size(), INT16_MAX);
        dist[0] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > Q;
        Q.push(make_pair(dist[0], 0));
        while(dist[graph.size()-1]==INT16_MAX && !Q.empty()){
            int next = Q.top().second;
            Q.pop();
            for(vector<size_t>::iterator it=graph[next].begin();it!=graph[next].end();it++){
                if(edges[*it].capacity == 0) continue;
                if(dist[next]+1 < dist[edges[*it].to]){
                    prev[edges[*it].to] = *it;
                    dist[edges[*it].to] = dist[next]+1;
                    Q.push(make_pair(dist[edges[*it].to], edges[*it].to));
                }
                if(dist[graph.size()-1]<INT16_MAX)
                    return true;
            }
        }
        if(dist[graph.size()-1]==INT16_MAX)
            return false;
        return true;
    }

    void findResidue(){
        for(int i=0;i<edges.size();i++){
            if(edges[i].flow > 0){
                edges[i].capacity -= edges[i].flow;
                edges[i^1].capacity += edges[i].flow;
                edges[i].flow = 0;
            }
        }
    }
};

FlowGraph read_data() {
    int vertex_count, edge_count;
    std::cin >> vertex_count >> edge_count;
    FlowGraph graph(vertex_count);
    for (int i = 0; i < edge_count; ++i) {
        int u, v, capacity;
        std::cin >> u >> v >> capacity;
        graph.add_edge(u - 1, v - 1, capacity);
    }
    return graph;
}

int max_flow(FlowGraph& graph, int from, int to) {
    int flow = 0;
    /* your code goes here */
    vector<int> prev(graph.size(), -1);
    while(graph.findPath(prev)){
        int itr = graph.size()-1;
        // int trace = edges[prev[itr]].capacity;
        // itr = edges[prev[itr]].from;
        int trace = INT16_MAX;
        while(itr>0){
            FlowGraph::Edge ed = graph.get_edge(prev[itr]);
            if(trace > ed.capacity){
                trace = ed.capacity;
            }
            itr = ed.from;
        }
        flow += trace;
        itr = graph.size()-1;
        while(itr>0){
            graph.add_flow(prev[itr], trace);
            FlowGraph::Edge ed = graph.get_edge(prev[itr]);
            itr = ed.from;
        }
        graph.findResidue();
        for(vector<int>::iterator it=prev.begin();it!=prev.end();it++){
            *it = -1;
        }
    }
    return flow;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    FlowGraph graph = read_data();

    std::cout << max_flow(graph, 0, graph.size() - 1) << "\n";
    return 0;
}
