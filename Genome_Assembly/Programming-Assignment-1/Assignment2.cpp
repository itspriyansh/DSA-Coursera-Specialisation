#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#include <random>
#include <algorithm>
#define TOLERENCE 2

using namespace std;

int largestBorder(string& a, string& b){
	int l = min(a.size(), b.size());
	for(int s=l;s>12;s--){
		int e=0;
		for(int i=0;i<s && e<=TOLERENCE;i++){
			if(a[a.size()-s+i]!=b[i]) e++;
		}
		if(e<=TOLERENCE) return s;
	}
	return 0;
}

char mix(vector<char> arr){
	map<char, int> m;
	for(char c: arr){
		m[c]++;
	}
	char ans = (*m.begin()).first;
	for(auto e: m){
		if(e.second > m[ans]){
			ans = e.first;
		}
	}
	return ans;
}

void hamiltonian(vector<string>& data, string& genome){
	vector<bool> visited(data.size(), false);
	genome = data.front();
	int cur = 0;
	for(int count=1, s=data.size();count<s;count++){
		visited[cur] = true;
		vector<pair<int, int> > overlaps;
		for(int i=1, l=data.size();i<l;i++){
			if(visited[i]) continue;
			int overlap = largestBorder(data[cur], data[i]);
			if(overlaps.empty() || overlap>=overlaps.back().first){
				overlaps.push_back(make_pair(overlap, i));
			}
		}
		if(overlaps.size()>3){
			char* a = &genome[genome.size()-overlaps[overlaps.size()-4].first];
			char* b = &data[overlaps[overlaps.size()-4].second][0];
			char* c = &data[overlaps[overlaps.size()-3].second][(overlaps[overlaps.size()-3].first-overlaps[overlaps.size()-4].first)];
			char* d = &data[overlaps[overlaps.size()-2].second][(overlaps[overlaps.size()-2].first-overlaps[overlaps.size()-4].first)];
			char* e = &data[overlaps[overlaps.size()-1].second][(overlaps[overlaps.size()-1].first-overlaps[overlaps.size()-4].first)];
			for(int i=0, l=overlaps[overlaps.size()-4].first;i<l;i++, a++, b++, c++, d++, e++){
				if(*a==*b && *b==*c && *c==*d && *d==*e) continue;
				const char ch = mix({*a, *b, *c, *d, *e});
				*a = *b = *c = *d = *e = ch;
			}
		}
		// cout<<"Overlaps\n";
		// for(auto e: overlaps){
		// 	cout<<e.first<<"->"<<e.second<<" ";
		// }cout<<endl;
		cur = overlaps.back().second;
		// cout<<"Adding->"<<genome<<" "<<data[cur]<<" "<<overlaps.back().first<<" "<<data[cur].substr(overlaps.back().first)<<endl;
		for(int i=overlaps.back().first;i<data[cur].size();i++){
			genome.push_back(data[cur][i]);
		}
	}
	genome.erase(0, largestBorder(data[cur], data[0]));
}

int main(){
	vector<string> dataset;
	string temp;
	for(int i=0;i<1618;i++){
		cin>>temp;
		dataset.push_back(temp);
	}
	random_device rd;
    mt19937 g(rd());
 	shuffle(dataset.begin(), dataset.end(), g);
	string genome;
	hamiltonian(dataset, genome);
	cout<<genome<<endl;
	return 0;
}