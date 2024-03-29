#ifndef Bogosort_H
#define Bogosort_H

#include <algorithm>
#include <chrono>
#include <future>
#include <iostream>
#include <random>
#include <vector>

/// @brief The best sorting algoritm
class Bogosort {
    template <typename T>
    static std::vector<T> sorting_fn(std::vector<T> vec, std::atomic<bool> &success) {
        while (!success.load() && !std::is_sorted(vec.begin(), vec.end())) {
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::shuffle(vec.begin(), vec.end(), std::default_random_engine(seed));
        }

        success.store(true);
        return vec;
    }

  public:
    /// @brief The thing that does the magic
    /// @tparam T 
    /// @param vector Input Vector 
    /// @param threads Number of threads to use
    /// @return The vector you supplied, sorted
    template <typename T>
    static std::vector<T> sort(std::vector<T> vector, int threads) {
        if (threads <= 1) {
            std::atomic<bool> success(false);
            return sorting_fn(vector, success);
        }

        std::atomic<bool> success(false);
        std::vector<std::future<std::vector<T>>> futures;

        for (int i = 0; i < threads; i++) {
            futures.push_back(std::async(
                std::launch::async, [](std::vector<T> v, std::atomic<bool> &s) {
                    return sorting_fn(v, s);
                },
                vector, std::ref(success)));
        }

        for (auto &future : futures) {
            std::vector<T> sorted = future.get();
            if (success.load() && std::is_sorted(sorted.begin(), sorted.end())) {
                return sorted;
            }
        }

        return vector;
    }
};

#endif