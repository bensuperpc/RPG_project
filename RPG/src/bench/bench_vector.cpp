#include <cstdio>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <random>
#include <thread>
#include <vector>
#include "../src/lib/math/prime.hpp"
#include "../src/lib/time/chrono/chrono.hpp"
#include "../src/lib/vector/vector.hpp"

#if __cplusplus >= 201703L
#    include "../src/lib/thread/Pool.hpp"
#else
#    include "../src/lib/thread/ThreadPool.h"
#endif
#include <algorithm>
#include <chrono>
#include <cmath>
#include <future>

struct Processor
{
    long double operator()(std::function<void(std::vector<std::vector<int>> &, std::vector<std::vector<int>> &)> elem_fn, size_t size)
    {
        auto &&Mat1 = vector::generate_matrix(size, size, 0);
        auto &&Mat2 = vector::generate_matrix(size, size, 0);
        auto &&t1 = chrono::now();
        (elem_fn)(Mat1, Mat2);
        auto &&t2 = chrono::now();
        Mat1.clear();
        Mat1.shrink_to_fit();
        Mat2.clear();
        Mat2.shrink_to_fit();
        return chrono::duration(t1, t2).count();
    }
};

// https://bigprimes.org/
// https://stackoverflow.com/questions/41749792/can-i-have-a-stdvector-of-template-function-pointers

int main()
{
    std::vector<std::pair<std::string, std::vector<std::future<long double>>>> results2 {};
#if __cplusplus >= 201703L
    thread::Pool thread_pool2(1);
#else
    ThreadPool thread_pool2(1);
#endif

    std::vector<int> nbrs_nbrs(4000);
    std::iota(nbrs_nbrs.begin(), nbrs_nbrs.end(), 1);

    const std::vector<std::pair<const std::string, void (*)(std::vector<std::vector<int>> &, std::vector<std::vector<int>> &)>> pointer_fn_map {
        {"cache_friendly_copy", &vector::cache_friendly_copy}, {"cache_unfriendly_copy", &vector::cache_unfriendly_copy}};

    results2.reserve(pointer_fn_map.size());

    for (auto &elem_fn : pointer_fn_map) {
        results2.emplace_back(std::pair<std::string, std::vector<std::future<long double>>>());
        results2.back().first = elem_fn.first;
        results2.back().second.reserve(nbrs_nbrs.size());
        for (auto &prime_nbr : nbrs_nbrs) {
            results2.back().second.emplace_back(thread_pool2.enqueue(Processor(), elem_fn.second, prime_nbr));
        }
    }
    std::cout << "Pool threading: OK" << std::endl;
    // std::this_thread::sleep_for(std::chrono::milliseconds(20000));
    // Get result
    std::vector<std::pair<std::string, std::vector<long double>>> time {};
    time.reserve(results2.size());
    for (auto &y : results2) {
        time.emplace_back(std::pair<std::string, std::vector<long double>>());
        time.back().second.reserve(y.second.size());
        time.back().first = y.first;
        for (auto &x : y.second) {
            time.back().second.emplace_back(x.get());
        }
    }
    std::cout << "Get data: OK" << std::endl;

    std::ifstream in("in.txt");
    std::cin.tie(0);
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); // save and redirect

    std::ofstream out("log_bench_vector.csv");
    std::ios_base::sync_with_stdio(false);

    auto coutbuf = std::cout.rdbuf(out.rdbuf()); // save and redirect

    // Header
    std::cout << "number,";
    for (size_t x = 0; x < time.size(); x++) {
        std::cout << time[x].first;
        if (x < time.size() - 1) {
            std::cout << ",";
        }
    }
    std::cout << std::setprecision(10) << std::fixed;
    std::cout << std::endl;

    for (size_t x = 0; x < time.back().second.size(); x++) {
        std::cout << x << ",";
        for (size_t y = 0; y < time.size(); y++) {
            std::cout << time[y].second[x];
            if (y < time.size() - 1) {
                std::cout << ",";
            }
        }
        std::cout << std::endl;
    }

    std::cin.rdbuf(cinbuf);
    std::cout.rdbuf(coutbuf);
}