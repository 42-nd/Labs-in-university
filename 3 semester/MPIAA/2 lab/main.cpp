#include "closest_pair.h"
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include <chrono>
using namespace std;
using namespace std::chrono;
int main(int argc, char **argv) {
    int result = Catch::Session().run(argc, argv);
    
    double time1 = 0.0;
    double time2 = 0.0;
    double time_stop = 0.6;
    int size_multiplicator = 10;
    int n = 20;
    while (time1 < time_stop && time2 < time_stop)
    {
        std::vector<double> seq = shuffled_sequence(n);
        std::vector<Point> Points;
        for (int i = 0; i < size(seq); i += 2) {
            Points.push_back(Point(seq[i], seq[i + 1]));
        }
        cout << "Time for closest_pair_full_search, N = " << n<< endl;
        auto t1 = steady_clock::now();
        pair<Point, Point> slow = closest_pair_full_search(Points);
        auto t2 = steady_clock::now();
        time1 = duration<double>(t2 - t1).count();

        cout << "Time :" << time1 << endl;
        cout << "---------------------------------------------" << endl;

        cout << "Time for closest_pair, N = " << n << endl;
        t1 = steady_clock::now();
        pair<Point, Point> fast = closest_pair(Points);
        t2 = steady_clock::now();
        time2 = duration<double>(t2 - t1).count();

        cout << "Time :" << time2 << endl;
        cout << "---------------------------------------------" << endl;

        n *= size_multiplicator;
    }
    return result;
}
