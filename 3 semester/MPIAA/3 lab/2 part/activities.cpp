#include "activities.h"
#include <vector>
#include <iostream>

#include <algorithm>
bool is_compatible(const Activity& activity1, const Activity& activity2) {
    return activity1.finish <= activity2.start || activity2.finish <= activity1.start;
}

std::vector<Activity> get_max_activities_full_search(const std::vector<Activity>& activities) {
    int n = activities.size();

    if (n <= 1) {
        return activities; 
    }
    
    std::vector<Activity> maxActivities; 


    for (int i = 0; i < (1 << n); ++i) {
        std::vector<Activity> currentActivities;

        for (int j = 0; j < n; ++j) {
            if (i & (1 << j)) {
                currentActivities.push_back(activities[j]);
            }
        }

        bool isCompatible = true;

        for (int k = 0; k < currentActivities.size(); ++k) {
            for (int l = k + 1; l < currentActivities.size(); ++l) {
                if (!is_compatible(currentActivities[k], currentActivities[l])) {
                    isCompatible = false;
                    break;
                }
            }
            if (!isCompatible) {
                break;
            }
        }

        if (isCompatible && currentActivities.size() > maxActivities.size()) {
            maxActivities = currentActivities;
        }
    }

    return maxActivities;
}
std::vector<Activity> get_max_activities(const std::vector<Activity>& activities) {
    std::vector<Activity> SortedActivities = activities; 
    sort(SortedActivities.begin(), SortedActivities.end(), [](Activity& a, Activity& b) {
        return a.finish < b.finish;
        });
    int CurrentIndex = 0;
    std::vector<Activity> maxActivities;
    while (CurrentIndex < size(SortedActivities)) {
        maxActivities.push_back(SortedActivities[CurrentIndex]);
        int NextIndex = CurrentIndex + 1;

        while (NextIndex < size(SortedActivities) && !is_compatible(SortedActivities[CurrentIndex], SortedActivities[NextIndex])) {
            NextIndex++;
        }

        if (NextIndex < size(SortedActivities)) {
            CurrentIndex = NextIndex;
        }
        else {
            break;
        }
    }

    return maxActivities;
}