#include "catch.hpp"

#include "tsp.h"
#include "measure_time.h"
#include <algorithm>

using namespace std;

// For a circilar path get its reverse.
vector<int> reversed(const vector<int> &path) {
    if (path.empty()) {
        return vector<int> {};
    }
    vector<int> result = {path[0]}; // first item is a start vertex
    result.insert(result.end(), path.rbegin(), path.rend()); // add vertices in reverse order
    result.pop_back(); // remove duplicated start vertex
    return result;
}

// Rotate path so it starts with the given vertex.
vector<int> start_with(const vector<int> &path, int vertex) {
    auto it = find(path.begin(), path.end(), vertex);
    if (it == path.end()) {
        return path;
    }
    vector<int> result(it, path.end()); // from start vertex to the path's end
    result.insert(result.end(), path.begin(), it); // add the rest of the path
    return result;
}

// From two possible directions for a circlular path choose one with min second vertex.
vector<int> min_dir(const vector<int> &path) {
    if (path.size() <= 1) {
        return path;
    }    
    const auto reversed_path = reversed(path);
    return (path[1] <= reversed_path[1] ? path : reversed_path);
}

vector<int> aligned(const vector<int> &path, int start_vertex) {
    return min_dir(start_with(path, start_vertex));
}

TEST_CASE( "[TSP] Empty graph", "[tsp]" ) {
    Graph g {};    
    CHECK(tsp_permutations(g) == vector<int> {} );
    CHECK(tsp_branches(g) == vector<int> {});
}

TEST_CASE( "[TSP] Single vertex", "[tsp]" ) {
    Graph g {}; 
    g.add_vertex(0);   
    CHECK(tsp_permutations(g) == vector<int> {} );
    CHECK(tsp_branches(g) == vector<int> {});
}

TEST_CASE( "[TSP] One edge", "[tsp]" ) {
    Graph g {{0, 1, 2.5}};
    measure_time(g,2);
    const auto result_permutations = tsp_permutations(g);
    const auto result_branches = tsp_branches(g);
    const auto expected = vector<int> {0, 1};  
    CHECK(aligned(result_permutations, 0) == expected );
    CHECK(aligned(result_branches, 0) == expected);
}

TEST_CASE("[TSP] Three vertices, three edges", "[tsp]") {
    Graph g{ {0, 1, 2.5}, {0, 2, 0.5}, {1, 2, 1.0} };
    measure_time(g, 3);
    const auto result_permutations = tsp_permutations(g);
    const auto result_branches = tsp_branches(g);
    const auto expected = std::vector<int>{ 0, 1, 2 };
    CHECK(aligned(result_permutations, 0) == expected);
    CHECK(aligned(result_branches, 0) == expected);
}

TEST_CASE( "[TSP] Four vertices", "[tsp]" ) {
    Graph g {{0, 1, 6.0}, {0, 2, 4.0}, {0, 3, 1.0},
             {1, 2, 3.5}, {1, 3, 2.0}, 
             {2, 3, 5.0}};
    measure_time(g,4);
    const auto result_permutations = tsp_permutations(g);
    const auto result_branches = tsp_branches(g);
    const auto expected = vector<int> {0, 2, 1, 3};
    CHECK(aligned(result_permutations, 0) == expected);
    CHECK(aligned(result_branches, 0) == expected);
}

TEST_CASE( "[TSP] Five vertices", "[tsp]" ) {
    Graph g {{0, 1, 2.0}, {0, 2, 4.0}, {0, 3, 1.0}, {0, 4, 2.5},
             {1, 2, 3.6}, {1, 3, 6.0}, {1, 4, 3.0}, 
             {2, 3, 7.0}, {2, 4, 5.0}, 
             {3, 4, 9.0}};      
    measure_time(g,5);
    const auto result_permutations = tsp_permutations(g);
    const auto result_branches = tsp_branches(g);
    const auto expected = vector<int> {0, 3, 2, 1, 4};
    CHECK(aligned(result_permutations, 0) == expected);
    CHECK(aligned(result_branches, 0) == expected);
}

TEST_CASE( "[TSP] Six vertices", "[tsp]" ) {
    Graph g {{0, 1, 2.0}, {0, 2, 4.0}, {0, 3, 1.0}, {0, 4, 2.5}, {0, 5, 3.2},
             {1, 2, 3.6}, {1, 3, 6.0}, {1, 4, 3.0}, {1, 5, 0.1},
             {2, 3, 7.0}, {2, 4, 5.0}, {2, 5, 9},
             {3, 4, 9.0}, {3, 5, 0.5},            
             {4, 5, 1.0}};       
    measure_time(g,6);
    const auto result_permutations = tsp_permutations(g);
    const auto result_branches = tsp_branches(g);
    const auto expected = vector<int> {0, 3, 5, 1, 2, 4};
    CHECK(aligned(result_permutations, 0) == expected);
    CHECK(aligned(result_branches, 0) == expected);
}

