#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    for (size_t i = 0; i < vec.size();) {
        if (vec[i] < 5) {
            vec.erase(vec.begin() + i);
        }
        else{
            i++;
        }
    }

    // Print the remaining elements
    for (int num : vec) {
        std::cout << num << " ";
    }

    return 0;
}
