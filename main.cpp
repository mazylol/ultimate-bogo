#include <algorithm>
#include <iostream>
#include <vector>

#include "Bogo.h"

int main() {
    std::vector<int> vec = {3, 5, 1, 9, 6, 8, 7, 30, 2, 4, 10, 11, 12, 13, 14, 15, 16, 17, 18};

    vec = Bogo::sort(vec, 2);

    for (auto &item : vec) {
        std::cout << item << " ";
    }
    std::cout << "\n";

    return 0;
}