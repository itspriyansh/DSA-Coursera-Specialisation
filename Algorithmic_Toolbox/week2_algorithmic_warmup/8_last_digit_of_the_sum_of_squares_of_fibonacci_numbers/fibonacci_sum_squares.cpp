#include <iostream>
#include <vector>
using namespace std;

int fibonacci_sum_squares_naive(long long n) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;
    long long sum      = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
        sum += current * current;
    }

    return sum % 10;
}

int fibonacci_sum_squares_fast(long long n) {
    n%=60;
    vector<int> F(n+2);
    F[0]=0;
    F[1]=1;
    for(int i=2;i<=n+1;i++) {
        F[i]=(F[i-1]+F[i-2])%10;
    }
    return (F[n]*F[n+1])%10;
}

int main() {
    long long n = 0;
    std::cin >> n;
    // std::cout << fibonacci_sum_squares_naive(n);
    std::cout << fibonacci_sum_squares_fast(n);
}
