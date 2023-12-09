#include <random>
#include "graph.h"
#include "tsp_ga.h"
#include "measure_time.h"
using namespace std;

Graph random_graph(int size) {
    Graph graph;
    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            graph.add_edge(i, j, Random(0, 100) / 10.0);
        }
    }
    return graph;
}
int main(int argc, char* argv[]) {
    
    int multi = 2;
    int size_stop = 2048;
    int N = 16;
    while (N < size_stop) {
        cout << "Start for graph size : " << N << endl;
        measure_time(random_graph(N), N);
        N *= multi;
        cout << "----------------------------------------" << endl;
    }
    return 0;
}
