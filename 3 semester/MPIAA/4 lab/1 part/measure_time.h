#pragma once

#include "shortest_path.h"
#include <iostream>
#include <random>
#include <numeric>
#include <chrono>
#include <ctime>

Graph random_graph(int size);
int random_number(int size);
void measure_time();
double shortest_path_time(const Graph& graph, int start_vertex, int end_vertex);
