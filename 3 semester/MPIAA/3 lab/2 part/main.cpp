#define CATCH_CONFIG_RUNNER

#include "catch.hpp"
#include <iostream>
#include <chrono>
#include <random>
#include "activities.h"
using namespace std;
using namespace std::chrono;
int main(int argc, char* argv[]) {
    int result = Catch::Session().run(argc, argv);

    default_random_engine generator;

    vector<Activity> randomActivities;
    double time1 = 0.0;
    double time2 = 0.0;
    double time_stop = 0.6;
    int size_multiplicator = 2;
    int n = 5;

    uniform_int_distribution<int> startDistribution(0, 1000); 
    uniform_int_distribution<int> finishDistribution(1, 100);
    while (time1 < time_stop && time2 < time_stop)
    {
        for (int i = 0; i < n; ++i) {
            int start = startDistribution(generator);
            int finish = start + finishDistribution(generator);
            randomActivities.push_back(Activity(start, finish));
        }
        cout << "Time for  get_max_activities_full_search, N = " << n << endl;
        auto t1 = steady_clock::now();
        vector<Activity> result1 = get_max_activities_full_search(randomActivities);
        auto t2 = steady_clock::now();
        time1 = duration<double>(t2 - t1).count();

        cout << "Time :" << time1 << endl;
        cout << "---------------------------------------------" << endl;

        cout << "Time for get_max_activities, N = " << n << endl;
        t1 = steady_clock::now();
        result1 = get_max_activities(randomActivities);
        t2 = steady_clock::now();
        time2 = duration<double>(t2 - t1).count();

        cout << "Time :" << time2 << endl;
        cout << "---------------------------------------------" << endl;

        n += size_multiplicator;
    }

    return result;
}