TEST_CASE("[TSP] Seven vertices", "[tsp]") {
    Graph g{ {0, 1, 3.0}, {0, 2, 1.5}, {0, 3, 2.0}, {0, 4, 5.0}, {0, 5, 4.2}, {0, 6, 6.1},
             {1, 2, 1.8}, {1, 3, 0.5}, {1, 4, 2.6}, {1, 5, 3.7}, {1, 6, 2.1},
             {2, 3, 4.2}, {2, 4, 3.3}, {2, 5, 1.9}, {2, 6, 0.8},
             {3, 4, 6.0}, {3, 5, 2.7}, {3, 6, 3.4},
             {4, 5, 0.6}, {4, 6, 1.3},
             {5, 6, 2.9} };
    measure_time(g, 7);
    const auto result_permutations = tsp_permutations(g);
    const auto result_branches = tsp_branches(g);
    const auto expected = vector<int>{ 0, 2, 5, 4, 6, 1, 3 };
    CHECK(aligned(result_permutations, 0) == expected);
    CHECK(aligned(result_branches, 0) == expected);
}

TEST_CASE("[TSP] Eight vertices", "[tsp]") {
    Graph g{ {0, 1, 1.2}, {0, 2, 3.5}, {0, 3, 2.7}, {0, 4, 4.3}, {0, 5, 5.6}, {0, 6, 2.1}, {0, 7, 3.4},
             {1, 2, 1.6}, {1, 3, 0.9}, {1, 4, 2.2}, {1, 5, 1.1}, {1, 6, 4.2}, {1, 7, 3.0},
             {2, 3, 5.0}, {2, 4, 2.8}, {2, 5, 4.1}, {2, 6, 1.7}, {2, 7, 2.9},
             {3, 4, 3.6}, {3, 5, 2.3}, {3, 6, 1.4}, {3, 7, 0.7},
             {4, 5, 3.2}, {4, 6, 2.4}, {4, 7, 1.3},
             {5, 6, 4.5}, {5, 7, 3.1},
             {6, 7, 2.8} };
    measure_time(g, 8);
    const auto result_permutations = tsp_permutations(g);
    const auto result_branches = tsp_branches(g);
    const auto expected = vector<int>{ 0, 1, 5, 3, 7, 4, 2, 6 };
    CHECK(aligned(result_permutations, 0) == expected);
    CHECK(aligned(result_branches, 0) == expected);
}

TEST_CASE("[TSP] Nine vertices", "[tsp]") {
    Graph g{ {0, 1, 2.3}, {0, 2, 4.5}, {0, 3, 3.2}, {0, 4, 2.6}, {0, 5, 1.1}, {0, 6, 5.2}, {0, 7, 3.7}, {0, 8, 1.8},
             {1, 2, 1.6}, {1, 3, 4.8}, {1, 4, 3.7}, {1, 5, 2.9}, {1, 6, 1.4}, {1, 7, 2.6}, {1, 8, 3.0},
             {2, 3, 2.7}, {2, 4, 1.9}, {2, 5, 4.3}, {2, 6, 2.8}, {2, 7, 3.1}, {2, 8, 3.6},
             {3, 4, 2.0}, {3, 5, 1.5}, {3, 6, 4.7}, {3, 7, 3.2}, {3, 8, 2.1},
             {4, 5, 3.9}, {4, 6, 1.7}, {4, 7, 2.8}, {4, 8, 3.3},
             {5, 6, 4.2}, {5, 7, 2.5}, {5, 8, 1.3},
             {6, 7, 3.6}, {6, 8, 2.0},
             {7, 8, 1.8} };
    measure_time(g, 9);
    const auto result_permutations = tsp_permutations(g);
    const auto result_branches = tsp_branches(g);
    const auto expected = vector<int>{ 0, 5, 3, 4, 6, 1, 2, 7, 8 };
    CHECK(aligned(result_permutations, 0) == expected);
    CHECK(aligned(result_branches, 0) == expected);
}

TEST_CASE("[TSP] Ten vertices", "[tsp]") {
    Graph g{ {0, 1, 4.5}, {0, 2, 3.2}, {0, 3, 2.1}, {0, 4, 1.9}, {0, 5, 5.6}, {0, 6, 4.3}, {0, 7, 3.8}, {0, 8, 2.4}, {0, 9, 2.7},
             {1, 2, 2.0}, {1, 3, 3.1}, {1, 4, 1.8}, {1, 5, 3.6}, {1, 6, 2.7}, {1, 7, 4.2}, {1, 8, 2.8}, {1, 9, 3.4},
             {2, 3, 3.7}, {2, 4, 2.2}, {2, 5, 1.5}, {2, 6, 3.9}, {2, 7, 2.3}, {2, 8, 3.0}, {2, 9, 4.1},
             {3, 4, 4.0}, {3, 5, 2.8}, {3, 6, 3.2}, {3, 7, 1.7}, {3, 8, 3.4}, {3, 9, 2.6},
             {4, 5, 4.9}, {4, 6, 2.5}, {4, 7, 3.3}, {4, 8, 1.6}, {4, 9, 4.7},
             {5, 6, 1.4}, {5, 7, 3.5}, {5, 8, 2.0}, {5, 9, 1.9},
             {6, 7, 4.6}, {6, 8, 1.3}, {6, 9, 3.6},
             {7, 8, 2.2}, {7, 9, 3.8},
             {8, 9, 2.9} };
    measure_time(g, 10);
    const auto result_permutations = tsp_permutations(g);
    const auto result_branches = tsp_branches(g);
    const auto expected = vector<int>{ 0, 3, 7, 2, 1, 4, 8, 6, 5, 9 };
    CHECK(aligned(result_permutations, 0) == expected);
    CHECK(aligned(result_branches, 0) == expected);
}
