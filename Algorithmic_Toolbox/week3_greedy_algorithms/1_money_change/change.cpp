#include <iostream>
using namespace std;

int get_change(int m) {
  //write your code here
	int coins = 0;
	while(m>=10){
		coins++;
		m-=10;
	}while(m>=5){
		coins++;
		m-=5;
	}while(m>=1){
		coins++;
		m-=1;
	}
	return coins;
}

int main() {
  int m;
  std::cin >> m;
  std::cout << get_change(m) << '\n';
}
