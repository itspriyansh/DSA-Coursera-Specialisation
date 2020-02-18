#include <iostream>
#include <vector>
#include <sys/resource.h>
// #include <algorithm>

using namespace std;

struct Vertex {
    int weight;
    std::vector <int> children;
};
typedef std::vector<Vertex> Graph;
typedef std::vector<int> Sum;

Graph ReadTree() {
    int vertices_count;
    std::cin >> vertices_count;

    Graph tree(vertices_count);

    for (int i = 0; i < vertices_count; ++i)
        std::cin >> tree[i].weight;

    for (int i = 1; i < vertices_count; ++i) {
        int from, to, weight;
        std::cin >> from >> to;
        tree[from - 1].children.push_back(to - 1);
        tree[to - 1].children.push_back(from - 1);
    }

    return tree;
}

int64_t dfs(vector<int>& table, const Graph &tree, int vertex, int parent) {
    // This is a template function for processing a tree using depth-first search.
    // Write your code here.
    // You may need to add more parameters to this function for child processing.
    if(table[vertex]!=-1){
        return table[vertex];
    }
    if(tree[vertex].children.empty()){
        table[vertex] = tree[vertex].weight;
        return tree[vertex].weight;
    }
    int result = tree[vertex].weight, alternate=0;
    for(int child: tree[vertex].children){
        if(child==parent) continue;
        alternate += dfs(table, tree, child, vertex);
        for(int grandchild: tree[child].children){
            if(grandchild==vertex) continue;
            result += dfs(table, tree, grandchild, child);
        }
    }
    table[vertex] = (result>=alternate ? result : alternate);
    return table[vertex];
}

int64_t MaxWeightIndependentTreeSubset(const Graph &tree) {
    size_t size = tree.size();
    if (size == 0)
        return 0;
    vector<int> table(tree.size(), -1);
    return dfs(table, tree, 0, -1);
    // You must decide what to return.
}

int main() {
    // This code is here to increase the stack size to avoid stack overflow
    // in depth-first search.
    const rlim_t kStackSize = 64L * 1024L * 1024L;  // min stack size = 64 Mb
    struct rlimit rl;
    int result;
    result = getrlimit(RLIMIT_STACK, &rl);
    if (result == 0)
    {
        if (rl.rlim_cur < kStackSize)
        {
            rl.rlim_cur = kStackSize;
            result = setrlimit(RLIMIT_STACK, &rl);
            if (result != 0)
            {
                fprintf(stderr, "setrlimit returned result = %d\n", result);
            }
        }
    }

    // Here begins the solution
    Graph tree = ReadTree();
    int weight = MaxWeightIndependentTreeSubset(tree);
    std::cout << weight << std::endl;
    return 0;
}
