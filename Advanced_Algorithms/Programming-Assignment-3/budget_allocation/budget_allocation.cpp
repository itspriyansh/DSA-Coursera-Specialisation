#include <ios>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct ConvertILPToSat {
    vector< vector<int> > A;
    vector<int> b;
    int m,n;

    ConvertILPToSat(int n, int m) : A(n, vector<int>(m)), b(n), m(m), n(n)
    {}

    void printEquisatisfiableSatFormula() {
        // This solution prints a simple satisfiable formula
        // and passes about half of the tests.
        // Change this function to solve the problem.
        vector<vector<int>> sat;

        for(int i=0;i<n;i++){
            vector<int> nonzero;
            for(int j=0;j<m;j++){
                if(A[i][j]!=0){
                    nonzero.push_back(j);
                }
            }
            if(nonzero.empty()){
                if(b[i]<0){
                    sat.push_back({1});
                    sat.push_back({-1});
                    break;
                }
            }else{
                int size = pow(2, nonzero.size());
                for(int j=0;j<size;j++){
                    int subset = j;
                    int64_t sum = 0;
                    for(int k=0;k<nonzero.size();k++){
                        sum += A[i][nonzero[k]] * (subset%2);
                        subset /= 2;
                    }
                    if(sum > b[i]){
                        vector<int> col;
                        subset = j;
                        for(int k=0;k<nonzero.size();k++){
                            if(subset%2==0){
                                col.push_back(nonzero[k]+1);
                            }else{
                                col.push_back(-1*nonzero[k]-1);
                            }
                            subset /= 2;
                        }
                        sat.push_back(col);
                    }
                }
            }
        }

        if(sat.empty() && m>0){
            sat.push_back({1,-1});
        }

        cout<<sat.size()<<" "<<m<<endl;
        for(int i=0;i<sat.size();i++){
            for(int j=0;j<sat[i].size();j++){
                cout<<sat[i][j]<<" ";
            }
            cout<<0<<endl;
        }
    }
};

int main() {
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    ConvertILPToSat converter(n, m);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        cin >> converter.A[i][j];
      }
    }
    for (int i = 0; i < n; i++) {
      cin >> converter.b[i];
    }

    converter.printEquisatisfiableSatFormula();

    return 0;
}
