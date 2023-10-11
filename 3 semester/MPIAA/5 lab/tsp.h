#include "graph.h"
#include <algorithm>
#include <vector>
#include <limits>
#include <numeric>
#include <queue>
#include <unordered_set>
/// Solve Travelling Salesman Problem (TSP) for the graph:
/// Find the shortest (with a minimal total weight) tour and return it as an array of vertices.
std::vector<int> tsp_permutations(const Graph &graph);
std::vector<int> tsp_branches(const Graph& graph);
std::vector<int> tsp_greedy(const Graph& G);