#define CATCH_CONFIG_RUNNER

#include "catch.hpp"

#include "lcs.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <random>

using namespace std::chrono;
using namespace std;

int main(int argc, char* argv[]) {
    int result = Catch::Session().run(argc, argv);

    default_random_engine generator;

    double time1 = 0.0;
    double time2 = 0.0;
    double time_stop = 0.6;
    int size_multiplicator = 2;
    int n = 5;
    while (time1 < time_stop && time2 < time_stop) {
        string fixedString(n, 'A');
        uniform_int_distribution<int> distribution(65, 90);
        string randomString(n, 'A');

        for (int i = 0; i < n; ++i) {
            randomString[i] = static_cast<char>(distribution(generator));
        }

        auto t1 = steady_clock::now();
        string temp = lcs(fixedString, randomString);
        auto t2 = steady_clock::now();

        time1 = duration<double>(t2 - t1).count();

        t1 = steady_clock::now();
        temp = lcs_rec_search(fixedString, randomString);
        t2 = steady_clock::now();

        time2 = duration<double>(t2 - t1).count();

        cout << "Time for lcs, N = " << n << endl;
        cout << "Time:" << time1 << endl;
        cout << "-------------------------------------" << endl;

        cout << "Time for lcs_rec_search, N = " << n << endl;
        cout << "Time:" << time2 << endl;
        cout << "-------------------------------------" << endl;
        n += size_multiplicator;
    }







    return result;
}
