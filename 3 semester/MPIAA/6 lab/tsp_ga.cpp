#include "tsp_ga.h"
#include <iostream>
using namespace std;
#include  <random>
#include <unordered_map>
#include <unordered_set>



double Random(double a, double b)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dis(min(a, b), max(a, b)); // Ensure a < b
    return dis(gen);
}


double length(const Graph& g, const vector<int>& path){
    if (path.size() <= 1) {
        return double(INFINITY);
    }
    double result = 0;
    for (auto i = 0; i < path.size() - 1; ++i)
    {
        result += g.edge_weight(path[i], path[i + 1]);
    }
    result += g.edge_weight(path[0], path[path.size() - 1]);
    return result;
}

vector<int> RandomPath(const Graph& g){
    int start_vertex = 0;
    vector<int> result;
    result.push_back(start_vertex);
    while (result.size() < g.get_vertices().size())
    {
        auto u = g.get_adjacent_vertices(result[result.size() - 1]);
        int current_vertex = rand() % u.size();
        if (find(result.begin(), result.end(), u[current_vertex]) == result.end()) {
            result.push_back(u[current_vertex]);
        }
    }
    return result;
}

vector<int> Transform(const vector<int>& path, const int& a, const int& b, const int& c, const int& d){
    vector<int> result;
    result.push_back(path[a]);
    for (int i = c; i != b; --i)
    {
        result.push_back(path[i]);
    }
    result.push_back(path[b]);
    for (int i = d; i < path.size(); ++i)
    {
        result.push_back(path[i]);
    }
    for (int i = 0; i < a; ++i)
    {
        result.push_back(path[i]);
    }
    return result;
}

vector<int> TwoOptImprove(const Graph& graph, const vector<int>& path)
{
    if (path.size() <= 3) {
        return path;
    }

    for (int i = 0; i < path.size() - 3; ++i)
    {
        for (int j = i + 2; j < path.size() - 1; ++j)
        {
            int oldWeight = graph.edge_weight(path[i], path[i + 1]) + graph.edge_weight(path[j], path[j + 1]);
            int newWeight = graph.edge_weight(path[i], path[j]) + graph.edge_weight(path[i + 1], path[j + 1]);
            if (newWeight < oldWeight) {
                return Transform(path, i, i + 1, j, j + 1);
            }
        }
    }

    return path;
}

vector<int> CrossoverER(const vector<int>& parent1, const vector<int>& parent2) {
    unordered_map<int, vector<int>> edgeMap;

    // —оздаем карту ребер смежности дл€ каждой вершины
    for (int i = 0; i < parent1.size() - 1; ++i) {
        edgeMap[parent1[i]].push_back(parent1[i + 1]);
        edgeMap[parent2[i]].push_back(parent2[i + 1]);
    }
    edgeMap[parent1.back()].push_back(parent1[0]);
    edgeMap[parent2.back()].push_back(parent2[0]);

    vector<int> offspring;
    int currentVertex = parent1[0];
    offspring.push_back(currentVertex);

    while (offspring.size() < parent1.size()) {
        vector<int> candidates = edgeMap[currentVertex];
        edgeMap[currentVertex].clear(); // ”дал€ем ребра, чтобы не использовать их повторно

        // ¬ыбираем следующую вершину, у которой минимальное число смежных ребер в карте ребер
        int nextVertex = candidates[0];
        int minNumEdges = edgeMap[candidates[0]].size();
        for (int i = 1; i < candidates.size(); ++i) {
            int numEdges = edgeMap[candidates[i]].size();
            if (numEdges < minNumEdges) {
                minNumEdges = numEdges;
                nextVertex = candidates[i];
            }
        }

        currentVertex = nextVertex;
        offspring.push_back(currentVertex);
    }

    return offspring;
}




vector<int> reversed(const vector<int>& path) {
    if (path.empty()) {
        return vector<int> {};
    }
    vector<int> result = { path[0] }; // first item is a start vertex
    result.insert(result.end(), path.rbegin(), path.rend()); // add vertices in reverse order
    result.pop_back(); // remove duplicated start vertex
    return result;
}

vector<int> start_with(const vector<int>& path, int vertex) {
    auto it = find(path.begin(), path.end(), vertex);
    if (it == path.end()) {
        return path;
    }
    vector<int> result(it, path.end());
    result.insert(result.end(), path.begin(), it);
    return result;
}

// From two possible directions for a circlular path choose one with min second vertex.
vector<int> min_dir(const vector<int>& path) {
    if (path.size() <= 1) {
        return path;
    }
    const auto reversed_path = reversed(path);
    return (path[1] <= reversed_path[1] ? path : reversed_path);
}

vector<int> aligned(const vector<int>& path, int start_vertex) {
    return min_dir(start_with(path, start_vertex));
}


vector<int> TSP_GA(const Graph& g, int P, int N, int MaxIt, double Pm, bool informe){
    vector<vector<int>> population;

    while (population.size() < P)
    {
        vector<int> path = RandomPath(g);
        if (!path.empty())
            population.push_back(path);
    }

    for (int it = 0; it < MaxIt; ++it)
    {
        vector<double> weights;
        double totalWeight = 0;

        for (auto& path : population){
            double w = totalWeight - length(g, path);
            weights.push_back(w);
            totalWeight += w;
        }

        //    SUS
        vector<vector<int>> parents;
        double dist = totalWeight / N;
        double start = Random(0, dist);
        double point = start;
        int k = 0;
        double sumWeight = weights[0];

        for (int i = 0; i < N; ++i){
            point = start + i * dist;
            while (sumWeight < point){
                k++;
                sumWeight += weights[k];
            }
            parents.push_back(population[k]);
        }


        vector<vector<int>> offspring;
        while (offspring.size() < P){
            int parentIndex1 = rand() % N;
            int parentIndex2 = rand() % N;
            vector<int> parent1 = parents[parentIndex1];
            vector<int> parent2 = parents[parentIndex2];

            vector<int> child = CrossoverER(parent1, parent2);

            if (Random(0, 1) < Pm) {
                child = TwoOptImprove(g, child);
            }

            offspring.push_back(child);
        }

        population = offspring;
        if (informe && (it+1) % 10 == 0) {
            double tempbestWeight = length(g, population[0]);
            vector<int> tempbestPath = population[0];
            for (auto& path : population)
            {
                double w = length(g, path);
                if (w < tempbestWeight)
                {
                    tempbestWeight = w;
                    tempbestPath = path;
                }
            }
            cout << "Iteration " << it + 1 << ": Best weight = " << tempbestWeight << " Best path:" << endl;
            for (auto i : aligned(tempbestPath,0)) {
                cout << i << " ";
            }
            cout << endl;
        }
        

    }

    double bestWeight = length(g, population[0]);
    vector<int> bestPath = population[0];
    for (auto& path : population)
    {
        double w = length(g, path);
        if (w < bestWeight)
        {
            bestWeight = w;
            bestPath = path;
        }



    }




    return aligned(bestPath, 0);
}


