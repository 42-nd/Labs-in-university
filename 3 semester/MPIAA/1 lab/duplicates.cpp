#include "duplicates.h"
#include <set>
#include <unordered_set>
// SLOW ALGOS
bool slow_has_duplicates(const std::vector<int>& data)
{ // O{n^2)
    for (size_t i = 0; i < data.size(); ++i)
    {
        for (size_t j = i + 1; j < data.size(); ++j)
        {
            if (data[i] == data[j])
            {
                return true;
            }
        }
    }
    return false;
}

std::vector<int> slow_get_duplicates(const std::vector<int>& data)
{ // O(n^2) or O(n^3)
    std::vector<int> duplicates;

    for (size_t i = 0; i < data.size(); ++i)
    {
        for (size_t j = i + 1; j < data.size(); ++j)
        {
            if (data[i] == data[j])
            {
                auto it = find(duplicates.begin(), duplicates.end(), data[i]);
                if (it == duplicates.end())
                {
                    duplicates.push_back(data[i]);
                }
            }
        }
    }

    return duplicates;
}
// FAST ALGOS
bool has_duplicates(const std::vector<int>& data)
{ // O(n) - time O(n) - space worst
    std::unordered_set<int> seen;
    for (const auto& element : data)
    {
        if (seen.count(element) > 0)
        {
            return true;
        }
        seen.insert(element);
    }
    return false;
}

std::vector<int> get_duplicates(const std::vector<int>& data)
{ // O(n) - time O(n) - space worst
    std::unordered_set<int> seen;
    std::vector<int> duplicates;

    for (const auto& element : data)
    {
        if (seen.count(element) > 0)
        {
            auto it = find(duplicates.begin(), duplicates.end(), element);
            if (it == duplicates.end())
            {
                duplicates.push_back(element);
            }
        }
        else
        {
            seen.insert(element);
        }
    }

    return duplicates;
}