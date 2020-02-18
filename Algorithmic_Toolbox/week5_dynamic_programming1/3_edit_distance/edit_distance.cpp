#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int edit_distance(const string str1, const string str2) {
  	//write your code here
	int l1 = str1.size(), l2 = str2.size();
	int D[l1+1][l2+1];
	for(int i=0;i<=l1;i++)
		D[i][0] = i;
	for(int j=0;j<=l2;j++)
		D[0][j] = j;
	for(int j=1;j<=l2;j++){
		for(int i=1;i<=l1;i++){
			int insertion = D[i][j-1]+1;
			int deletion = D[i-1][j]+1;
			int match = D[i-1][j-1];
			if(str1[i-1] != str2[j-1])
				match++;
			D[i][j] = min(min(insertion, deletion), match);
		}
	}
  	return D[l1][l2];
}

int main() {
  string str1;
  string str2;
  std::cin >> str1 >> str2;
  std::cout << edit_distance(str1, str2) << std::endl;
  return 0;
}
