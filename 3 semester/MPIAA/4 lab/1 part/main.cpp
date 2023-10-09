#define CATCH_CONFIG_RUNNER

#include "catch.hpp"
#include "shortest_path.h"
#include "graph.h"
#include "measure_time.h"

int main(int argc, char* argv[]) {
    measure_time();

    int result = Catch::Session().run(argc, argv);
    return result;

}
