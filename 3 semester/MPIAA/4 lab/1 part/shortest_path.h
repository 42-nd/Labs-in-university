#pragma once

#include "graph.h"
#include <limits.h>
#include <vector>

/// Return shortest path from start to end as array of vertices.
std::vector<int> shortest_path(const Graph& graph, int start_vertex, int end_vertex);
