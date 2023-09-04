#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <random>
#include <list>
#include <chrono>
#include <set>
#include <unordered_set>

using namespace std;
using namespace std::chrono;

// Returns shuffled sequence of unique numbers of specified size, with values from start to start + size - 1.
vector<int> shuffled_sequence(int size, int start = 0)
{
    vector<int> result(size);
    iota(result.begin(), result.end(), start);
    random_device rd;
    mt19937 rng(rd());
    shuffle(result.begin(), result.end(), rng);
    return result;
}

// Returns sequence of random numbers of specified size, with values from 0 to max.
vector<int> random_sequence(int size, int max)

{
    default_random_engine generator;
    uniform_int_distribution<int> distribution(0, max);
    vector<int> result;
    for (int i = 0; i < size; i++)
    {
        result.push_back(distribution(generator));
    }
    return result;
}

template <typename Container>
auto measure_time_list_and_vector(Container &container, int size)
{
    // Perform push_back into container
    auto t1 = steady_clock::now();
    const auto elems_to_add = shuffled_sequence(size);
    for (const auto &elem : elems_to_add)
    {
        container.push_back(elem);
    }
    auto t2 = steady_clock::now();
    auto time1 = duration<double>(t2 - t1).count();
    cout << "Push_back: " << time1 << " seconds" << endl;

    // Perform instertion into container
    container.clear();
    t1 = steady_clock::now();
    const auto elems_to_insert = shuffled_sequence(size);
    for (const auto &elem : elems_to_insert)
    {
        container.insert(container.end(), elem);
    }
    t2 = steady_clock::now();
    auto time2 = duration<double>(t2 - t1).count();
    cout << "Insert: " << time2 << " seconds" << endl;

    // Perform search into container.
    int hits = 0;
    const auto elems_to_search = random_sequence(10, size);
    t1 = steady_clock::now();
    for (const auto &elem : elems_to_search)
    {
        auto it = find(container.begin(), container.end(), elem);
        if (it != container.end())
        {
            hits++;
        }
    }
    t2 = steady_clock::now();
    auto time3 = duration<double>(t2 - t1).count();
    cout << "Find: " << time3 << " seconds" << endl;
    auto fulltime = time1 + time2 + time3;
    cout << "Fulltime: " << fulltime << " seconds" << endl;
    return fulltime;
}

template <typename Container>
auto measure_time_set_and_unordered_set(Container &container, int size)
{
    // Perform push_back into container
    auto t1 = steady_clock::now();
    const auto elems_to_add = shuffled_sequence(size);
    for (const auto &elem : elems_to_add)
    {
        container.insert(elem);
    }
    auto t2 = steady_clock::now();
    auto time1 = duration<double>(t2 - t1).count();
    cout << "Insert: " << time1 << " seconds" << endl;

    // Perform search into container.
    int hits = 0;
    const auto elems_to_search = random_sequence(10, size);
    t1 = steady_clock::now();
    for (const auto &elem : elems_to_search)
    {
        auto it = container.find(elem);
        if (it != container.end())
        {
            hits++;
        }
    }
    t2 = steady_clock::now();
    auto time2 = duration<double>(t2 - t1).count();
    cout << "Find: " << time2 << " seconds" << endl;

    auto fulltime = time1 + time2;
    cout << "Fulltime: " << fulltime << " seconds" << endl;
    return fulltime;
}

int main(int argc, char **argv)
{
    // Containers to use.
    vector<int> container_vector;
    list<int> container_list;
    set<int> container_set;
    unordered_set<int> container_unordered_set;

    double total_time = 0.0;
    double time_stop = 1.0;
    int size_multiplicator = 10;
    int n = 10;

    while (total_time < time_stop)
    {
        cout << "Time for vector N = " << n << endl;
        total_time += measure_time_list_and_vector(container_vector, n);
        cout << "---------------------------------------------" << endl;
        n *= size_multiplicator;
    }

    total_time = 0.0;
    n = 10;
    while (total_time < time_stop)
    {
        cout << "Time for list N = " << n << endl;
        total_time += measure_time_list_and_vector(container_list, n);
        cout << "---------------------------------------------" << endl;
        n *= size_multiplicator;
    }

    total_time = 0.0;
    n = 10;
    while (total_time < time_stop)
    {
        cout << "Time for set N = " << n << endl;
        total_time += measure_time_set_and_unordered_set(container_set, n);
        cout << "---------------------------------------------" << endl;
        n *= size_multiplicator;
    }

    total_time = 0.0;
    n = 10;
    while (total_time < time_stop)
    {
        cout << "Time for unordered_set N = " << n << endl;
        total_time += measure_time_set_and_unordered_set(container_unordered_set, n);
        cout << "---------------------------------------------" << endl;
        n *= size_multiplicator;
        // Увеличиваем размер вдвое на каждой итерации
    }
}