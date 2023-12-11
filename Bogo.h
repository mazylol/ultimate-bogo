#include <algorithm>
#include <random>
#include <chrono>

class Bogo {
  public:
    template <typename T>
    static void sort(T *vec) {
        while (!std::is_sorted(vec->begin(), vec->end())) {
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::shuffle(vec->begin(), vec->end(), std::default_random_engine(seed));
        }
    }
};