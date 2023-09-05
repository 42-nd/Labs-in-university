#include <vector>
#include <numeric>
#include <random>
#include "duplicates.h"

using namespace std;

// Returns shuffled sequence of unique numbers of specified size, with values from start to start + size - 1.
vector<int> shuffled_sequence(int size)
{
    vector<int> result(size);
    iota(result.begin(), result.end(), 0);
    random_device rd;
    mt19937 rng(rd());
    shuffle(result.begin(), result.end(), rng);
    return result;
}
