#include "graph.h"

#include <vector>
#include <iostream>
#include <algorithm>
#include <limits>
/// Solve Travelling Salesman Problem (TSP) for the graph:
/// Find the shortest (with a minimal total weight) tour and return it as an array of vertices.
std::vector<int> TSP_LS(const Graph& graph);
std::vector<int> Transform(const std::vector<int>& path, int i, int j);
double calculate_path_length(const std::vector<int>& path, const Graph& graph);