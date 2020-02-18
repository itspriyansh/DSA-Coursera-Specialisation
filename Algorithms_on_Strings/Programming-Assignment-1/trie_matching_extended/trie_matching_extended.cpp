#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int const Letters =    4;
int const NA      =   -1;

struct Node
{
	int next [Letters];
	bool patternEnd;

	Node ()
	{
		fill (next, next + Letters, NA);
		patternEnd = false;
	}
};

int letterToIndex (char letter)
{
	switch (letter)
	{
		case 'A': return 0; break;
		case 'C': return 1; break;
		case 'G': return 2; break;
		case 'T': return 3; break;
		default: assert (false); return -1;
	}
}

vector <int> solve (string text, int n, vector <string> patterns)
{
	vector <int> result;
	// write your code here
	vector<Node> list(1);
	for(int i=0;i<patterns.size();i++){
		int current = 0;
		for(int j=0;j<patterns[i].size();j++){
			// checking(patterns[i][j], 53);
			if(list[current].next[letterToIndex(patterns[i][j])]!=NA){
				current = list[current].next[letterToIndex(patterns[i][j])];
			}else{
				list[current].next[letterToIndex(patterns[i][j])] = list.size();
				current = list.size();
				Node temp;
				list.push_back(temp);
			}
			if(j+1==patterns[i].size()) list[current].patternEnd = true;
		}
	}
	for(int i=0;i<text.size();i++){
		// checking(text[i], 65);
		int c = letterToIndex(text[i]);
		int current = 0, temp=i;
		while(true){
			if(list[current].patternEnd){
				result.push_back(i);
				break;
			}
			else{
				if(c!=NA && list[current].next[c]!=NA){
					current = list[current].next[c];
					c = (++temp < text.size())?letterToIndex(text[temp]):NA;
				}else break;
			}
		}
	}
	return result;
}

int main (void)
{
	string t;
	cin >> t;

	int n;
	cin >> n;

	vector <string> patterns (n);
	for (int i = 0; i < n; i++)
	{
		cin >> patterns[i];
	}

	vector <int> ans;
	ans = solve (t, n, patterns);

	for (int i = 0; i < (int) ans.size (); i++)
	{
		cout << ans[i];
		if (i + 1 < (int) ans.size ())
		{
			cout << " ";
		}
		else
		{
			cout << endl;
		}
	}

	return 0;
}
