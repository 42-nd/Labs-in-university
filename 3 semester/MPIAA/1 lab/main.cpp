#include "duplicates.h"
#include <iostream>
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include <chrono>


using namespace std;
using namespace std::chrono;

int main(int argc, char **argv)
{
    int result = Catch::Session().run(argc, argv);

    double time = 0.0;
    double time_stop = 0.2;
    int size_multiplicator = 10;
    int size = 10;
    while (time < time_stop)
    {
        cout << "Time for slow_has_duplicates, N = " << size << endl;
        const auto data = shuffled_sequence(size);

        auto t1 = steady_clock::now();
        bool isdup = slow_has_duplicates(data);
        auto t2 = steady_clock::now();
        time = duration<double>(t2 - t1).count();
        cout << "isdup? " << isdup << endl;
        cout << "Time :" << time << endl;
        cout << "---------------------------------------------" << endl;
        size *= size_multiplicator;
    }

    time = 0.0;
    size = 10;
    
    while (time < time_stop)
    {
        cout << "Time for slow_get_duplicates, N = " << size << endl;
        const auto data = shuffled_sequence(size);

        auto t1 = steady_clock::now();
        vector<int> dups = slow_get_duplicates(data);
        auto t2 = steady_clock::now();
        time = duration<double>(t2 - t1).count();

        cout << "Time :" << time << endl;
        cout << "---------------------------------------------" << endl;
        size *= size_multiplicator;
    }

    time = 0.0;
    size = 10;

    while (time < time_stop)
    {
        cout << "Time for has_duplicates, N = " << size << endl;
        const auto data = shuffled_sequence(size);

        auto t1 = steady_clock::now();
        bool isdup = has_duplicates(data);
        auto t2 = steady_clock::now();
        time = duration<double>(t2 - t1).count();
        cout << "isdup? " << isdup << endl;
        cout << "Time :" << time << endl;
        cout << "---------------------------------------------" << endl;
        size *= size_multiplicator;
    }

    time = 0.0;
    size = 10;

    while (time < time_stop)
    {
        cout << "Time for get_duplicates, N = " << size << endl;
        const auto data = shuffled_sequence(size);

        auto t1 = steady_clock::now();
        vector<int> dups = get_duplicates(data);
        auto t2 = steady_clock::now();
        time = duration<double>(t2 - t1).count();

        cout << "Time :" << time << endl;
        cout << "---------------------------------------------" << endl;
        size *= size_multiplicator;
    }

    return result;
}
