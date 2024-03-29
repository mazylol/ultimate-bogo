#include <algorithm>
#include <iostream>
#include <vector>

#include <Bogosort.h>

int main() {
    std::vector<int> vec = {3, 5, 1, 9, 6, 8, 9, 27, 28};

    vec = Bogosort::sort(vec, 8);

    for (auto &item : vec) {
        std::cout << item << " ";
    }
    std::cout << "\n";

    return 0;
}