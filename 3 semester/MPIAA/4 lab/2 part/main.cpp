#define CATCH_CONFIG_RUNNER 
#include "catch.hpp" 
#include "graph.h"
#include "min_spanning_tree.h"
#include "measure_time.h"

int main(int argc, char* argv[]) {
	measure_time();
	int result = Catch::Session().run(argc, argv);
	return result;

}
