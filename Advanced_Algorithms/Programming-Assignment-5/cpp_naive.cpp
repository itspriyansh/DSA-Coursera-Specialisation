#include <iostream>
#include <math.h>
#include <algorithm>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <cstdlib>
#include <map>
using namespace std;

int64_t hash_func(int64_t a, int64_t b, int64_t m, int64_t x){
	int64_t p = 1610612741;
	x = (x%p)%m;
	a %= m;
	x = ((a*x)%p)%m;
	b %= m;
	return ((x+b)%p)%m;
}

int sign(int64_t a, int64_t b, int64_t x){
	int res = hash_func(a, b, 100, x);
	return (res<50 ? -1 : 1);
}

class CountSketch{
	public:
		int b, t;
		vector<int64_t> hashValues;
		vector<int64_t> results;
		vector<vector<int64_t>> data;
	
		CountSketch(int64_t n):b((int)log(n)*750+1),
		t((int)log(n)+1),
		hashValues(vector<int64_t>(t+1)),
		data(vector<vector<int64_t>>(b, vector<int64_t>(t))),
		results(vector<int64_t>(t)){
			srand(time(NULL));
			// cout<<"Enter "<<t<<" hash Values:\n";
			int64_t p = 1610612740;
			for(int i=0;i<=t;i++){
				hashValues[i] = rand()%p + 1;
				// cin>>hashValues[i];
			}
		}
		void update(int64_t index, int64_t frequency){
			for(int i=0;i<t;i++){
				data[hash_func(hashValues[i], hashValues[i+1], b, index)][i] += (sign(hashValues[i], hashValues[i+1], index) * frequency);
				// cout<<"Update: "<<hash_func(hashValues[i], hashValues[i+1], b, index)<<", "<<i<<" for "<<index<<" and "<<frequency<<" as "<<data[hash_func(hashValues[i], hashValues[i+1], b, index)][i]<<endl;
			}
		}
		int64_t estimate(int64_t index){
			for(int i=0;i<t;i++){
				results[i] = data[hash_func(hashValues[i], hashValues[i+1], b, index)][i]*sign(hashValues[i], hashValues[i+1], index);
			}
			nth_element(results.begin(), results.begin()+results.size()/2,results.end());
			return *next(results.begin(), results.size()/2);
		}
};
class Naive{
	public:
		map<int64_t, int64_t> begin, end;
		void update(int64_t id, int64_t value, int ind){
			if(ind==0){
				map<int64_t, int64_t>::iterator it = begin.find(id);
				if(it==begin.end()){
					begin.insert(make_pair(id, value));
				}
			}else{
				map<int64_t, int64_t>::iterator it = end.find(id);
				if(it==end.end()){
					end.insert(make_pair(id, value));
				}
			}
		}
		int64_t estimate(int64_t id){
			return begin[id]-end[id];
		}
};
void stress_test(){
	srand(time(NULL));
	while(true){
		int total = 50000, threshold=50, range=16;


		int n = rand()%(total-2) + 3, t = rand()%(threshold-2) + 3;
		bool flag=false;
		CountSketch count(n);
		Naive naive;
		int64_t id, value;
		for(int i=0;i<n;i++){
			id = rand()%(int64_t)(pow(2, range));
			value = rand()%(int64_t)(pow(2, range));
			if(naive.begin.find(id)==naive.begin.end()){
				count.update(id, value);
				naive.update(id, value, 0);
			}
		}
		for(map<int64_t, int64_t>::iterator it=naive.begin.begin();it!=naive.begin.end();it++){
			id = it->first;
			value = it->second - (rand()%(4*t));
			if(naive.end.find(id)==naive.end.end()){
				count.update(id, -1*value);
				naive.update(id, value, 1);
			}
		}
		for(map<int64_t, int64_t>::iterator it=naive.begin.begin();it!=naive.begin.end();it++){
			int64_t l1=count.estimate(it->first), l2=naive.estimate(it->first);
			int ans1, ans2;
			if(l1>=t) ans1=1;
			else ans1=0;
			if(l2>=t) ans2=1;
			else ans2=0;
			if(ans1==ans2){
				cout<<"Test Passed "<<it->first<<endl;
			}
			else{
				cout<<"Test Failed "<<it->first<<endl;
	
				cout<<"Take a look\n";
				cout<<it->first<<"->"<<it->second<<"->"<<naive.end[it->first]<<endl;
				cout<<t<<"=>"<<count.estimate(it->first)<<"->"<<naive.estimate(it->first)<<endl;
				flag = true;
				break;
			}
		}
		if(flag) break;
		else{ cout<<"Bring Another Test\n"; }
		// cin.ignore();
	}
}

int main() {
	// stress_test();
    int n, t;
    scanf("%d %d", &n, &t);

    // map<int, int> M;
    CountSketch count(n);
    int64_t id, value;

    for (int i = 0; i < n; ++i) {
        cin>>id>>value;

        count.update(id, value);
    }

    for (int i = 0; i < n; ++i) {
        cin>>id>>value;

        count.update(id, -1*value);
    }

    int num_queries = 0;
    scanf("%d", &num_queries);
    for (int q = 0; q < num_queries; ++q) {
        int64_t query = 0;
        cin>>query;

        int64_t ans = count.estimate(query);
        // cout<<"Answer->"<<ans<<endl;
        if (ans >= t)
        	cout<<"1 ";
        else
            cout << "0 ";
    }

    return 0;
}



