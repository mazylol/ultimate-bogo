#include <algorithm>
#include <chrono>
#include <future>
#include <memory>
#include <random>
#include <thread>
#include <vector>

class Bogo {
    template <typename T>
    static std::vector<T> sorting_fn(std::vector<T> vec) {
        while (!std::is_sorted(vec.begin(), vec.end())) {
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::shuffle(vec.begin(), vec.end(), std::default_random_engine(seed));
        }

        return vec;
    }

  public:
    // lame version
    template <typename T>
    static std::vector<T> sort(std::vector<T> vec) {
        return sorting_fn(vec);
    }

    // multithreaded version
    /*template <typename T>
    static std::vector<T> sort(std::vector<T> vec, int threads) {
        if (threads <= 1) {
            return sorting_fn(vec);
        }

        std::vector<std::future<std::vector<T>>> futures;
        std::vector<std::vector<T>> sub_vecs;

        for (int i = 0; i < threads; i++) {
            sub_vecs.push_back(std::vector<T>());
        }

        for (int i = 0; i < vec.size(); i++) {
            sub_vecs[i % threads].push_back(vec[i]);
        }

        for (int i = 0; i < threads; i++) {
            futures.push_back(std::async(std::launch::async, sorting_fn<T>, sub_vecs[i]));
        }

        for (int i = 0; i < threads; i++) {
            futures[i].wait();
        }

        for (int i = 0; i < threads; i++) {
            sub_vecs[i] = futures[i].get();
        }

        vec.clear();

        for (int i = 0; i < threads; i++) {
            vec.insert(vec.end(), sub_vecs[i].begin(), sub_vecs[i].end());
        }

        return vec;
    }
    */

    // better multithreaded version
    template <typename T>
    static std::vector<T> sort(std::vector<T> vec, int threads) {
        if (threads <= 1) {
            return sorting_fn(vec);
        }

        std::vector<std::future<std::vector<T>>> futures;

        for (int i = 0; i < threads; i++) {
            futures.push_back(std::async(std::launch::async, sorting_fn<T>, vec));
        }

        for (int i = 0; i < threads; i++) {
            futures[i].wait();
        }

        for (int i = 0; i < threads; i++) {
            if (futures[i].wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
                vec = futures[i].get();
                break;
            }
        }

        return vec;
    }
};