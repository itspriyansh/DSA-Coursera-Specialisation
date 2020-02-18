#include <iostream>
#include <vector>
#include <algorithm>

int64_t MaxPairwiseProductNaive(const std::vector<int>& numbers) {
    int64_t max_product = 0;
    int n = numbers.size();

    for (int first = 0; first < n; ++first) {
        for (int second = first + 1; second < n; ++second) {
            max_product = std::max(max_product, ((int64_t)numbers[first]) * numbers[second]);
        }
    }

    return max_product;    
}
int64_t MaxPairwiseProductFast(const std::vector<int>& numbers) {
    int n = numbers.size();
    int index1 = -1;
    for(int i=0; i<n; i++) {
    	if((index1==-1) || (numbers[i]>numbers[index1])) 
    		index1 = i;
    }
    int index2 = -1;
    for(int j=0; j<n; j++) {
    	if((index1!=j) && ((index2==-1) || (numbers[j]>numbers[index2])))
    		index2=j;
    }
    int64_t result = ((int64_t)numbers[index1])*numbers[index2];
    return result;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> numbers(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> numbers[i];
    }

    int64_t result = MaxPairwiseProductFast(numbers);
    std::cout << result << "\n";
    return 0;
}