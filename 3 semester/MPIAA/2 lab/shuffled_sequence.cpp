#include <vector>
#include <numeric>
#include <random>

using namespace std;

// Returns shuffled sequence of unique numbers of specified size, with values from start to start + size - 1.
vector<double> shuffled_sequence(int size)
{
    vector<double> result(size);
    iota(result.begin(), result.end(), 0);
    random_device rd;
    mt19937 rng(rd());
    shuffle(result.begin(), result.end(), rng);
    return result;
}
