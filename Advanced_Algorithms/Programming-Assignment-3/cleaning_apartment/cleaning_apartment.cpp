#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int from;
    int to;
};

struct ConvertHampathToSat {
    int numVertices;
    vector<vector<int>> edges;

    ConvertHampathToSat(int n, int m) :
        numVertices(n),
        edges(n)
    {  }

    void printEquisatisfiableSatFormula() {
        // This solution prints a simple satisfiable formula
        // and passes about half of the tests.
        // Change this function to solve the problem.
        vector<vector<int>> sat;
        for(int i=0;i<numVertices;i++){
            vector<int> col1, col2;
            for(int j=0;j<numVertices;j++){
                col1.push_back(i*numVertices+j+1);
                col2.push_back(j*numVertices+i+1);
            }
            if(col1.empty()) continue;
            col1.push_back(0);
            col2.push_back(0);
            sat.push_back(col1);
            sat.push_back(col2);

            for(int j=0;j<col1.size()-2;j++){
                for(int k=j+1;k<col1.size()-1;k++){
                    sat.push_back({-1*col1[j], -1*col1[k], 0});
                    sat.push_back({-1*col2[j], -1*col2[k], 0});
                }
            }
        }

        for(int i=0;i<edges.size();i++){
            for(int j=0;j<numVertices;j++){
                if((i*numVertices+j+1)%numVertices==0) continue;
                vector<int> col;
                col.push_back(-1*i*numVertices-j-1);
                for(int k=0;k<edges[i].size();k++){
                    col.push_back(edges[i][k]*numVertices+j+2);
                }
                sat.push_back(col);
                sat.back().push_back(0);
            }
        }

        cout<<sat.size()<<" "<<numVertices*numVertices<<endl;
        for(int i=0;i<sat.size();i++){
            for(int j=0;j<sat[i].size();j++){
                cout<<sat[i][j];
                if(j+1<sat[i].size()) cout<<" ";
            }cout<<endl;
        }
    }
};

int main() {
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    ConvertHampathToSat converter(n, m);
    for (int i = 0; i < m; ++i) {
        // cin >> converter.edges[i].from >> converter.edges[i].to;
        Edge edge;
        cin >> edge.from >> edge.to;
        converter.edges[edge.from-1].push_back(edge.to-1);
        converter.edges[edge.to-1].push_back(edge.from-1);
    }

    converter.printEquisatisfiableSatFormula();

    return 0;
}
