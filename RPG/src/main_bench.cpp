#include <algorithm>
#include <boost/multiprecision/cpp_int.hpp>
#include <chrono>
#include <cstdio>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <random>
#include <thread>
#include <vector>
#include "src/lib/math/prime.hpp"
#include "src/lib/time/chrono/chrono.hpp"
#include "src/lib/vector/vector.hpp"

#if __cplusplus >= 201703L
#    include "src/lib/thread/Pool.hpp"
#else
#    include "src/lib/thread/ThreadPool.h"
#endif
#include <algorithm>
#include <chrono>
#include <cmath>
#include <future>

struct Processor
{
    // long double operator()(bool(*elem_fn)(const long long int &), long long int prime_nbr)
    long double operator()(std::function<bool(const long long int &)> elem_fn, long long int prime_nbr)
    {
        auto &&t1 = chrono::now();
        if ((elem_fn)(prime_nbr) != true) {
            std::cout << "ERROR, is prime NBR: " << prime_nbr << std::endl;
        }
        auto &&t2 = chrono::now();
        return chrono::duration(t1, t2).count();
        // std::this_thread::sleep_for(std::chrono::seconds(1));
    }
};

struct Processor1
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
    // std::vector<std::vector<std::future<std::pair<std::string, long double>>>> results {};
    std::vector<std::pair<std::string, std::vector<std::future<long double>>>> results {};

#if __cplusplus >= 201703L
    thread::Pool thread_pool(std::thread::hardware_concurrency() / 2);
#else
    ThreadPool thread_pool(std::thread::hardware_concurrency() / 2);
#endif
    const std::vector<long long int> prime_nbrs
        = {7, 29, 151, 4219, 40829, 251857, 4000037, 40000003, 400000009, 400000009, 4000000007, 40000000003, 400000000019, 999999999989, 4312512644831,
            67280421310721, 369822932657561, 1323784290040759, 67428322156073819, 979025471535264563, 3815136756226794067};
    const std::vector<std::pair<const std::string, bool (*)(const long long int &)>> pointer_map {{"isPrime_opti_1", &math::prime::isPrime_opti_1},
        {"isPrime_opti_2", &math::prime::isPrime_opti_2}, {"isPrime_opti_3", &math::prime::isPrime_opti_3}, {"isPrime_opti_4", &math::prime::isPrime_opti_4},
        {"isPrime_opti_5", &math::prime::isPrime_opti_5}, //{"isPrime_opti_5T", &math::prime::isPrime_opti_5<long long int>},
        {"isPrime_opti_6", &math::prime::isPrime_opti_6}, {"isPrime_opti_8(3&5)", &math::prime::isPrime_opti_8}};
   

    //const std::vector<long long int> prime_nbrs = {116677907, 138689389, 254980819, 260517689, 309428993, 383281957, 396682753, 403562587, 468763033, 487323973, 576933671, 615231907, 618071749, 656203337, 721276979, 714607867, 721753423, 806622203, 959244661, 965160901};

    // Generate poolthreading
    results.reserve(pointer_map.size());
    for (auto &elem_fn : pointer_map) {
        results.emplace_back(std::pair<std::string, std::vector<std::future<long double>>>());
        results.back().first = elem_fn.first;
        results.back().second.reserve(prime_nbrs.size());
        for (auto &prime_nbr : prime_nbrs) {
            results.back().second.emplace_back(thread_pool.enqueue(Processor(), elem_fn.second, prime_nbr));
        }
    }

    // Get result
    std::vector<std::pair<std::string, std::vector<long double>>> time {};
    time.reserve(results.size());
    for (auto &y : results) {
        time.emplace_back(std::pair<std::string, std::vector<long double>>());
        time.back().second.reserve(y.second.size());
        time.back().first = y.first;
        for (auto &x : y.second) {
            time.back().second.emplace_back(x.get());
        }
    }

    std::ifstream in("in.txt");
    std::cin.tie(0);
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); // save and redirect

    std::ofstream out("log.csv");
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
    /*
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
             results2.back().second.emplace_back(thread_pool2.enqueue(Processor1(), elem_fn.second, prime_nbr));
         }
     }
     std::cout << "Pool threading: OK" << std::endl;
     //std::this_thread::sleep_for(std::chrono::milliseconds(20000));
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

     std::ofstream out("log.csv");
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
    */
}
/*
int main()
{

    ThreadPool pool(4);
    std::vector< std::future<int> > results;

    for(int i = 0; i < 8; ++i) {
        results.emplace_back(
            pool.enqueue([i] {
                std::cout << "hello " << i << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                std::cout << "world " << i << std::endl;
                return i*i;
            })
        );
    }

    for(auto && result: results)
        std::cout << result.get() << ' ';
    std::cout << std::endl;

    return 0;
}
*/
