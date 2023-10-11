#include "measure_time.h"
#include "tsp.h"
Graph random_graph(int size) {
    Graph graph;
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution_distance(10, 100);

    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            graph.add_edge(i, j, distribution_distance(generator) / 10.0);
        }
    }

    int additional_edges = random_number(size);

    for (int i = 0; i < additional_edges; ++i) {
        int vertex_1 = std::uniform_int_distribution<int>(0, size - 1)(generator);
        int vertex_2 = std::uniform_int_distribution<int>(0, size - 1)(generator);
        if (vertex_1 != vertex_2 && graph.has_edge(vertex_1, vertex_2)) {
            graph.remove_edge(vertex_1, vertex_2);
        }
    }

    return graph;
}

int random_number(int size) {
    srand(time(NULL));

    return rand() % size;
}

void measure_time(const Graph& graph,int N) {
    double time_stop = 10;
    double time1 = 0;
    //int N = 3;
    int muli = 1;
    //do {
        //Graph graph = random_graph(N);

        auto t1 = std::chrono::high_resolution_clock::now(); // Record time before executing the algorithm
        std::vector<int> result = tsp_permutations(graph);
        auto t2 = std::chrono::high_resolution_clock::now(); // Record time after executing the algorithm
        time1 = std::chrono::duration<double>(t2 - t1).count(); // Calculate the time difference
        std::cout << "tsp_permutations: " << "N = " << N << ", " << "time = " << time1 << " seconds" << std::endl;

        t1 = std::chrono::high_resolution_clock::now(); // Record time before executing the algorithm
        result = tsp_branches(graph);
        t2 = std::chrono::high_resolution_clock::now(); // Record time after executing the algorithm
        time1 = std::chrono::duration<double>(t2 - t1).count(); // Calculate the time difference
        std::cout << "tsp_branches: " << "N = " << N << ", " << "time = " << time1 << " seconds" << std::endl;

        t1 = std::chrono::high_resolution_clock::now(); // Record time before executing the algorithm
        result = tsp_greedy(graph);
        t2 = std::chrono::high_resolution_clock::now(); // Record time after executing the algorithm
        time1 = std::chrono::duration<double>(t2 - t1).count(); // Calculate the time difference
        std::cout << "tsp_greedy: " << "N = " << N << ", " << "time = " << time1 << " seconds" << std::endl;
        std::cout << "---------------------------------" << std::endl;
        //N += muli;
    //} while (time1 < time_stop);
}

