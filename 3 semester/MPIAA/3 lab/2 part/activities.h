#pragma once

#include "activity.h"

#include <vector>

// Get a maximum-size subset of mutually compatible activities.
std::vector<Activity> get_max_activities(const std::vector<Activity> &activities);
std::vector<Activity> get_max_activities_full_search(const std::vector<Activity>& activities);
