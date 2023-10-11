#pragma once

#include "graph.h"
#include <iostream>
#include <random>
#include <numeric>
#include <chrono>
#include <ctime>

Graph random_graph(int size);
int random_number(int size);
void measure_time(const Graph& graph, int N);
