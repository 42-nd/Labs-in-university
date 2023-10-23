#include"tsp.h"
using namespace std;

double calculate_path_length(const vector<int>& path, const Graph& graph) {
    double length = 0.0;
    for (size_t i = 0; i < path.size() - 1; ++i) {
        length += graph.edge_weight(path[i], path[i + 1]);
    }
    length += graph.edge_weight(path.back(), path.front()); // замыкаем маршрут
    return length;
}

vector<int> two_opt_swap(const vector<int>& path, int i, int j) {
    vector<int> new_path = path;
    reverse(new_path.begin() + i, new_path.begin() + j + 1);
    return new_path;
}

vector<int> TSP_LS(const Graph& graph) {
    if (graph.get_vertices().empty() || graph.get_vertices().size() == 1) {
        return vector<int>();
    }

    vector<int> current_path = graph.get_vertices(); // случайный маршрут
    bool improved = true;

    while (improved) {
        improved = false;
        for (size_t i = 0; i < current_path.size() - 1; ++i) {
            for (size_t j = i + 1; j < current_path.size(); ++j) {
                double old_length = calculate_path_length(current_path, graph);
                vector<int> new_path = two_opt_swap(current_path, i, j);
                double new_length = calculate_path_length(new_path, graph);
                if (new_length < old_length) {
                    current_path = new_path;
                    improved = true;
                }
            }
        }
    }

    return current_path;
}
