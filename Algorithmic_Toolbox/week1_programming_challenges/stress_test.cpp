#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

int64_t MaxPairwiseProductNaive(const std::vector<int>& numbers) {
    int64_t max_product = 0;
    int n = numbers.size();

    for (int first = 0; first < n; ++first) {
        for (int second = first + 1; second < n; ++second) {
            max_product = std::max(max_product, (int64_t)numbers[first] * (int64_t)numbers[second]);
        }
    }

    return max_product;    
}
int64_t MaxPairwiseProductFast(const std::vector<int>& numbers) {
    int n = numbers.size();
    int index1 = 0;
    for(int i=1; i<n; i++) {
    	if(numbers[i]>numbers[index1]) 
    		index1 = i;
    }
    int index2 = 1;
    if(index1 != 0)
    	index2 = 0;
    for(int j=index2+1; j<n; j++) {
    	if((index1!=j) && (numbers[j]>numbers[index2]))
    		index2=j;
    }
    int64_t result = (int64_t)numbers[index1]*(int64_t)numbers[index2];
    return result;
}
int64_t MaxPairwiseProductTest(const std::vector<int>& numbers) {
    int n = numbers.size();
    int first = numbers[0], second = numbers[1];
    if(first<second)
        std::swap(first, second);
    for(int i=2; i<n; i++) {
        if(numbers[i]>first) {
            second = first;
            first = numbers[i];
        } else if(numbers[i]>second) {
            second = numbers[i];
        }
    }
    return (int64_t)first*(int64_t)second;
}

int main() {
    int n_max, max;
    std::cin >> n_max >> max;
    while(true) {
        int n = (rand()%(n_max-1))+2;
        std::vector<int> numbers(n);
        for (int i = 0; i < n; ++i) {
            numbers[i]=(rand()%max)+1;
            std::cout<<numbers[i]<<' ';
        }
        std::cout<<std::endl;
        int64_t result1=MaxPairwiseProductFast(numbers);
        int64_t result2=MaxPairwiseProductTest(numbers);
        if(result1==result2)
            std::cout<<"OK\n";
        else {
            std::cout<<"Wrong Answer: "<<result1<<' '<<result2<<'\n';
            break;
        }
    }
    // int64_t result = MaxPairwiseProduct(numbers);
    // std::cout << result << "\n";
    return 0;
}