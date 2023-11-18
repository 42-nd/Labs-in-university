#include "graph.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <limits>
using namespace std;
#include "config.h"
/// Solve Travelling Salesman Problem (TSP) for the graph:
/// Find the shortest (with a minimal total weight) tour and return it as an array of vertices.
vector<int> TSP_GA(const Graph& g, int P, int N, int MaxIt, double Pm, bool informe);
vector<int> CrossoverER(const vector<int>& parent1, const vector<int>& parent2);
vector<int> TwoOptImprove(const Graph& graph, const vector<int>& path);
vector<int> Transform(const vector<int>& path, const int& a, const int& b, const int& c, const int& d);
double length(const Graph& g, const vector<int>& path);
double Random(double a, double b);
vector<int> RandomPath(const Graph& g);
vector<int> reversed(const vector<int>& path);
vector<int> start_with(const vector<int>& path, int vertex);
vector<int> min_dir(const vector<int>& path);
vector<int> aligned(const vector<int>& path, int start_vertex);