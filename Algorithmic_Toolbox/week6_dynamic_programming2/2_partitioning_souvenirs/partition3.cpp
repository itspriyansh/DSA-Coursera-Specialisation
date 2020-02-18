#include <iostream>
#include <vector>

using namespace std;

int partition3(vector<int> &A) {
	int sum=0;
	for(size_t i=0;i<A.size();i++)
		sum+=A[i];
	if(sum%3==0){
		int n = A.size();
		int part[sum/3+1][sum/3+1][n+1];
		for(size_t i=0;i<=sum/3;i++){
			for(size_t j=0;j<=sum/3;j++)
				part[i][j][0] = 0;
		}
		for(size_t i=0;i<=n;i++){
			part[0][0][i] = 1;
		}
		for(size_t i=0;i<=sum/3;i++){
			for(size_t j=0;j<=sum/3;j++){
				if(i==0 && j==0)
					break;
				for(size_t k=1;k<=n;k++){
					part[i][j][k] = part[i][j][k-1];
					if(i>=A[k-1] && j>=A[k-1])
						part[i][j][k] = part[i][j][k] || part[i-A[k-1]][j-A[k-1]][k-1];
				}
			}
		}
		return part[sum/3][sum/3][n];
	}
  return 0;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> A(n);
  for (size_t i = 0; i < A.size(); ++i) {
    std::cin >> A[i];
  }
  std::cout << partition3(A) << '\n';
}
