#include "tsp.h"
#include <iostream>
using namespace std;

double calculateTourWeight(const vector<int>& tour, const Graph& graph) {
    double weight = 0;
    for (size_t i = 0; i < tour.size() - 1; ++i) {
        weight += graph.edge_weight(tour[i], tour[i + 1]);
    }
    // Add the weight of the edge from the last vertex back to the start vertex
    weight += graph.edge_weight(tour.back(), tour.front());
    return weight;
}

void generatePermutations(vector<int>& tour, vector<int>& bestTour, double& minWeight, const Graph& graph) {
    if (tour.size() == graph.get_vertices().size()) {
        double weight = calculateTourWeight(tour, graph);
        if (weight < minWeight) {
            minWeight = weight;
            bestTour = tour;
        }
        return;
    }

    vector<int> vertices = graph.get_vertices();
    for (int vertex : vertices) {
        if (find(tour.begin(), tour.end(), vertex) == tour.end()) {
            tour.push_back(vertex);
            generatePermutations(tour, bestTour, minWeight, graph);
            tour.pop_back();
        }
    }
}

vector<int> tsp_permutations(const Graph& graph) {
    vector<int> tour, bestTour;
    double minWeight = numeric_limits<double>::max();

    if (graph.get_vertices().size() <= 1) {
        return tour;
    }

    tour.push_back(graph.get_vertices()[0]);

    if (graph.get_vertices().size() == 1) {
        return tour;
    }

    generatePermutations(tour, bestTour, minWeight, graph);

    return bestTour;
}

double Length(const vector<int>& path, const Graph& graph) {
    if (path.size() == 1) {
        return std::numeric_limits<double>::infinity();
    }
    double length = 0.0;
    for (size_t i = 0; i < path.size() - 1; ++i) {
        length += graph.edge_weight(path[i], path[i + 1]);
    }
    if (path.back() != path.front()) {
        length += graph.edge_weight(path.back(), path.front());  // Замыкаем маршрут
    }
    return length;
}

vector<int> MinPath(const vector<int>& path1, const vector<int>& path2, const Graph& graph) {
    return Length(path1, graph) < Length(path2, graph) ? path1 : path2;
}

double LowerBound(const Graph& graph, const vector<int>& visited) {
    double lowerBound = 0.0;
    for (int v : graph.get_vertices()) {
        if (find(visited.begin(), visited.end(), v) == visited.end()) {
            vector<pair<int, double>> edges = graph.get_adjacent_edges(v);
            sort(edges.begin(), edges.end(), [](const pair<int, double>& a, const pair<int, double>& b) {
                return a.second < b.second;
                });

            if (edges.size() >= 2) {
                lowerBound += (edges[0].second + edges[1].second) / 2;
            }
            else if (!edges.empty()) {
                lowerBound += edges[0].second;
            }
        }
    }
    return lowerBound;
}

vector<int> BnB(const Graph& graph, vector<int> visited, vector<int>& bestPath) {
    if (visited.size() == graph.get_vertices().size()) {
        return MinPath(bestPath, visited, graph);
    }

    for (int v : graph.get_vertices()) {
        if (find(visited.begin(), visited.end(), v) == visited.end()) {
            vector<int> nextVisited = visited;
            nextVisited.push_back(v);
            //cout <<nextVisited.size() << " " << bestPath.size() << " " << LowerBound(graph, nextVisited) << " cccc" << Length(bestPath, graph) << endl;
            if (LowerBound(graph, nextVisited) < Length(bestPath, graph)) {
                vector<int> newPath = BnB(graph, nextVisited, bestPath);
                //cout << bestPath.size() << " " << newPath.size() << endl;
                bestPath = MinPath(bestPath, newPath, graph);
            }
        }
    }
    return bestPath;
}

vector<int> tsp_branches(const Graph& graph) {
    vector<int> vertices = graph.get_vertices();
    if (vertices.empty()) {
        return vector<int>();  
    }

    if (vertices.size() == 1) {
        return vector<int>();
    }

    vector<int> initialPath = { vertices[0] };  // Начинаем с первой вершины
    vector<int> bestPath = { 0};
    return BnB(graph, initialPath, bestPath);
}

vector<int> tsp_greedy(const Graph& G) {
    vector<int> path;
    if (G.get_vertices().empty()) {
        return path;  // возвращаем пустой путь для графа без вершин
    }

    path.push_back(0);
    unordered_set<int> visited;
    visited.insert(0);

    while (visited.size() < G.get_vertices().size()) {
        int current = path.back();
        double min_weight = numeric_limits<double>::infinity();
        int next_vertex = -1;

        // Находим следующую вершину с минимальным весом ребра
        for (const auto& edge : G.get_adjacent_edges(current)) {
            int neighbor = edge.first;
            double weight = edge.second;
            if (visited.find(neighbor) == visited.end() && weight < min_weight) {
                min_weight = weight;
                next_vertex = neighbor;
            }
        }

        // Если не удалось найти следующую вершину, вернуться к начальной
        if (next_vertex == -1) {
            next_vertex = 0;
        }

        // Добавляем следующую вершину в путь и отмечаем её как посещенную
        path.push_back(next_vertex);
        visited.insert(next_vertex);
    }

    return path;
}