
#pragma once

#include "graph.h"
#include <vector>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>


struct Edge1;
// Return minimal spanning tree for the (connected) graph as array of edges.
std::vector<std::pair<int, int>> min_spanning_tree(const Graph& graph);

