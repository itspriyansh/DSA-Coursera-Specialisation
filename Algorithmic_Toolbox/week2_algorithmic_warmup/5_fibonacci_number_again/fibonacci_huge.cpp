#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

long long get_fibonacci_huge_naive(long long n, long long m) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
    }

    return current % m;
}

long pisano_period(long long n) {
    int a=0, b=1, c=0;
    for(long i=1;i<n*n;i++) {
        c=(a+b)%n;
        a=b;
        b=c;
        if(a==0 && b==1){
            return i;
        }
    }
}

long long get_fibonacci_huge_fast(long long n, long long m) {
    long target = n%pisano_period(m);
    long long first=0, second=1, current=0;
    if(target==1){
        current=1;
    }else{
        for(int i=2;i<=target;i++){
            current = (first+second)%m;
            first=second;
            second=current;
        }
    }
    return current;
}

int main() {
    long long n, m;
    std::cin >> n >> m;
    // std::cout << get_fibonacci_huge_naive(n, m) << '\n';
    std::cout << get_fibonacci_huge_fast(n, m) << '\n';
}
