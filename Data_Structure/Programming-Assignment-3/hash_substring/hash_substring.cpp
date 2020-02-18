#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;
typedef unsigned long long ull;

struct Data {
    string pattern, text;
};

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

void print_occurrences(const std::vector<int>& output) {
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}

bool areEqual(string a, string b){
    if(a.size()!=b.size())
        return false;
    for(size_t i=0;i<a.size();i++){
        if(a[i]!=b[i])
            return false;
    }
    return true;
}

long long polyHash(const string& P, size_t p, size_t x){
    long long hash = 0;
    for (int i = static_cast<int> (P.size()) - 1; i >= 0; --i)
        hash = (hash * x + P[i]) % p;
    return hash;
}

void precomputeHashes(string T, int P, size_t p, size_t x, vector<long long> &H){
    string S = T.substr(T.size()-P);
    H[T.size()-P] = polyHash(S, p, x);
    long long y = 1;
    for(int i=0;i<P;i++)
        y = (y*x)%p;
    for(int i=T.size()-P-1;i>=0;i--)
        H[i] = (x * (H[i+1]) + T[i] - y*(T[i+P])) % p;
}

vector<int> rabin_karp(const Data& input){
    const string& p = input.pattern, t = input.text;
    int prime = 1000000007;
    int multiplier = rand() % (prime-1) + 1;
    vector<int> result;
    long long pHash = polyHash(p,prime,multiplier);
    vector<long long> H;
    H.resize(t.size()-p.size()+1);
    precomputeHashes(t, p.size(), prime, multiplier, H);
    // cout<<pHash<<endl;
    for(int i=0;i<H.size();i++){
        // cout<<H[i]<<" ";
        if(pHash!=H[i])
            continue;
        string T = t.substr(i, p.size());
        if(areEqual(T, p))
            result.push_back(i);
    }
    // cout<<endl;
    return result;
}

std::vector<int> get_occurrences(const Data& input) {
    const string& s = input.pattern, t = input.text;
    std::vector<int> ans;
    for (size_t i = 0; i + s.size() <= t.size(); ++i)
        if (t.substr(i, s.size()) == s)
            ans.push_back(i);
    return ans;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    print_occurrences(rabin_karp(read_input()));
    return 0;
}
