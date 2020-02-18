#include <iostream>
#include <vector>
using namespace std;

long long get_fibonacci_partial_sum_naive(long long from, long long to) {
    long long sum = 0;

    long long current = 0;
    long long next  = 1;

    for (long long i = 0; i <= to; ++i) {
        if (i >= from) {
            sum += current;
        }

        long long new_current = next;
        next = next + current;
        current = new_current;
    }

    return sum % 10;
}

int get_fibonacci_partial_sum_fast(long long from, long long to) {
    from%=60;
    to%=60;
    vector<int> F(to+3);
    F[0]=0;
    F[1]=1;
    for(int i=2;i<=to+2;i++) {
        F[i]=(F[i-1]+F[i-2])%10;
    }
    return (10+F[to+2]-F[from+1])%10;
}

int main() {
    long long from, to;
    std::cin >> from >> to;
    // std::cout << get_fibonacci_partial_sum_naive(from, to) << '\n';
    std::cout << get_fibonacci_partial_sum_fast(from, to) << '\n';
}
