#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Query {
    string type, s;
    size_t ind;
};
struct Word{
    string s;
    Word *next;
};

class QueryProcessor {
    int bucket_count;
    // store all strings in one vector
    vector<Word*> elems;
    size_t hash_func(const string& s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;
    }

public:
    explicit QueryProcessor(int bucket_count): bucket_count(bucket_count) {
        elems.resize(bucket_count);
    }

    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

    void writeSearchResult(bool was_found) const {
        std::cout << (was_found ? "yes\n" : "no\n");
    }

    bool search(string s){
        size_t pos = hash_func(s);
        Word *p = elems[pos];
        while(p!=NULL){
            if(p->s == s)
                break;
            p = p->next;
        }
        return (p!=NULL);
    }

    void processQuery(const Query& query) {
        if (query.type == "check") {
            // use reverse order, because we append strings to the end
            Word *p = elems[query.ind];
            while(p!=NULL){
                cout<<p->s<<" ";
                p = p->next;
            }
            std::cout << "\n";
        } else {
            // vector<string>::iterator it = std::find(elems.begin(), elems.end(), query.s);
            if (query.type == "find"){
                writeSearchResult(search(query.s));
            }
            else if (query.type == "add") {
                if(!search(query.s)){
                    size_t pos = hash_func(query.s);
                    Word *p = new Word;
                    p->s = query.s;
                    p->next = elems[pos];
                    elems[pos] = p;
                }
            } else if (query.type == "del") {
                size_t pos = hash_func(query.s);
                if(elems[pos]!=NULL){
                    Word *p = elems[pos], *q = NULL;
                    while(p!=NULL){
                        if(p->s == query.s){
                            if(q==NULL)
                                elems[pos] = p->next;
                            else{
                                q->next = p->next;
                            }
                            free(p);
                            break;
                        }
                        q = p;
                        p = p->next;
                    }
                }
            }
        }
    }

    void processQueries() {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            processQuery(readQuery());
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}
