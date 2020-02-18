#include <ios>
#include <iostream>
#include <vector>

using namespace std;

struct Edge {
    int from;
    int to;
};

struct ConvertGSMNetworkProblemToSat {
    int numVertices;
    vector<Edge> edges;

    ConvertGSMNetworkProblemToSat(int n, int m) :
        numVertices(n),
        edges(m)
    {  }

    void printEquisatisfiableSatFormula() {
        // This solution prints a simple satisfiable formula
        // and passes about half of the tests.
        // Change this function to solve the problem.
        cout<<numVertices*4+edges.size()*3<<" "<<numVertices*3<<endl;
        for(int i=0;i<numVertices;i++){
            cout<<i*3+1<<" "<<i*3+2<<" "<<i*3+3<<" "<<0<<endl;
            cout<<i*-3-1<<" "<<i*-3-2<<" "<<0<<endl;
            cout<<i*-3-2<<" "<<i*-3-3<<" "<<0<<endl;
            cout<<i*-3-3<<" "<<i*-3-1<<" "<<0<<endl;
        }
        for(int i=0;i<edges.size();i++){
            cout<<2+edges[i].from*-3<<" "<<2+edges[i].to*-3<<" "<<0<<endl;
            cout<<1+edges[i].from*-3<<" "<<1+edges[i].to*-3<<" "<<0<<endl;
            cout<<edges[i].from*-3<<" "<<edges[i].to*-3<<" "<<0<<endl;
        }
    }
};

int main() {
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    ConvertGSMNetworkProblemToSat converter(n, m);
    for (int i = 0; i < m; ++i) {
        Edge edge;
        cin >> converter.edges[i].from >> converter.edges[i].to;
    }

    converter.printEquisatisfiableSatFormula();

    return 0;
}
