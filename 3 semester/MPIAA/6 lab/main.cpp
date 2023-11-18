#include <random>
#include "graph.h"
#include "measure_time.h"
using namespace std;
int random_number(int size) {
    srand(time(NULL));

    return rand() % size;
}

Graph random_graph(int size) {
    Graph graph;
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution_distance(10, 100);

    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            graph.add_edge(i, j, distribution_distance(generator) / 10.0);
        }
    }
    return graph;
}
int main(int argc, char* argv[]) {
    
    int multi = 2;
    int size_stop = 2048;
    int N = 64;
    while (N < size_stop) {
        cout << "Start for graph size : " << N << endl;
        measure_time(random_graph(N), N);
        N *= multi;
        cout << "----------------------------------------" << endl;
    }
    return 0;
}
