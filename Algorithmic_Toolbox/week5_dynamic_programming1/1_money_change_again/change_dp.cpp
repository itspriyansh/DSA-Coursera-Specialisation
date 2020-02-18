#include <iostream>
#include <algorithm>
using namespace std;

long long get_change(int m) {
  	//write your code here
  	int coins[] = {1, 3, 4};
	long long M[m+1];
	M[0] = 0;
	for(int i=1;i<=m;i++){
		M[i] = INT64_MAX;
		for(int j=0;j<3;j++){
			if(i>=coins[j])
				M[i] = min(M[i], M[i-coins[j]]+1);
		}
	}
  	return M[m];
}

int main() {
  int m;
  std::cin >> m;
  std::cout << get_change(m) << '\n';
}
