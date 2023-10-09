
#include "shortest_path.h"
#include <limits.h>
using namespace std;

    vector<int> shortest_path(const Graph & graph, int start_vertex, int end_vertex) {
        // Return shortest path in the graph from start vertex to end vertex as array of vertices.
        // First item in the result should be start vertex, last - end vertex.
        // Return empty array if there is no path.

        // Your implementation here.
        if (graph.get_vertices().size() < 2 || graph.get_adjacent_vertices(end_vertex).size() < 1 || start_vertex == end_vertex)
            return vector<int> {};

        vector<int> result;
        map<int, double> distance;
        vector<int> vertices = graph.get_vertices();

        for (int i = 0; i < vertices.size(); ++i) {
            distance.emplace(vertices[i], DBL_MAX);
        }

        map<int, int> parent;
        for (int i = 0; i < vertices.size(); ++i) {
            parent.emplace(vertices[i], -1);
        }

        distance[start_vertex] = 0;

        while (!vertices.empty()) {
            double min_distance = distance[vertices[0]];
            int min_distance_vertex = vertices[0];

            for (int i = 0; i < vertices.size(); ++i) {
                if (distance[vertices[i]] < min_distance) {
                    min_distance = distance[vertices[i]];
                    min_distance_vertex = vertices[i];
                }
            }

            vertices.erase(find(vertices.begin(), vertices.end(), min_distance_vertex));

            if (min_distance_vertex == end_vertex) {
                int vertex = end_vertex;

                while (vertex != start_vertex) {
                    result.insert(result.begin(), vertex);
                    vertex = parent[vertex];
                    if (vertex == -1) {
                        return vector<int> {};
                    }
                }
                result.insert(result.begin(), start_vertex);

                return result;
            }

            vector<int> adjacent_vertices = graph.get_adjacent_vertices(min_distance_vertex);
            for (int i = 0; i < adjacent_vertices.size(); ++i) {
                if (distance[adjacent_vertices[i]] > distance[min_distance_vertex] + graph.edge_weight(min_distance_vertex, adjacent_vertices[i])) {
                    distance[adjacent_vertices[i]] = distance[min_distance_vertex] + graph.edge_weight(min_distance_vertex, adjacent_vertices[i]);
                    parent[adjacent_vertices[i]] = min_distance_vertex;
                }
            }

        }
    }

