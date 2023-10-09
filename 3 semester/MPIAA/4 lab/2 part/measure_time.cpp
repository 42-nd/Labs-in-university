#include "measure_time.h"

Graph random_graph(int size) {
    Graph graph;
    int vertices = size - 1;
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution_distance(10, 100);

    for (int i = 0; i < vertices; ++i) {
        graph.add_edge(i, i + 1, distribution_distance(generator) / 10.0);
    }

    int additional_edges = random_number(size);

    for (int i = 0; i < additional_edges; ++i) {
        int vertex_1 = random_number(size);
        int vertex_2 = random_number(size);
        if (!(graph.has_edge(vertex_1, vertex_2) || vertex_1 == vertex_2)) {
            graph.add_edge(vertex_1, vertex_2, distribution_distance(generator) / 10.0);
        }
    }

    return graph;
}

int random_number(int size) {
    srand(time(NULL));

    return rand() % size;
}

void measure_time() {
    double time_stop = 0.5;
    double time1 = 0;
    int N = 10;
    int muli = 10;
    do {
        Graph graph = random_graph(N);

        auto t1 = std::chrono::high_resolution_clock::now(); // Record time before executing the algorithm
        std::vector<std::pair<int, int>> result = min_spanning_tree(graph);
        auto t2 = std::chrono::high_resolution_clock::now(); // Record time after executing the algorithm
        time1 = std::chrono::duration<double>(t2 - t1).count(); // Calculate the time difference

        std::cout << "min_spanning_tree: " << "N = " << N << ", " << "time = " << time1 << " seconds" << std::endl;
        N *= muli;
    } while (time1 < time_stop);
}

