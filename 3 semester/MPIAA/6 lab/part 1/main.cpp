#define CATCH_CONFIG_RUNNER

#include "catch.hpp"
#include "graph.h"
#include "measure_time.h"
#include "tsp.h"

int main(int argc, char* argv[]) {
    
    int result = Catch::Session().run(argc, argv);
    //measure_time();
    return result;
}
