#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class FlowGraph {
public:
    struct Edge {
        int from, to, capacity, flow;
    };

private:
    vector<Edge> edges;
    vector<vector<size_t> > graph;
    vector<int> in, out, low;

public:
	int limit;
    explicit FlowGraph(size_t n): graph(n), in(n,0), out(n,0), limit(0) {}

    void add_edge(int from, int to, int lower, int capacity) {
        Edge forward_edge = {from, to, capacity-lower, 0};
        Edge backward_edge = {to, from, 0, 0};
        graph[from].push_back(edges.size());
        edges.push_back(forward_edge);
        graph[to].push_back(edges.size());
        edges.push_back(backward_edge);
        in[to]+=lower;
        out[from]+=lower;
        limit += lower;
        low.push_back(lower);
    }

    void addSourceAndSink(){
    	int n=in.size()-1;
    	for(int i=1;i<n;i++){
    		Edge forward_edge = {0, i, in[i], 0};
        	Edge backward_edge = {i, 0, 0, 0};
        	graph[0].push_back(edges.size());
	        edges.push_back(forward_edge);
	        graph[i].push_back(edges.size());
	        edges.push_back(backward_edge);
	        forward_edge = {i, n, out[i], 0};
        	backward_edge = {n, i, 0, 0};
        	graph[i].push_back(edges.size());
	        edges.push_back(forward_edge);
	        graph[n].push_back(edges.size());
	        edges.push_back(backward_edge);   
    	}
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
        edges[id].flow += flow;
        edges[id ^ 1].flow -= flow;
    }

    bool findPath(vector<int>& prev){
        vector<int> dist(graph.size(), INT32_MAX);
        dist[0] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > Q;
        Q.push(make_pair(dist[0], 0));
        while(dist[graph.size()-1]==INT32_MAX && !Q.empty()){
            int next = Q.top().second;
            Q.pop();
            for(vector<size_t>::iterator it=graph[next].begin();it!=graph[next].end();it++){
                if(edges[*it].capacity == 0) continue;
                if(dist[next]+1 < dist[edges[*it].to]){
                    prev[edges[*it].to] = *it;
                    dist[edges[*it].to] = dist[next]+1;
                    Q.push(make_pair(dist[edges[*it].to], edges[*it].to));
                }
                if(dist[graph.size()-1]<INT32_MAX)
                    return true;
            }
        }
        if(dist[graph.size()-1]==INT32_MAX)
            return false;
        return true;
    }

    void findResidue(){
        for(int i=0;i<edges.size();i++){
            if(edges[i].flow != 0){
                edges[i].capacity -= edges[i].flow;
                // edges[i^1].capacity += edges[i].flow;
                edges[i].flow = 0;
            }
        }
    }
    void printResult(){
    	for(int i=0,j=1;i<low.size();i++,j+=2){
    		cout<<edges[j].capacity+low[i]<<endl;
    	}
    }
};

FlowGraph read_data() {
    int vertex_count, edge_count;
    std::cin >> vertex_count >> edge_count;
    vertex_count+=2;
    FlowGraph graph(vertex_count);
    for (int i = 0; i < edge_count; ++i) {
        int u, v, capacity, lower;
        std::cin >> u >> v >> lower >> capacity;
        graph.add_edge(u, v, lower, capacity);
    }
    graph.addSourceAndSink();
    return graph;
}

void max_flow(FlowGraph& graph, int from, int to) {
    int flow = 0;
    /* your code goes here */
    vector<int> prev(graph.size(), -1);
    while(graph.findPath(prev)){
        int itr = graph.size()-1;
        int trace = INT32_MAX;
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
    // cout<<"Flow->"<<flow<<endl;
    if(flow==graph.limit){
    	cout<<"YES\n";
    	graph.printResult();
    }else{
    	cout<<"NO\n";
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    FlowGraph graph = read_data();

    max_flow(graph, 0, graph.size() - 1);
    return 0;
}