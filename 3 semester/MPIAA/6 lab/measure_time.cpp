#include "measure_time.h"
#include "tsp_ga.h"
#include "tsp_ls.h"
#include "tsp.h"
using namespace std;
void measure_time(const Graph& graph,int N) {
    double time_stop = 10;
    double time1 = 0;
    auto t1 = std::chrono::high_resolution_clock::now(); // Record time before executing the algorithm
    std::vector<int> result = TSP_GA(graph, P, Ne, MaxIt, Pm, informe);
    auto t2 = std::chrono::high_resolution_clock::now(); // Record time after executing the algorithm
    time1 = std::chrono::duration<double>(t2 - t1).count(); // Calculate the time difference
    std::cout << "TSP_GA: " << "N = " << N << ", " << "time = " << time1 << " seconds " << std::endl;
    if (display_paths) {
        std::cout << "Path:" << std::endl;
        for (auto it : result) {
            std::cout << it << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Path lenght: " << length(graph, result) << std::endl;
    if (!only_ga) {
        time1 = 0;
        t1 = std::chrono::high_resolution_clock::now(); // Record time before executing the algorithm
        result = TSP_LS(graph);
        t2 = std::chrono::high_resolution_clock::now(); // Record time after executing the algorithm
        time1 = std::chrono::duration<double>(t2 - t1).count(); // Calculate the time difference
        std::cout << "TSP_LS: " << "N = " << N << ", " << "time = " << time1 << " seconds " << std::endl;
        if (display_paths) {
            std::cout << "Path:" << std::endl;
            for (auto it : result) {
                std::cout << it << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "Path lenght: " << length(graph, result) << std::endl;

        time1 = 0;
        t1 = std::chrono::high_resolution_clock::now(); // Record time before executing the algorithm
        result = tsp_greedy(graph);
        t2 = std::chrono::high_resolution_clock::now(); // Record time after executing the algorithm
        time1 = std::chrono::duration<double>(t2 - t1).count(); // Calculate the time difference
        std::cout << "tsp_greedy: " << "N = " << N << ", " << "time = " << time1 << " seconds " << std::endl;
        if (display_paths) {
            std::cout << "Path:" << std::endl;
            for (auto it : result) {
                std::cout << it << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "Path lenght: " << length(graph, result) << std::endl;

    }
    
}

