#include <iostream>
#include <algorithm>
#include <vector>

using std::vector;
using std::min;
using std::make_pair;
typedef vector<vector<int> > Matrix;

const int INF = 1e9;

Matrix read_data() {
    int vertex_count, edge_count;
    std::cin >> vertex_count >> edge_count;
    Matrix graph(vertex_count, vector<int>(vertex_count, INF));
    for (int i = 0; i < edge_count; ++i) {
        int from, to, weight;
        std::cin >> from >> to >> weight;
        --from, --to;
        graph[from][to] = graph[to][from] = weight;
        // graph[from][to]=weight;
    }
    return graph;
}

int assign(Matrix& table, Matrix& assigned, const Matrix& graph, int set, int end){
    if(assigned[set][end]!=-1){
        return table[set][end];
    }
    table[set][end] = INF;
    assigned[set][end] = end;
    int itr = (set<<1)+1;
    for(int i=0;itr>0;i++){
        if(itr%2==0){
            itr /= 2;
            continue;
        }
        if(i==end){
            itr /= 2;
            continue;
        }
        if(table[set][end] > assign(table, assigned, graph, set^(1<<(end-1)), i)+graph[i][end]){
            table[set][end] = assign(table, assigned, graph, set^(1<<(end-1)), i)+graph[i][end];
            assigned[set][end] = i;
        }
        itr /= 2;
    }
    return table[set][end];
}

std::pair<int, vector<int> > optimal_path(const Matrix& graph) {
    // This solution tries all the possible sequences of stops.
    // It is too slow to pass the problem.
    // Implement a more efficient algorithm here.
    Matrix table(1<<(graph.size()-1), vector<int>(graph.size()));
    Matrix assigned(table.size(), vector<int>(graph.size(), -1));
    table[0][0]=0;
    assigned[0][0]=0;
    for(int i=1;i<table.size();i++){
        table[i][0]=INF;
        assigned[i][0]=0;
    }
    int result = INF, track=-1;
    for(int i=1;i<graph.size();i++){
        if(result > assign(table, assigned, graph, table.size()-1, i)+graph[0][i]){
            result = assign(table, assigned, graph, table.size()-1, i)+graph[0][i];
            track = i;
        }
    }

    // std::cout<<"Table:\n";
    // for(vector<int> row: table){
    //     for(int el: row){
    //         el==INF ? std::cout<<"INF " : std::cout<<el<<" ";
    //     }std::cout<<std::endl;
    // }
    // std::cout<<"Assigned:\n";
    // for(vector<int> row: assigned){
    //     for(int el: row){
    //         std::cout<<el<<" ";
    //     }std::cout<<std::endl;
    // }
    // std::cout<<"Track->"<<track<<std::endl;

    if(result>=INF) return make_pair(-1, vector<int>());
    vector<int> dir={1};
    int set = table.size()-1;
    while(track != assigned[set][track] && assigned[set][track]!=-1){
        dir.push_back(track+1);
        track = assigned[set][track];
        set ^= (1<<(dir.back()-2));
    }
    return make_pair(result, dir);
}

void print_answer(const std::pair<int, vector<int> >& answer) {
    std::cout << answer.first << "\n";
    if (answer.first == -1)
        return;
    const vector<int>& path = answer.second;
    for (size_t i = 0; i < path.size(); ++i)
        std::cout << path[i] << " ";
    std::cout << "\n";
}

int main() {
    print_answer(optimal_path(read_data()));
    return 0;
}
