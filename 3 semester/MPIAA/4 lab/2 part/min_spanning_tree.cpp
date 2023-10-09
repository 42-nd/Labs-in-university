#include "min_spanning_tree.h"
// Prim's Algorithm
using namespace std;

struct Edge {
    int from, to;
    double weight;

    Edge(int f, int t, double w) : from(f), to(t), weight(w) {}

    // Override the comparison operator for use in the min-heap
    bool operator<(const Edge& other) const {
        return weight > other.weight;
    }
};

vector<pair<int, int>> min_spanning_tree(const Graph& graph) {
    // Return minimal spanning tree (MST) for the graph as an array of edges.
    // Each edge is represented by its two vertices.
    // Order of edges in the result and vertices in edges doesn't matter.
    // Return an empty array if MST doesn't exist.
    vector<pair<int, int>> result;
    priority_queue<Edge> min_heap;
    set<int> visited;

    // Choose a starting vertex (can choose any)
    if (!graph.get_vertices().empty()) {
        int start_vertex = graph.get_vertices()[0];
        visited.insert(start_vertex);

        // Add all incident edges of the starting vertex to the min-heap
        for (const auto& adj_edge : graph.get_adjacent_edges(start_vertex)) {
            int to_vertex = adj_edge.first;
            double weight = adj_edge.second;
            min_heap.push(Edge(start_vertex, to_vertex, weight));
        }

        while (!min_heap.empty()) {
            Edge current_edge = min_heap.top();
            min_heap.pop();
            int from_vertex = current_edge.from;
            int to_vertex = current_edge.to;

            // If the to_vertex is already visited, skip this iteration
            if (visited.count(to_vertex) > 0)
                continue;

            // Add the edge to the result and mark the vertex as visited
            result.push_back(make_pair(from_vertex, to_vertex));
            visited.insert(to_vertex);

            // Add the incident edges of the to_vertex to the min-heap
            for (const auto& adj_edge : graph.get_adjacent_edges(to_vertex)) {
                int next_vertex = adj_edge.first;
                double weight = adj_edge.second;
                min_heap.push(Edge(to_vertex, next_vertex, weight));
            }
        }
    }

    return result;
}
