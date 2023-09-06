#pragma once

#include "point.h"

#include <vector>

// Find the closest pair of points from given points.
std::pair<Point, Point> closest_pair(const std::vector<Point> &points);
std::pair<Point, Point> closest_pair_full_search(const std::vector<Point>& points);
std::vector<double> shuffled_sequence(int size);